#include <cstddef>
#include <cstdint>

namespace my {

template <typename T>
class vector {
  public:
    vector()
    : d_size{0}
    , d_capacity{2}
    , d_buffer{new uint8_t[offset*d_capacity]}
    {}

    explicit vector(size_t size);

    //vector(size_t size, const T& defaultValue);

    //vector(std::initilizer_list<T> items);

    T& at(size_t idx);
    const T& at(size_t idx) const;

    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

    void reserve(size_t capacity);

    size_t size() const { return d_size; }

    void clear();

    ~vector();

  private:
    size_t   d_size;
    size_t   d_capacity;
    uint8_t* d_buffer;
    static constexpr size_t offset = sizeof(T);
};

template <typename T>
vector<T>::vector(size_t size)
: d_size{size}
, d_capacity{size}
, d_buffer{new uint8_t[d_capacity*offset]}
{
    for(size_t i = 0; i < d_size; ++i)
    {
        new (d_buffer + offset * i) T{};
    }
}

template <typename T>
T& vector<T>::operator[](size_t idx) {
    return const_cast<T&>(const_cast<const vector*>(this)->operator[](idx));
}

template <typename T>
const T& vector<T>::operator[](size_t idx) const {
    return reinterpret_cast<const T&>(d_buffer[idx*offset]);
}

template <typename T>
T& vector<T>::at(size_t idx) {
    return const_cast<T&>(const_cast<const vector*>(this)->at(idx));
}

template <typename T>
const T& vector<T>::at(size_t idx) const {
    if (idx >= d_size) {
        throw "Error";
    }
    return reinterpret_cast<const T&>(d_buffer[idx*offset]);
}

template <typename T>
void vector<T>::reserve(size_t capacity) {
    if (capacity <= d_capacity) {
        return;
    }

    uint8_t* newBuffer = new uint8_t[offset*capacity];
    for(size_t i = 0; i < d_size; ++i) {
        new (newBuffer + i * offset) T{this->operator[](i)};
    }
    const auto size = d_size;
    clear();
    d_size = size;
    d_buffer = newBuffer;
}

template <typename T>
void vector<T>::clear() {
    if (!d_buffer) {
        return;
    }
    for (size_t i = 0; i < d_size; ++i) {
        this->operator[](i).~T();
    }
    d_size = 0;
    delete[] d_buffer;
    d_buffer = nullptr;
}

template <typename T>
vector<T>::~vector() {
    clear();
}
} // close namespace my
