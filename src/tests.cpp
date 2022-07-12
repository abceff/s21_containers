#include <gtest/gtest.h>
#include "s21_containers.h"

// #include <list>

TEST(Test, default_list_constructor_test) {
    s21_list<long double *> my_list;
    long double * example;
    memset(&example, 0, sizeof(long double *));
    EXPECT_EQ((my_list.front()), example);
}
TEST(Test, parametrized_list_constructor_test) {
    s21_list<int> my_list(5);
    EXPECT_EQ((my_list.size()), 5);

    int example;
    memset(&example, 0, sizeof(int));
    EXPECT_EQ((my_list.back()), example);
}
TEST(Test, initializer_list_constructor_test) {
    std::initializer_list<double> a = {1.5, 2.34, 3.789, -0.35, 5};
    s21_list<double> my_list(a);
    s21_list<double>::ListIterator itr = my_list.begin();
    ++itr;
    ++itr;
    ++itr;
    --itr;
    EXPECT_EQ(*itr, 3.789);
    s21_list<double>::ListIterator itr2 = my_list.begin();
    ++itr2;
    ++itr2;
    EXPECT_TRUE(itr == itr2);
    s21_list<double>::ListIterator itr3 = my_list.begin();
    ++itr3;
    EXPECT_TRUE(itr2 != itr3);
    EXPECT_EQ((my_list.size()), 5);
}
TEST(Test, copy_list_constructor_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    s21_list<int> my_list(a);
    
    s21_list<int> my_list2(my_list);
    s21_list<int>::ListIterator itr = my_list2.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(Test, move_list_constructor_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    s21_list<int> my_list(a);
    s21_list<int> my_list2(std::move(my_list));

    s21_list<int>::ListIterator itr2 = my_list2.end();
    EXPECT_EQ(*itr2, 5);
    --itr2;
    EXPECT_EQ(*itr2, 4);
    --itr2;
    EXPECT_EQ(*itr2, 3);
    --itr2;
    EXPECT_EQ(*itr2, 2);
    --itr2;
    EXPECT_EQ(*itr2, 1);
}
TEST(Test, front_and_end_list_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    s21_list<int> my_list(a);
    EXPECT_EQ(my_list.front(), 1);
    EXPECT_EQ(my_list.back(), 5);
}
TEST(Test, empty_list_test) {
    s21_list<long double *> my_list;
    EXPECT_TRUE(my_list.empty());
}
TEST(Test, max_size_list_test) {
    s21_list<long double *> my_list;
    EXPECT_EQ(my_list.max_size(), SIZE_MAX);
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    s21_list<int> my_list2(a);
    EXPECT_EQ(my_list2.max_size(), SIZE_MAX);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
