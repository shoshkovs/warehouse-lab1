#include "WarehouseIterator.h"

WarehouseIterator::WarehouseIterator(Iterator current, Iterator end)
    : current_(current), end_(end) {}

Product& WarehouseIterator::operator*() const {
    return **current_;
}

WarehouseIterator& WarehouseIterator::operator++() {
    if (current_ != end_) {
        ++current_;
    }
    return *this;
}

bool WarehouseIterator::operator==(const WarehouseIterator& other) const {
    return current_ == other.current_;
}

bool WarehouseIterator::operator!=(const WarehouseIterator& other) const {
    return current_ != other.current_;
}
