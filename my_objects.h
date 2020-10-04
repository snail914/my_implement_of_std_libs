#pragma once
#include <iostream>

namespace my {

struct Ball {
    Ball() {
        std::cout << "'Ball' default constructed" << std::endl;
    }
    Ball(const Ball&) {
        std::cout << "'Ball' copy constructed" << std::endl;
    }
    Ball(Ball&&) {
        std::cout << "'Ball' move constructed" << std::endl;
    }
    ~Ball() {
        std::cout << "'Ball' destructed" << std::endl;
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
