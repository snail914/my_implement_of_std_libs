# my impl of std libs
better understand std classes by implementing my versions of c++ std libs

### tags
meta-programming, std, googletest

```bash
# using google test framework
mkdir build&&cmake -B build&&make -j -C build&&./build/test_my_libs
```

### `my::any` (vs `std::any`)
#### solution
using function pointer to store the destructor of provided template type
#### example
```c++
my::any a;
a.emplace<std::string>("abc");
a = 23;
assert(23 == a.get<int>());
```

### `my::tuple` (vs `std::tuple`)
#### solution
using chained inheritance
#### example
```c++
using DoubleInt = my::tuple<double, int>;
static_assert(DoubleInt::size() == 2, "");
static_assert(my::get<0>(DoubleInt(2.4, 50)) == 2.4, "");
```

### `my::function` (vs `std::function`)
#### solution
using inheritance to store the functor of provided template type. similar
concept as `my::any`
#### example
```c++
using F = my::function<bool(const int&, const int&)>;
F f {std::less<int>()};
EXPECT_EQ(f(10, 20), true);
```

