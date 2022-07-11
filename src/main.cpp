#include "s21_containers.h"


int main() {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    s21_list<int> aboba(a);
    // s21_list<int> copy(std::move(a));
    // aboba->push_front(5);
    // aboba.end();
    aboba.erase(aboba.begin());

    aboba.get_node_values();

    return 0;
}