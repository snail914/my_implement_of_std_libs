#include "my_any.h"

namespace my {

any::any()
: d_item_p {nullptr}
, d_deleter_p {nullptr}
, d_copier_p {nullptr}
{
}

any::any(any&& val)
: d_item_p {val.d_item_p}
, d_deleter_p {val.d_deleter_p}
, d_copier_p {val.d_copier_p}
{
    val.d_item_p = nullptr;
    val.d_deleter_p = nullptr;
    val.d_copier_p = nullptr;
}

any::any(const any& val)
: any()
{
    if (val.has_value()) {
        d_deleter_p = val.d_deleter_p;
        d_copier_p = val.d_copier_p;
        d_item_p = val.d_copier_p(val.d_item_p);
    }
}

any& any::operator=(any&& val) {
    if (&val == this) {
        return *this;
    }
    if (val.has_value()) {
        d_item_p = val.d_item_p;
        d_deleter_p = val.d_deleter_p;
        d_copier_p = val.d_copier_p;
        val.d_item_p = nullptr;
        val.d_deleter_p = nullptr;
        val.d_copier_p = nullptr;
    }
    else {
        reset();
    }
    return *this;
}

any& any::operator=(const any& val) {
    if (&val == this) {
        return *this;
    }
    if (val.has_value()) {
        d_deleter_p = val.d_deleter_p;
        d_copier_p = val.d_copier_p;
        d_item_p = val.d_copier_p(val.d_item_p);
    }
    else {
        reset();
    }
    return *this;
}

any::~any() {
    reset();
}

bool any::has_value() const {
    return d_item_p;
}

void any::reset() {
    if (d_item_p) {
        d_deleter_p(d_item_p);
        d_item_p = nullptr;
        d_deleter_p = nullptr;
        d_copier_p = nullptr;
    }
}
}

