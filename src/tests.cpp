#include <gtest/gtest.h>
#include "s21_containers.h"

// #include <list>

TEST(Test, default_list_constructor_test) {
    s21_list<long double *> our;
    long double * example;
    memset(&example, 0, sizeof(long double *));
    EXPECT_EQ((our.front()), example);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
