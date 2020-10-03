#include <cassert>

#include "my_any.h"
#include "my_objects.h"


int main() {
    my::any a;
    assert(!a.has_value());
    a.emplace<my::Ball>();
    assert(a.has_value());

    my::any b{123};

    my::any c{my::Ball()};
    const auto& item = c.emplace<my::Desk>(1, 2);
    assert(item == my::Desk(1, 2));
    assert(c.get<my::Desk>() == my::Desk(1, 2));
    //c.get<int>(); // expect throw
}
