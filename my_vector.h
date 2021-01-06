#include <cassert>
#include <utility>

namespace my {

template <typename T>
class Vector {
  public:
    Vector();

    Vector(std::initializer_list<T> items);

    // Accessors
    const T& operator[](size_t i) const;

    // Modifiers
    void reserve(size_t cap);

    void push_back(T item);

    T& operator[](size_t i);

    void reset();

    ~Vector();

    T* data();

  private:

    static constexpr size_t s_offset = sizeof(T);
    size_t                  d_capacity;
    size_t                  d_size;
    uint8_t*                d_buff;
};


template <typename T>
Vector<T>::Vector()
: d_capacity {2}
, d_size{0}
, d_buff{new uint8_t[d_capacity*s_offset]}
{}


template <typename T>
const T& Vector<T>::operator[](size_t i) const {
    assert(i <= d_size);
    return *(reinterpret_cast<T*>(d_buff + i * s_offset));
}

template <typename T>
T& Vector<T>::operator[](size_t i) {
    return *(reinterpret_cast<T*>(d_buff + i * s_offset));
}

template <typename T>
void Vector<T>::reset() {
    if (!d_buff) {
        return;
    }
    for (size_t i = 0; i < d_size; ++i) {
        this->operator[](i).~T();
    }
    delete[] d_buff;
    d_buff = nullptr;
    d_size = 0;
    d_capacity = 0;
}

template <typename T>
void Vector<T>::reserve(size_t cap) {
    assert(cap >= d_capacity);

    uint8_t* newBuff = new uint8_t[cap];
    auto size = d_size;
    for (size_t i = 0; i < d_size; ++i) {
        new (newBuff + s_offset * i) T{this->operator[](i)};
    }
    reset();
    d_buff = newBuff;
    d_size = size;
}

template <typename T>
void Vector<T>::push_back(T item) {
    if (d_size == d_capacity) {
        reserve(d_capacity << 1);
    }

    new (d_buff + s_offset * d_size) T{std::move(item)};
    ++d_size;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> items)
: d_capacity {items.size() * 2}
, d_size {0}
, d_buff {new uint8_t[d_capacity * s_offset]}
{
    for (auto item : items) {
        new (d_buff + s_offset * d_size) T{std::move(item)};
        ++d_size;
    }
}

template <typename T>
Vector<T>::~Vector() {
    reset();
}

template <typename T>
T* Vector<T>::data() {
    return reinterpret_cast<T*>(d_buff);
}
}
