//
//  main.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 11/26/14.
//  Copyright (c) 2014 Bryant Davis. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <stack>
#include <vector>
#include <unordered_map>

class Database {
public:
    
    Database()
        :pairs{std::unordered_map<std::string, int>{}},
        count{std::unordered_map<int, int>{}},
        blocks{std::stack<std::stack<std::vector<std::string>>>{}},
        current_command{std::vector<std::string>{}},
        rollback_command{std::vector<std::string>{}} {}
    
    bool command_ready() {
        if (current_command.at(0) == "SET") { return current_command.size() == 3;}
        if (current_command.at(0) == "GET") { return current_command.size() == 2;}
        if (current_command.at(0) == "UNSET") { return current_command.size() == 2;}
        if (current_command.at(0) == "NUMEQUALTO") { return current_command.size() == 2;}
        if (current_command.at(0) == "BEGIN") { return current_command.size() == 1;}
        if (current_command.at(0) == "ROLLBACK") { return current_command.size() == 1;}
        if (current_command.at(0) == "COMMIT") { return current_command.size() == 1;}
        if (current_command.at(0) == "END") { end(); return true;}
        return true; //if command doesn't exist let handle_command detect this
    }
    
    void handle_command() {
        if (current_command.at(0) == "BEGIN") {
            blocks.push(std::stack<std::vector<std::string>>{});
            return;
        }
        if (!rollingback && !blocks.empty() && (current_command.at(0) == "SET" || current_command.at(0) == "UNSET")) {
            build_rollback_command(current_command);
            blocks.top().push(rollback_command);
            if (current_command.at(0) == "SET") { unset(current_command.at(1)); }
        }
        if (current_command.at(0) == "SET") {
            int value = 0;
            std::istringstream (current_command.at(2)) >> value;
            set(current_command.at(1), value);
            return;
        }
        if (current_command.at(0) == "GET") {
            std::cout << get(current_command.at(1)) << '\n';
            return;
        }
        if (current_command.at(0) == "UNSET") {
            unset(current_command.at(1));
            return;
        }
        if (current_command.at(0) == "NUMEQUALTO") {
            int value = 0;
            std::istringstream (current_command.at(1)) >> value;
            std::cout << numequalto(value) << '\n';
            return;
        }
        if (current_command.at(0) == "COMMIT") {
            while (!blocks.empty()) {
                blocks.pop();
            }
            return;
        }
        if (current_command.at(0) == "ROLLBACK") {
            rollingback = true;
            while(!blocks.top().empty()) {
                current_command = blocks.top().top();
                handle_command();
                blocks.top().pop();
            }
            blocks.pop();
            rollingback = false;
            return;
        }
        if (current_command.at(0) == "END") {
            end();
            return;
        }
        std::cout << "there was a problem with your query\n";
    }
    
    void set(std::string name, int value) {
        auto i = pairs.find(name);
        if (i != pairs.end()) {
            i->second = value;
        } else {
            pairs.insert({name, value});
        }
        auto c = count.find(value);
        if( c != count.end() ) {
            ++c->second;
        } else {
            count.insert({value, 1});
        }
    }
    
    int get(std::string name) {
        return ( pairs.find(name) != pairs.end() ) ? pairs.find(name)->second : NULL;
    } //could use a private method that returns a pointer, and the public method will print a string of either null or 1
    
    void unset(std::string name) { //if it wasn't yet set, we need to detect this
        if (pairs.find(name) != pairs.end()) {
            int value = pairs.find(name)->second;
            if (pairs.erase(name)) {
                --count.find(value)->second;
            }
        }
    }
    
    int numequalto(int x) {
        return ( count.find(x) != count.end() ) ? count.find(x)->second : 0;
    }
    
    void end() {
        exit(9);
    }
    
    std::vector<std::string> current_command;
    
private:
    std::unordered_map<std::string, int> pairs;
    std::unordered_map<int, int> count;
    std::stack<std::stack<std::vector<std::string>>> blocks;
    std::vector<std::string> rollback_command;
    bool rollingback = false;
    void build_rollback_command(std::vector<std::string> current_command) {
      //apply an inverse operation to SET and UNSET
        rollback_command.clear();
        if (current_command.at(0) == "SET") {
            if (get(current_command.at(1))) {
                rollback_command.push_back(current_command.at(0));
                rollback_command.push_back(current_command.at(1));
                rollback_command.push_back(std::to_string(get(current_command.at(1))));
            } else {
                rollback_command.push_back("UNSET");
                rollback_command.push_back(current_command.at(1));
            }
        } else {
            if (get(current_command.at(1))) {
                rollback_command.push_back(current_command.at(0));
                rollback_command.push_back(current_command.at(1));
                rollback_command.push_back(std::to_string(get(current_command.at(1))));
            }
            //if unset is called on something that isn't set then don't need to build rollback command
        }
    }
};
int main(int argc, const char * argv[]) {
    
    Database database {};
    
    std::cout << "welcome to My Simple Database, you can terminate the program by entering END\n";
    
    while (true) {
        std::string word;
        
        while (std::cin >> word) {
            database.current_command.push_back(word);
            if (database.command_ready()) {
                database.handle_command();
                database.current_command.clear();
            }
        }
        
        if(std::cin.eof()) {
            std::cout << "reached end of file";
            std::cin.clear();
        }
        
    }
    
    return 0;
}
