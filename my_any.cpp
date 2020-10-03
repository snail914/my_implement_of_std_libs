#include "my_any.h"

namespace my {

any::any()
: d_item_p {nullptr}
, d_deleter_p {nullptr}
{
}

any::~any() {
    if (d_deleter_p) {
        d_deleter_p(d_item_p);
    }
}

bool any::has_value() const {
    return d_item_p;
}

}

