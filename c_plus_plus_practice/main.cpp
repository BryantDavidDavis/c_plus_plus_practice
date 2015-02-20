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
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <stack>
#include <set>
#include <vector>
#include <unordered_map>
//#include "bry_stack.h"
//#include "blist.h"
//#include "blist.cpp"
//#include "clist.h"
//#include "clist.cpp"
//#include "bstack.h"
//#include "bstack.cpp"
//#include "bqueue.h"
//#include "bqueue.cpp"
//#include "cstack.h"
//#include "SetOfStacks.h"
//#include "myqueue.h"
//#include "AnimalQueue.h"
//#include "btree.h"
//#include "bgraph.h"
//#include "priority_queue.h"
//struct Command{
//    std::vector<std::string> line {};
//};

class Database {
public:
    
    Database():pairs{std::unordered_map<std::string, int>{}}, count{std::unordered_map<int, int>{}} {}
    
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
        if (!blocks.empty() && (current_command.at(0) == "SET" || current_command.at(0) == "UNSET")) {
            build_rollback_command(current_command);
            blocks.top().push(rollback_command); //this is not pushing anything onto the top stack
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
        }
        if (current_command.at(0) == "ROLLBACK") {
            while(!blocks.top().empty()) {
                current_command = blocks.top().top();
                handle_command();
                blocks.top().pop();
            }
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
    
    void unset(std::string name) {
        int value = pairs.find(name)->second;
        if (pairs.erase(name)) {
            --count.find(value)->second;
        }
    }
    
    int numequalto(int x) {
        return ( count.find(x) != count.end() ) ? count.find(x)->second : 0;
    }
    
    void end() {
        exit(9);
    }
    
    std::vector<std::string> current_command{};
    
private:
    std::unordered_map<std::string, int> pairs {};
    std::unordered_map<int, int> count {};
    std::stack<std::stack<std::vector<std::string>>> blocks {};
    std::vector<std::string> rollback_command{};
    
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
    
    Database database{};
    
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
        
    }
    
    return 0;
}

//    while (keep_running) {
//        for (std::string word; std::cin >> word;) {
//            if (word == "GET") {
//                std::cout << word << '\n';
//                //database.set(std::cin >> word, std::cin >> word);
//
//            }
//            //std::cout << word << '\n';
//        }
//    } //this works for inputs of one type

//    while (command != "END") {
//        std::cin >> command;
//        if (command == "SET") {
//            if(std::cin >> key) {
//                if (std::cin >> value) {
//                    std::cout << command << key << value << '\n';
//                } else {
//                    std::cout << "invalid command";
//                }
//            } else {
//                std::cout << "invalid command";
//            }
//        } else if (command == "GET") {
//                if (std::cin >> key) {
//                    std::cout << "getting" << key << '\n';
//                } else {
//                    std::cout << "key not specified";
//                }
//        } else {
//            std::cout << "no such command" << '\n';
//        }
//        //std::cin >> key;
//        //std::cin >> value;
//        //std::cout << command << key << value << '\n';
//    }
//database.set("bryant", 33);
//database.set("jolene", 72);
//database.set("steven", 67);
//database.set("suzanne", 31);
//database.set("lori", 33);
//std::cout <<  database.get("bryant");
//database.unset("bryant");
//std::cout << database.get("bryant");
//database.set("bryant", 33);
//std::cout << database.numequalto(33);
//    std::unordered_map<std::string, int> pairs {};
//    std::unordered_map<int, int> count {};
//    std::vector<std::pair<std::string, int>> values {{"balasf", 2}, {"mysecondguy", 15}, {"whatsupdoc", 42}};
//    for (auto i = values.begin(); i != values.end(); ++i) {
//        pairs.insert(*i);
//    }
//    for (auto i = pairs.begin(); i != pairs.end(); ++i) {
//        std::cout << i->second;
//    }

