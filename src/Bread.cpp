#include "Bread.h"

#include <memory>

Bread::Bread(const std::string& name,
             const Price& price,
             const Quantity& quantity,
             const Weight& weight)
    : Food(name, price, quantity, weight) {}

Bread::Bread(int id,
             const std::string& name,
             const Price& price,
             const Quantity& quantity,
             const Weight& weight)
    : Food(id, name, price, quantity, weight) {}

std::unique_ptr<Product> Bread::clone() const {
    return std::make_unique<Bread>(*this);
}

std::string Bread::getInfo() const {
    return makeInfo("Bread");
}

void Bread::transferTo(Warehouse& other) {
    transferToWarehouse(other);
}
