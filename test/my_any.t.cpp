#include <utility>
#include "my_any.h"
#include "my_objects.h"

#include "gtest/gtest.h"

TEST(my_any, tests) {
    my::any a;
    EXPECT_FALSE(a.has_value());

    a.emplace<my::Ball>();
    EXPECT_TRUE(a.has_value());

    my::any b{123};

    my::any c{my::Ball()};
    const auto& item = c.emplace<my::Desk>(1, 2);
    EXPECT_EQ(item, my::Desk(1, 2));
    EXPECT_EQ(c.get<my::Desk>(), my::Desk(1, 2));
    EXPECT_THROW({
        c.get<int>();
    }, const char*);
}

TEST(my_any, copy) {
    const my::any a = my::Desk(1, 2);
    const my::any b {a};
    my::any c;
    my::any d = c;
    c = b;
}

TEST(my_any, move) {
    my::any a = my::Desk(1, 2);
    my::any b {std::move(a)};
    my::any c;
    c = std::move(b);
    my::any d = my::any();
}