//    Priority_queue mypq;
//    mypq.offer(3);
//    mypq.offer(6);
//    mypq.offer(9);
//    mypq.offer(12);
//    mypq.offer(15);
//    mypq.offer(11);
//    mypq.offer(4);
//    mypq.offer(1);
//    std::cout << mypq.poll();
//    std::cout << mypq.poll();
//    std::cout << mypq.poll();
//    std::cout << mypq.poll();
//    std::cout << mypq.poll();
//    std::cout << mypq.poll();
//std::cout << mypq.peek();
//    std::vector<int> a{1,2,3,4,5,6,7,8,9};
//    BSTree big_tree = BSTree::min_height(a);
//    std::vector<int> b{5,6,7,8,9};
//    BSTree sub_tree = BSTree::min_height(b);
//
//    //std::cout << BSTree::is_subtree(big_tree, sub_tree);
//    bool outcome = BSTree::is_subtree(big_tree, sub_tree);
//    if (outcome == true) {
//        std::cout << "it is!";
//    } else {
//        std::cout << "it isn't";
//    }
//
//    //std::cout << 1;
//    //std::cout << new_tree.isBST();

//    std::vector<std::list<int>> lists {};
//
//    new_tree.build_lists(lists);

//    bgraph mygraph{};
//
//    mygraph.insert(0,1);
//    mygraph.insert(0,4);
//    mygraph.insert(1,2);
//    mygraph.insert(1,3);
//    mygraph.insert(4,3);
//    mygraph.insert(4,1);
//    mygraph.insert(2,3);
//    mygraph.insert(4,6);
//
//    std::cout << mygraph.path_exists(0, 3);
//    std::cout << mygraph.path_exists(6, 1);
//    std::cout << mygraph.path_exists(0, 3);
//

//
//    //std::set<int> myset = {3,4,6,2,9,7,5,12,1};
//
//    //std::cout << *(myset.begin());
//
//    BSTree mytree{};
//
//    for (int i = 5; i != 10; ++i) {
//        mytree.insert(i);
//    }
//    for (int i = 1; i != 5; ++i) {
//        mytree.insert(i);
//    }
//    for (int i = 10; i != 14; ++i) {
//        mytree.insert(i);
//    }
//
//    std::cout << mytree.depth();
//
//    BSTree newtree{};
//
//    newtree.insert(3);
//    newtree.insert(2);
//    newtree.insert(4);
//    newtree.insert(1);
//    newtree.insert(5);
//
//    std::cout << mytree.is_balanced();
//    std::cout << newtree.is_balanced();

//    AnimalQueue shelter {};
//    shelter.enqueue(1, "charlie");
//    shelter.enqueue(2, "phillip");
//    shelter.enqueue(2, "ralph");
//    shelter.enqueue(1, "baxter");
//    shelter.enqueue(1, "langford");
//
//    std::cout << *(shelter.dequeueDog().name);
//    std::cout << *(shelter.dequeueCat().name);
//    shelter.enqueue(1, "clifford");
//    std::cout << *(shelter.dequeueAny().name);
//    std::cout << *(shelter.dequeueCat().name);
//    std::cout << *(shelter.dequeueAny().name);
//    std::cout << *(shelter.dequeueAny().name);

//    std::stack<int> my_stack;
//    my_stack.push(3);
//    my_stack.push(1);
//    my_stack.push(5);
//    my_stack.push(7);
//    my_stack.push(6);
//    my_stack.push(9);
//    my_stack.push(4);
//
//    sort_stack(my_stack);
//
//    while (!my_stack.empty()) {
//        std::cout << my_stack.top();
//        my_stack.pop();
//    }

//void sort_stack(std::stack<int>& a) {
//    std::stack<int> b {};
//    int to_push {};
//    int min {};
//    for (int i = 0; ((a.size() - i) != 0); ++i) {
//        bool has_min = false;
//
//        while(!a.empty()) {
//            if (!has_min) {
//                min = a.top();
//                a.pop();
//                has_min = true;
//            } else if (a.top() < min) {
//                b.push(min);
//                min = a.top();
//                a.pop();
//            } else {
//                to_push = a.top();
//                b.push(to_push);
//                a.pop();
//            }
//
//        }
//        a.push(min);
//        while(!b.empty()) {
//            to_push = b.top();
//            a.push(to_push);
//            b.pop();
//        }
//    }
//}

