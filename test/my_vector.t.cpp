#include <utility>
#include "my_vector.h"
#include "my_objects.h"

#include "gtest/gtest.h"

TEST(my_vector, tests) {
    my::vector<int> a;
    EXPECT_EQ(a.size(), 0);
    my::vector<int> b{2};
    EXPECT_EQ(b.size(), 2);

    my::vector<my::Ball> c;
    my::vector<my::Ball> d{2};
    d.reserve(4);
    EXPECT_EQ(d.size(), 2);
    d.clear();
    EXPECT_EQ(d.size(), 0);
}
