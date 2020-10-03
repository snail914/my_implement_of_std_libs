# my impl of std libs (meta-programming)
better understand std classes by implementing my versions of c++ std libs

```bash
mkdir build&&cmake -B build&&make -j -C build&&./build/test_my_libs
```

### `my::any` (vs `std::any`)
#### solution
using function pointer to store the descructor of provided template type
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
