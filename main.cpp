
#include "eld/any/any.hpp"

#include <iostream>
#include <gtest/gtest.h>

struct Foo{};
struct Bar{};

TEST(any_cast_check, int_from_int)
{
    eld::any i = int();
    ASSERT_TRUE(i.contains_type<int>());
}

TEST(any_cast_check, double_from_int)
{
    eld::any i = int();
    ASSERT_FALSE(i.contains_type<double>());
}

TEST(any_cast_check, foo_from_foo)
{
    eld::any i = Foo();
    ASSERT_TRUE(i.contains_type<Foo>());
}

TEST(any_cast_check, foo_from_int)
{
    eld::any i = int();
    ASSERT_FALSE(i.contains_type<Foo>());
}

TEST(any_cast_check, int_from_foo)
{
    eld::any i = Foo();
    ASSERT_FALSE(i.contains_type<Bar>());
}

TEST(any_cast_check, bar_from_bar)
{
    eld::any i = Bar();
    ASSERT_TRUE(i.contains_type<Bar>());
}

TEST(any_cast_check, bar_from_foo)
{
    eld::any i = Bar();
    ASSERT_FALSE(i.contains_type<Foo>());
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