//    MyQueue myqueue {};
//
//    for (int i = 0; i != 5; ++i) {
//        myqueue.push(i);
//    }
//
//
//    std::cout << myqueue.pop() << '\t';
//    std::cout << myqueue.pop() << '\t';
//    myqueue.push(8);
//    std::cout << myqueue.pop() << '\t';
//    std::cout << myqueue.pop() << '\t';
//    for (int i = 0; i != 5; ++i) {
//        if (i == 49) {
//            //std::cout << myqueue.pop() << '\t';
//        }
//    }
//


//SetOfStacks my_stack {};
//
//for (int i = 0; i != 200; ++i) {
//    my_stack.push(i);
//}
//
//for (int i = 0; i != 200; ++i) {
//    std::cout << my_stack.pop() << '\t';
//    }
//    cstack my_stack {};
//
//    for (int i = 15; i != 0; --i) {
//        my_stack.push(i);
//        std::cout << my_stack.min();
//    }
//
//    for (int i = 0; i != 10; ++i) {
//        std::cout << my_stack.pop() << '\n';
//        std::cout << "min is: " << my_stack.min() << '\n';
//    }
//    std::cout << my_stack.peek();
//
//    for (int i = 14; i != 4; --i) {
//        std::cout << my_stack.pop();
//    }

//    bqueue<int> my_queue {};
//    for (int i = 0; i != 20; ++i) {
//        my_queue.enqueue(i);
//    }
//
//    std::cout << my_queue.peek();
//    my_queue.dequeue();
//    std::cout << my_queue.peek();
//
//    bstack<min_wrapper<int>> my_stack {};
//    for (int i = 0; i != 12; ++i) {
//        my_stack.push(i);
//    }

//std::cout << my_stack.min();
//std::cout << clist<int>::is_palindrome(a);
//    for (auto p = a.begin(); p != a.end(); ++p) {
//        std::cout << *p;
//    }


//    clist<int> result = clist<int>::sumlists(a, b);
//
//    for (auto p = result.begin(); p != result.end(); ++p) {
//        std::cout << *p;
//    }
//clist<int> a {8,9,3,7,3,9,8};
//clist<int> b {2,0,5,6};
//
//bool has_dupes(char* test) {
//    bool* characters = new bool[256];
//    
//    for (auto i = 0; i < 256; ++i) {
//        characters[i] = false;
//    }
//    
//    for (auto i = 0; test[i] != '\0'; ++i) {
//        
//        
//        if (characters[test[i]] == true) {
//            delete[] characters;
//            return false;
//        } else {
//            characters[test[i]] = true;
//        }
//    }
//    delete[] characters;
//    return true;
//}
//
//void reverse_string(char* test) {
//    char swapper;
//    int length = 0;
//    char end_char;
//    for (auto i = 0; test[i] != '\0'; ++i) {
//        ++length;
//    }
//    for (auto i = 0; i < length/2; ++i) {
//        swapper = test[i];
//        end_char = test[length - i - 1];
//        test[i] = end_char;
//        test[length - i - 1] = swapper;
//        //std::cout << test;
//    }
//}
//
//bool is_perm(std::string first, std::string second) {
//    int length_first = 0;
//    int length_second = 0;
//    for (auto i = 0; first[i] != '\0'; ++i) {
//        ++length_first;
//    }
//    for (auto i = 0; second[i] != '\0'; ++i) {
//        ++length_second;
//    }
//    
//    if (length_first != length_second) {
//        return false;
//    }
//    
//    std::sort(first.begin(), first.end());
//    std::sort(second.begin(), second.end());
//    //std::cout << first << '\n';
//    //std::sort(std::begin(second), std::end(second) - 1);
//    //std::sort(first[0], first[length_first]);
//    //std::sort(second[0], second[length_second]);
//    
//    for (auto i = 0; i < length_first; ++i) {
//        if (first[i] != second[i]) {
//            return false;
//        }
//    }
//    
//    return true;
//    
//}
//
//void escape_spaces(char* word, int length) {
//    
//    char* back;
//    for (auto i = 0; i < (length - 1); ++i) {
//        if (word[i] == ' ') {
//            length = length + 2;
//            back = word + length;
//            while (back > (word + i + 1)) {
//                *back = *(back - 2);
//                --back;
//            }
//            word[i] = '%';
//            word[i+1] = '2';
//            word[i+2] = '0';
//            i = i + 2;
//        }
//    }
//    word[length] = '\0';
//}
//
//std::string compress_string(std::string my_string) {
//    
//    //first we check if there are duplicates
//    bool is_compressible = false;
//    for (auto p = my_string.begin(); ((p != my_string.end()) && (!is_compressible)); ++p) {
//        if (*p == *(p+1)) {
//            is_compressible = true;
//        }
//    }
//    if (!is_compressible) {
//        return my_string;
//    }
//    
//    std::string compressed_string {};
//    for (std::string::iterator p = my_string.begin(); p != my_string.end(); ++p) {
//        char count = '1';
//        while (*p == *(p + 1)) {
//            ++p;
//            ++count;
//        }
//        compressed_string.push_back(*p);
//        compressed_string.push_back(count);
//    }
//    return compressed_string;
//    
//}
//
//void modify_string(std::string& a) {
//    a[0] = 'f';
//}

