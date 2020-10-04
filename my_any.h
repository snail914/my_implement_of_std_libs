#pragma once
#include <utility>

namespace my {

class any {
  public:
    // CONSTRUCTORS
    any();

    template <typename T, typename U=std::enable_if_t<!std::is_same<std::remove_reference_t<T>, any>::value, void>>
    any(T&&);

    any(any&&);

    any(const any&);

    // MODIFIERS
    template <typename T>
    any& operator=(T&&);

    any& operator=(any&&);
    any& operator=(const any&);

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

    template <typename T>
    static void* copy(void* ptr);

    void reset();

    void* d_item_p;

    void(*d_deleter_p)(void*);

    void*(*d_copier_p)(void*);
};

template <typename T, typename>
any::any(T&& val)
: d_item_p {static_cast<void*>(new T{std::forward<T>(val)})}
, d_deleter_p {&release<T>}
, d_copier_p {&copy<T>}
{
}

template <typename T>
any& any::operator=(T&& val) {
    const auto val_p = new T {std::forward<T>(val)};
    // release the previously held item
    reset();
    d_item_p = static_cast<void*>(val_p);
    d_deleter_p = &release<T>;
    d_copier_p = &copy<T>;
    return *this;
}

template <typename T, typename... Args>
T& any::emplace(Args&&... args) {
    const auto val_p = new T {std::forward<Args>(args)...};
    // release the previously held item
    reset();
    d_item_p = static_cast<void*>(val_p);
    d_deleter_p = &release<T>;
    d_copier_p = &copy<T>;
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

template <typename T>
void* any::copy(void* ptr) {
    T* val_p = nullptr;
    if (ptr) {
        val_p = new T{*static_cast<T*>(ptr)};
    }
    return static_cast<void*>(val_p);
}

} // close namespace my
