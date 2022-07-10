#include "s21_containers.h"
#include <iostream>

int main() {
    // std::initializer_list<int> a = {1, 2, 3};
    s21_list* aboba = new s21_list();
    aboba->push_front(5);

    std::cout << aboba->get_node_value() << std::endl;
    return 0;
}