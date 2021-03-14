#pragma once
#include <iostream>

namespace my {

struct Chair {
    Chair() {
        std::cout << "'Chair' default constructed" << std::endl;
    }
    Chair(const Chair&) {
        std::cout << "'Chair' copy constructed" << std::endl;
    }
    Chair(Chair&&) {
        std::cout << "'Chair' move constructed" << std::endl;
    }
    ~Chair() {
        std::cout << "'Chair' destructed" << std::endl;
    }
};

struct Desk {
    Desk(int num, int age)
    : d_num {num}
    , d_age {age} {
        std::cout << "'Desk' constructed with num="
                  << num  << ", age=" << age << std::endl;
    }
    Desk(const Desk& rhs)
    : d_num {rhs.d_num}
    , d_age {rhs.d_age} {
        std::cout << "'Desk' copy constructed" << std::endl;
    }
    Desk(Desk&& rhs)
    : d_num {rhs.d_num}
    , d_age {rhs.d_age} {
        std::cout << "'Desk' move constructed" << std::endl;
    }
    ~Desk() {
        std::cout << "'Desk' destructed" << std::endl;
    }

    bool operator==(const Desk& rhs) const {
        return d_num == rhs.d_num && d_age == rhs.d_age;
    }

  private:
    int d_num;
    int d_age;
};

}
