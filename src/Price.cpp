#include "Price.h"

#include <stdexcept>

Price::Price(int value) {

    setValue(value);

}

int Price::getValue() const {

    return value_;

}

void Price::setValue(int value) {

    if (value < 0) {

        throw std::invalid_argument("Price cannot be negative");

    }

    value_ = value;

}
