#include "Warehouse.h"

#include "LoggingProxy.h"

#include <stdexcept>
#include <utility>

Warehouse::Warehouse(std::size_t maxSize)
    : maxSize_(maxSize), currentSize_(0) {
    if (maxSize == 0) {
        throw std::invalid_argument("Warehouse size must be positive");
    }
}

Warehouse::Warehouse(const Warehouse& other)
    : maxSize_(other.maxSize_), currentSize_(other.currentSize_) {
    for (const std::unique_ptr<Product>& product : other.products_) {
        products_.push_back(product->clone());
    }
    updateOwners();
    LoggingProxy::log("WAREHOUSE", "copy constructor", "success");
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this == &other) {
        return *this;
    }

    std::vector<std::unique_ptr<Product>> copies;
    for (const std::unique_ptr<Product>& product : other.products_) {
        copies.push_back(product->clone());
    }
    products_ = std::move(copies);
    maxSize_ = other.maxSize_;
    currentSize_ = other.currentSize_;
    updateOwners();
    LoggingProxy::log("WAREHOUSE", "copy assignment", "success");
    return *this;
}

Warehouse::Warehouse(Warehouse&& other) noexcept
    : products_(std::move(other.products_)),
      maxSize_(other.maxSize_),
      currentSize_(other.currentSize_) {
    other.currentSize_ = 0;
    updateOwners();
    LoggingProxy::log("WAREHOUSE", "move constructor", "success");
}

Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    products_ = std::move(other.products_);
    maxSize_ = other.maxSize_;
    currentSize_ = other.currentSize_;
    other.currentSize_ = 0;
    updateOwners();
    LoggingProxy::log("WAREHOUSE", "move assignment", "success");
    return *this;
}

Warehouse::~Warehouse() = default;

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (product == nullptr) {
        throw std::invalid_argument("Product cannot be null");
    }
    if (currentSize_ >= maxSize_) {
        throw std::overflow_error("Warehouse is full");
    }
    if (findById(product->getId()) != nullptr) {
        throw std::invalid_argument("Product ID already exists");
    }
    product->setWarehouse(this);
    LoggingProxy::log("WAREHOUSE", "add", product->getName());
    products_.push_back(std::move(product));
    ++currentSize_;
}

bool Warehouse::removeById(int id) {
    for (std::size_t index = 0; index < products_.size(); ++index) {
        if (products_[index]->getId() == id) {
            products_[index]->setWarehouse(nullptr);
            LoggingProxy::log("WAREHOUSE", "remove by id", std::to_string(id));
            products_.erase(products_.begin() + static_cast<std::ptrdiff_t>(index));
            --currentSize_;
            return true;
        }
    }
    return false;
}

bool Warehouse::removeByIndex(std::size_t index) {
    if (index >= products_.size()) {
        throw std::out_of_range("Product index is out of range");
    }
    products_[index]->setWarehouse(nullptr);
    LoggingProxy::log("WAREHOUSE", "remove by index", std::to_string(index));
    products_.erase(products_.begin() + static_cast<std::ptrdiff_t>(index));
    --currentSize_;
    return true;
}

Product* Warehouse::findById(int id) {
    for (const std::unique_ptr<Product>& product : products_) {
        if (product->getId() == id) {
            LoggingProxy::log("WAREHOUSE", "find by id", "found");
            return product.get();
        }
    }
    LoggingProxy::log("WAREHOUSE", "find by id", "not found");
    return nullptr;
}

const Product* Warehouse::findById(int id) const {
    for (const std::unique_ptr<Product>& product : products_) {
        if (product->getId() == id) {
            LoggingProxy::log("WAREHOUSE", "find by id", "found");
            return product.get();
        }
    }
    LoggingProxy::log("WAREHOUSE", "find by id", "not found");
    return nullptr;
}

std::vector<Product*> Warehouse::findByCategory(const std::string& category) {
    std::vector<Product*> result;
    for (const std::unique_ptr<Product>& product : products_) {
        if (product->getCategory() == category) {
            result.push_back(product.get());
        }
    }
    LoggingProxy::log("WAREHOUSE", "find by category",
                      std::to_string(result.size()));
    return result;
}

std::vector<const Product*> Warehouse::findByCategory(
    const std::string& category) const {
    std::vector<const Product*> result;
    for (const std::unique_ptr<Product>& product : products_) {
        if (product->getCategory() == category) {
            result.push_back(product.get());
        }
    }
    LoggingProxy::log("WAREHOUSE", "find by category",
                      std::to_string(result.size()));
    return result;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) {
    std::vector<Product*> result;
    for (const std::unique_ptr<Product>& product : products_) {
        if (product->getPrice().getValue() == price.getValue()) {
            result.push_back(product.get());
        }
    }
    LoggingProxy::log("WAREHOUSE", "find by price",
                      std::to_string(result.size()));
    return result;
}

std::vector<const Product*> Warehouse::findByPrice(const Price& price) const {
    std::vector<const Product*> result;
    for (const std::unique_ptr<Product>& product : products_) {
        if (product->getPrice().getValue() == price.getValue()) {
            result.push_back(product.get());
        }
    }
    LoggingProxy::log("WAREHOUSE", "find by price",
                      std::to_string(result.size()));
    return result;
}

std::size_t Warehouse::getSize() const {
    return currentSize_;
}

std::size_t Warehouse::getMaxSize() const {
    return maxSize_;
}

WarehouseIterator Warehouse::begin() {
    return WarehouseIterator(products_.begin(), products_.end());
}

WarehouseIterator Warehouse::end() {
    return WarehouseIterator(products_.end(), products_.end());
}

ConstWarehouseIterator Warehouse::begin() const {
    return ConstWarehouseIterator(products_.begin(), products_.end());
}

ConstWarehouseIterator Warehouse::end() const {
    return ConstWarehouseIterator(products_.end(), products_.end());
}

void Warehouse::transferProduct(int id, Warehouse& other) {
    if (this == &other) {
        throw std::invalid_argument("Warehouses must be different");
    }
    if (other.currentSize_ >= other.maxSize_) {
        throw std::overflow_error("Target warehouse is full");
    }
    if (other.findById(id) != nullptr) {
        throw std::invalid_argument("Product ID already exists in target");
    }

    for (std::size_t index = 0; index < products_.size(); ++index) {
        if (products_[index]->getId() == id) {
            std::unique_ptr<Product> product = std::move(products_[index]);
            products_.erase(products_.begin() + static_cast<std::ptrdiff_t>(index));
            --currentSize_;
            product->setWarehouse(&other);
            other.products_.push_back(std::move(product));
            ++other.currentSize_;
            return;
        }
    }
    throw std::logic_error("Product is not stored in this warehouse");
}

void Warehouse::updateOwners() {
    for (const std::unique_ptr<Product>& product : products_) {
        product->setWarehouse(this);
    }
}
