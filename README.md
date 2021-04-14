# my impl of std libs

### `my::vtable` (vs c++ `virtual`)
#### solution
Re-implementation of `Sy Brand(twitter@TartanLlama)`'s excellent ACCU 2021 talk
about dynamic polymorphism with code injection and metaclasses.
#### example
```c++
Animal animal = Cat();
animal.speak(); // cat speaks;

std::vector<Animal> animals{Cat{}, Dog{}, Rabbit{}};
for (const auto& a : animals) {  a.speak(); }
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

