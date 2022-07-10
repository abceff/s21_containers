#include "s21_containers.h"


int main() {
    std::initializer_list<int> a = {1, 2, 3};
    s21_list* aboba = new s21_list(a);
    // aboba->push_front(5);

    aboba->get_node_values();
    return 0;
}