#include <string>

#include "my_tuple.h"
#include "my_objects.h"

#include "gtest/gtest.h"

TEST(my_tuple, tests) {
    std::cerr << 123;
    using Int3 = my::tuple<int, int, int>;
    static_assert(Int3::size() == 3, "");
    constexpr Int3 nums{1, 2, 1};
    static_assert(my::get<2>(nums) == 1, "");

    using Double = my::tuple<double>;
    static_assert(Double::size() == 1, "");
    static_assert(my::get<0>(Double{2.3}) == 2.3, "");

    using BoolStrInt =  my::tuple<bool, std::string, int>;
    static_assert(BoolStrInt::size() == 3, "");
    assert(my::get<1>(BoolStrInt{true, "1223", 23}) == "1223");

    using Str2 = my::tuple<std::string, std::string>;
    static_assert(Str2::size() == 2, "");

    using Object2 = my::tuple<my::Chair, my::Desk>;
    static_assert(Object2::size() == 2, "");
    Object2 o2{{}, {2, 3}};
    assert((my::get<1>(o2) == my::Desk{2, 3}));
}
