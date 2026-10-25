#include "Jacket.h"

#include <memory>

Jacket::Jacket(const std::string& name,

               const Price& price,

               const Quantity& quantity,

               const Weight& weight)

    : Clothing(name, price, quantity, weight) {}

Jacket::Jacket(int id,

               const std::string& name,

               const Price& price,

               const Quantity& quantity,

               const Weight& weight)

    : Clothing(id, name, price, quantity, weight) {}

std::unique_ptr<Product> Jacket::clone() const {

    return std::make_unique<Jacket>(*this);

}

std::string Jacket::getInfo() const {

    return makeInfo("Jacket");

}

void Jacket::transferTo(Warehouse& other) {

    transferToWarehouse(other);

}
