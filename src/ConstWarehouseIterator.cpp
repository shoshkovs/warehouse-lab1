#include "ConstWarehouseIterator.h"

ConstWarehouseIterator::ConstWarehouseIterator(Iterator current, Iterator end)

    : current_(current), end_(end) {}

const Product& ConstWarehouseIterator::operator*() const {

    return **current_;

}

ConstWarehouseIterator& ConstWarehouseIterator::operator++() {

    if (current_ != end_) {

        ++current_;

    }

    return *this;

}

bool ConstWarehouseIterator::operator==(

    const ConstWarehouseIterator& other) const {

    return current_ == other.current_;

}

bool ConstWarehouseIterator::operator!=(

    const ConstWarehouseIterator& other) const {

    return current_ != other.current_;

}
