#include <iostream>
#include <string>

namespace my {

class Animal {

  public:
    template <typename T>
    Animal(const T& t)
    : d_derived{static_cast<void*>(new T{t})}
    , d_vtable{&Animal::s_table<T>}
    {}

    void speak() const {
        d_vtable->speak(d_derived);
    }

    std::string toString() const {
        return d_vtable->toString(d_derived);
    }

    ~Animal() {
        d_vtable->destroy(d_derived);
        std::cout << "destroy animal instance" << std::endl;
    }

  private:
    struct VTable {
        void(*speak)(void*);
        std::string(*toString)(void*);
        void(*destroy)(void*);
    };

    template <typename Derived>
    static constexpr VTable s_table {
        [](void* ptr) { static_cast<Derived*>(ptr)->speak(); },
        [](void* ptr) { return static_cast<Derived*>(ptr)->toString(); },
        [](void* ptr) { delete static_cast<Derived*>(ptr); }
    };

    void*   d_derived;
    const VTable* d_vtable;
};


class Cat {
  public:
    ~Cat() {
        std::cout << "destroy cat instance" << std::endl;
    }

    void speak() const { std::cout << "Cat speaks" << std::endl; }

    std::string toString () const { return "Cat"; }
};
}
