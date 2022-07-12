#include "s21_containers.h"
#include <iostream>
#include <list>

int main() {
    // std::initializer_list<int> a = {1, 2, 3, 4, 5};
    // s21_list<int> aboba(a);
    std::list<int> b = {1, 2, 3, 4, 5, 6};
    // std::list<int>::iterator it = b.end();
    std::cout << b.max_size() << std::endl;
    // s21_list<int> aboba(a);
    // // s21_list<int> copy(std::move(a));
    // // aboba->push_front(5);
    // // aboba.end();
    // aboba.erase(aboba.begin());

    // aboba.get_node_values();
    // s21_list<int> a;

    // std::list<s21_list<int>> myList;
    // std::list<s21_list<int>>::iterator it = myList.begin();
    // std::cout << *it << std::endl;

    // struct example {
    //     int a;
    //     char* b;
    // };
    // s21_list<struct example> our;
    // std::list<s21_list<struct example>> orig;
    // // our.get_node_values();
    // if (memcmp(&(our.front()), &(orig.front()), sizeof(struct example)) == 0) {
    //     std::cout << "области памяти равны" << std::endl;
        
    // } else {
    //     std::cout << "области памяти отличаются" << std::endl;
    // }


    return 0;
}