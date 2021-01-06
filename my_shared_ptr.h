#include <iostream>
namespace my {

class Count {
  public:
    Count(): d_val{1} {}
    int get() const { return d_val; }
    void increase() { ++d_val; }
    void decrease() { --d_val; }

  private:
    int d_val;
};

template <typename T>
class SharedPtr {
  public:
    SharedPtr()
    : d_ptr{nullptr}
    , d_count{nullptr}
    {
    }

    SharedPtr(T* ptr)
    : d_ptr{ptr}
    , d_count{new Count{}}
    {
    }

    SharedPtr(const SharedPtr& val)
    : d_ptr{val.d_ptr}
    , d_count{val.d_count}
    {
        if (d_count) {
            d_count->increase();
        }
    }

    SharedPtr(SharedPtr&& val)
    : d_ptr{val.d_ptr}
    , d_count{val.d_count}
    {
        val.d_ptr = nullptr;
        val.d_count = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& rhs)
    {
        if (&rhs == this) {
            return *this;
        }
        release();
        d_ptr = rhs.d_ptr;
        d_count = rhs.d_count;
        if (d_count) {
            d_count->increase();
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& rhs)
    {
        if (&rhs == this) {
            return *this;
        }
        release();
        d_ptr = rhs.d_ptr;
        d_count = rhs.d_count;
        rhs.d_ptr = nullptr;
        rhs.d_count = nullptr;
        return *this;
    }

    void release() {
        if (d_count != nullptr) {
            d_count->decrease();
            if (d_count->get() == 0) {
                delete d_ptr;
                delete d_count;
            }
        }
        d_ptr = nullptr;
        d_count = nullptr;
    }

    int count() const noexcept {
        return d_count ? d_count->get() : 0;
    }

    ~SharedPtr() {
        release();
    }

  private:
    T*      d_ptr;
    Count*  d_count;
};

} // close namespace my
