#include "my_function.h"

#include "gtest/gtest.h"

TEST(my_functin, test_lambda) {
    using F = my::function<int(int, int)>;
    const auto add = [](int lhs, int rhs){
        return lhs + rhs;
    };

    {
        F f(add);
        EXPECT_EQ(f(10, 20), 30);
    }

    {
        F f;
        f = add;
        EXPECT_EQ(f(10, 20), 30);
    }
}

TEST(my_functin, test_functor) {
    using F = my::function<bool(const int&, const int&)>;

    {
        F f {std::less<int>()};
        EXPECT_EQ(f(10, 20), true);
    }

	{
		F f;
		f = std::less<int>();
		EXPECT_EQ(f(10, 20), true);
	}
}

std::string cat(const std::string& lhs, const std::string& rhs) {
	return lhs + rhs;
}

TEST(my_functin, test_func_ptr) {
    using F = my::function<std::string(const std::string&,
									   const std::string&)>;
    {
		F f{cat};
        EXPECT_EQ(f("123", "456"), "123456");
    }

	{
		F f;
		f = &cat;
        EXPECT_EQ(f("123", "456"), "123456");
	}
}
