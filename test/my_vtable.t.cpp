#include "my_vtable.h"
#include "vector"

#include "gtest/gtest.h"

TEST(my_vtable, tests) {
  using namespace my;
  {
    Animal animal = Cat{};
    animal.speak();
  }
  {
    Animal animal = Rabbit{};
    animal.speak();
  }
  std::vector<Animal> animals{Cat{}, Dog{}, Rabbit{}};
  EXPECT_EQ(animals[0].toString(), "Cat");
  EXPECT_EQ(animals[1].toString(), "Dog");
  EXPECT_EQ(animals[2].toString(), "Rabbit");
}
