#include "my_vtable.h"

#include "gtest/gtest.h"

TEST(my_vtable, tests) {
    my::Animal animal = my::Cat();
    animal.speak();
}

