#include "Milk.h"

#include <memory>

Milk::Milk(const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight)

    : Food(name, price, quantity, weight) {}

Milk::Milk(int id,

           const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight)

    : Food(id, name, price, quantity, weight) {}

std::unique_ptr<Product> Milk::clone() const {

    return std::make_unique<Milk>(*this);

}

std::string Milk::getInfo() const {

    return makeInfo("Milk");

}

void Milk::transferTo(Warehouse& other) {

    transferToWarehouse(other);

}
