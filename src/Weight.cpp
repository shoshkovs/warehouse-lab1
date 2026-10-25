#include "Weight.h"

#include <stdexcept>

Weight::Weight(double value) {

    setValue(value);

}

double Weight::getValue() const {

    return value_;

}

void Weight::setValue(double value) {

    if (value < 0.0) {

        throw std::invalid_argument("Weight cannot be negative");

    }

    value_ = value;

}
