#include "Product.h"

#include "LoggingProxy.h"

#include "Warehouse.h"

#include <sstream>

#include <stdexcept>

int Product::nextId_ = 1;

Product::Product(const std::string& name,

                 const Price& price,

                 const Quantity& quantity,

                 const Weight& weight,

                 const std::string& category)

    : Product(nextId_++, name, price, quantity, weight, category) {}

Product::Product(int id,

                 const std::string& name,

                 const Price& price,

                 const Quantity& quantity,

                 const Weight& weight,

                 const std::string& category)

    : id_(id),

      name_(name),

      price_(price),

      quantity_(quantity),

      weight_(weight),

      category_(category),

      warehouse_(nullptr) {

    if (id <= 0) {

        throw std::invalid_argument("Product ID must be positive");

    }

    if (name.empty()) {

        throw std::invalid_argument("Product name cannot be empty");

    }

    if (id >= nextId_) {

        nextId_ = id + 1;

    }

}

Product::Product(const Product& other)

    : id_(other.id_),

      name_(other.name_),

      price_(other.price_),

      quantity_(other.quantity_),

      weight_(other.weight_),

      category_(other.category_),

      warehouse_(nullptr) {}

Product::~Product() = default;

int Product::getId() const {

    return id_;

}

const std::string& Product::getName() const {

    return name_;

}

const Price& Product::getPrice() const {

    return price_;

}

const Quantity& Product::getQuantity() const {

    return quantity_;

}

const Weight& Product::getWeight() const {

    return weight_;

}

const std::string& Product::getCategory() const {

    return category_;

}

void Product::changeQuantity(int delta) {

    quantity_.change(delta);

    LoggingProxy::log("PRODUCT", "change quantity", name_);

}

void Product::setPrice(const Price& newPrice) {

    price_ = newPrice;

    LoggingProxy::log("PRODUCT", "set price", name_);

}

std::string Product::makeInfo(const std::string& type) const {

    std::ostringstream output;

    output << type << " | id=" << id_ << " | name=" << name_

           << " | price=" << price_.getValue()

           << " | quantity=" << quantity_.getValue()

           << " | weight=" << weight_.getValue();

    return output.str();

}

void Product::transferToWarehouse(Warehouse& other) {

    if (warehouse_ == nullptr) {

        throw std::logic_error("Product does not belong to a warehouse");

    }

    warehouse_->transferProduct(id_, other);

    LoggingProxy::log("PRODUCT", "transfer", name_);

}

void Product::setWarehouse(Warehouse* warehouse) {

    warehouse_ = warehouse;

}
