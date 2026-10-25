#include "Laptop.h"

#include <memory>

Laptop::Laptop(const std::string& name,

               const Price& price,

               const Quantity& quantity,

               const Weight& weight)

    : Electronics(name, price, quantity, weight) {}

Laptop::Laptop(int id,

               const std::string& name,

               const Price& price,

               const Quantity& quantity,

               const Weight& weight)

    : Electronics(id, name, price, quantity, weight) {}

std::unique_ptr<Product> Laptop::clone() const {

    return std::make_unique<Laptop>(*this);

}

std::string Laptop::getInfo() const {

    return makeInfo("Laptop");

}

void Laptop::transferTo(Warehouse& other) {

    transferToWarehouse(other);

}
