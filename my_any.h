#pragma once
#include <utility>

namespace my {

class any {
  public:
    // CONSTRUCTORS
    any();

    template <typename T>
    any(T&&);

    any(any&&) = delete;
    any(const any&) = delete;

    // MODIFIERS
    template <typename T>
    any& operator=(T&&);

    any& operator=(any&&) = delete;
    any& operator=(const any&) = delete;

    template <typename T, typename... Args>
    T& emplace(Args&&... args);

    template <typename T>
    T& get();

    // OBSERVERS
    bool has_value() const;

    template <typename T>
    const T& get() const;

    ~any();

  private:
    template <typename T>
    static void release(void* ptr);

    void* d_item_p;

    void(*d_deleter_p)(void*);
};




template <typename T>
any::any(T&& val)
: d_item_p {static_cast<void*>(new T{std::forward<T>(val)})}
, d_deleter_p {&release<T>}
{
}

template <typename T>
any& any::operator=(T&& val) {
    const auto val_p = new T {std::forward<T>(val)};
    if (d_deleter_p) {
        // release the previously held item
        d_deleter_p(d_item_p);
    }
    d_item_p = static_cast<void*>(val_p);
    d_deleter_p = &release<T>;
    return *this;
}

template <typename T, typename... Args>
T& any::emplace(Args&&... args) {
    const auto val_p = new T {std::forward<Args>(args)...};
    if (d_deleter_p) {
        // release the previously held item
        d_deleter_p(d_item_p);
    }
    d_item_p = static_cast<void*>(val_p);
    d_deleter_p = &release<T>;
    return *static_cast<T*>(d_item_p);
}

template <typename T>
const T& any::get() const {
    if (&release<T> != d_deleter_p) {
        throw "bad type";
    }
    return *static_cast<T*>(d_item_p);
}

template <typename T>
T& any::get() {
    return const_cast<T&>(const_cast<const any&>(*this).get<T>());
}

template <typename T>
void any::release(void* ptr) {
    if (ptr) {
        delete static_cast<T*>(ptr);
        ptr = nullptr;
    }
}

} // close namesapce my