//
//blist<int> mylist {};
//
//for (int i = 0; i < 12; ++i) {
//    mylist.push_front(i);
//}
//for (int i = 0; i < 5; ++i) {
//    mylist.push_front(i);
//}
////mylist.remove(7);
//
//mylist.print_list();
//std::cout << '\n';
//mylist.deduplicate();
//mylist.print_list();
//std::cout << '\n';
//mylist.partition(7);
//mylist.print_list();

//
//clist<int> my_list {};
//for (int i = 0; i < 15; ++i) {
//    my_list.push_front(i);
//}
//
//for (int i = 0; i < 8; ++i) {
//    my_list.push_front(i);
//}
//my_list.reverse();
//
//my_list.deduplicate(my_list);

//blist<int> my_list {};
//my_list.push_front(7);
//my_list.push_front(4);
//my_list.push_front(8);
//my_list.push_front(4);
//my_list.push_front(6);
//my_list.push_front(9);
//
//my_list.deduplicate();
//my_list.remove(8);
//my_list.remove(7);
//my_list.remove(4);
//my_list.pop_front();
//my_list.pop_front();
//my_list.pop_front();

//    blist<std::string> your_list {};
//    your_list.push_front("let's try this one");
//    your_list.push_front("now let's try that one");
//
//    your_list.pop_front();
//
//
//
//std::string a {"alabaster"};
//modify_string(a);
//std::cout << a;
//    std::string test1 {"aaabbcddddeefffffffg"};
//    std::string test2 {"abcdefg"};
//    //compress_string(test1);
//    //compress_string(test2);
//    std::cout << test1 << '\n';
//    std::cout  << compress_string(test1) << '\n';
//    std::cout << "hello my furry friends, you are so furry indeed";
//    std::cout << "why don't you just go have a party with all your furriness";

//    Bry_stack first_stack{5};
//    std::cout << first_stack.capacity();
//    first_stack.push(7);
//    std::cout << first_stack.size();
//    std::cout << first_stack.peek();
//

//char test[] {"abcdedfasdf asdf;lkjsdf"};
//char another_test[] {"blam"};
//char first_test[] {"robert"};
//char second_test[] {"trebor"};
//std::string test2 {"trebor"};

//int int_test[] {0,1,5,3,8,12,2,1};
//std::cout << has_dupes(test) << "\n";
//std::cout << has_dupes(another_test);
//reverse_string(test);
//std::cout << test;
//std::sort(std::begin(int_test), std::end(int_test));
//std::cout << int_test[4];

//    std::sort(std::begin(test), std::end(test) - 1);
//    for (auto i = 0; test[i] != '\0'; ++i) {
//        std::cout << test[i];
//    }

//std::cout << is_perm(a_third_test, fourth_test);
//std::cout << is_perm(test1, test2);
//std::cout << test1 << '\n';

//std::string test1 {"Tim ot hy"};

//char test1[14] {"tim ot hy    "};
//escape_spaces(test1, 9);
//std::string test1 {"tim ot hy    "};
//std::cout << test1;

