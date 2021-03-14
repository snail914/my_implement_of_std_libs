#include <iostream>
#include <string>

namespace my {

class Animal {

public:
  template <typename T>
  Animal(const T &t)
  : d_derived{new T{t}}
  , d_vtable{&Animal::s_table<T>} {}

  Animal(const Animal &animal)
  : d_vtable{animal.d_vtable}
  , d_derived{animal.d_vtable->copy(animal.d_derived)} {}

  Animal(Animal &&animal)
  : d_vtable{animal.d_vtable}
  , d_derived{animal.d_vtable->move(animal.d_derived)} {}

  void speak() const { d_vtable->speak(d_derived); }

  std::string toString() const { return d_vtable->toString(d_derived); }

  ~Animal() {
    d_vtable->destroy(d_derived);
    std::cout << "destroy animal instance" << std::endl;
  }

private:
  struct VTable {
    void (*speak)(void *);
    std::string (*toString)(void *);
    void *(*copy)(void *);
    void *(*move)(void *);
    void (*destroy)(void *);
  };

  template <typename Derived>
  static constexpr VTable s_table{
      [](void *ptr) { static_cast<Derived *>(ptr)->speak(); },
      [](void *ptr) { return static_cast<Derived *>(ptr)->toString(); },
      [](void *ptr) -> void * {
        return new Derived(*(static_cast<Derived *>(ptr)));
      },
      [](void *ptr) -> void * {
        auto origin = static_cast<Derived *>(ptr);
        return new Derived(std::move(*origin));
      },
      [](void *ptr) { delete static_cast<Derived *>(ptr); }};

  void *d_derived;
  const VTable *d_vtable;
};

class Cat {
public:
  ~Cat() { std::cout << "destroy cat instance" << std::endl; }

  void speak() const { std::cout << "Cat speaks" << std::endl; }

  std::string toString() const { return "Cat"; }
};

class Dog {
public:
  ~Dog() { std::cout << "destroy cat instance" << std::endl; }

  void speak() const { std::cout << "Dog speaks" << std::endl; }

  std::string toString() const { return "Dog"; }
};

class Rabbit {
public:
  ~Rabbit() { std::cout << "destroy rabbit instance" << std::endl; }

  void speak() const { std::cout << "Rabbit speaks" << std::endl; }

  std::string toString() const { return "Rabbit"; }
};

} // namespace my
