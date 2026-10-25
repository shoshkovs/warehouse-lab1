#include "Quantity.h"

#include <stdexcept>

Quantity::Quantity(int value) {
    setValue(value);
}

int Quantity::getValue() const {
    return value_;
}

void Quantity::setValue(int value) {
    if (value < 0) {
        throw std::invalid_argument("Quantity cannot be negative");
    }
    value_ = value;
}

void Quantity::change(int delta) {
    setValue(value_ + delta);
}
