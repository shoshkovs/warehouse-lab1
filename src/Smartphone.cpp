#include "Smartphone.h"

#include <memory>

Smartphone::Smartphone(const std::string& name,

                       const Price& price,

                       const Quantity& quantity,

                       const Weight& weight)

    : Electronics(name, price, quantity, weight) {}

Smartphone::Smartphone(int id,

                       const std::string& name,

                       const Price& price,

                       const Quantity& quantity,

                       const Weight& weight)

    : Electronics(id, name, price, quantity, weight) {}

std::unique_ptr<Product> Smartphone::clone() const {

    return std::make_unique<Smartphone>(*this);

}

std::string Smartphone::getInfo() const {

    return makeInfo("Smartphone");

}

void Smartphone::transferTo(Warehouse& other) {

    transferToWarehouse(other);

}
