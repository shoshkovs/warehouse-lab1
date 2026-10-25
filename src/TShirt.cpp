#include "TShirt.h"

#include <memory>

TShirt::TShirt(const std::string& name,

               const Price& price,

               const Quantity& quantity,

               const Weight& weight)

    : Clothing(name, price, quantity, weight) {}

TShirt::TShirt(int id,

               const std::string& name,

               const Price& price,

               const Quantity& quantity,

               const Weight& weight)

    : Clothing(id, name, price, quantity, weight) {}

std::unique_ptr<Product> TShirt::clone() const {

    return std::make_unique<TShirt>(*this);

}

std::string TShirt::getInfo() const {

    return makeInfo("TShirt");

}

void TShirt::transferTo(Warehouse& other) {

    transferToWarehouse(other);

}
