#pragma once

#include "Product.h"

#include <memory>
#include <vector>

class Warehouse;

class ConstWarehouseIterator {
public:
    const Product& operator*() const;
    ConstWarehouseIterator& operator++();
    bool operator==(const ConstWarehouseIterator& other) const;
    bool operator!=(const ConstWarehouseIterator& other) const;

private:
    using Iterator = std::vector<std::unique_ptr<Product>>::const_iterator;

    ConstWarehouseIterator(Iterator current, Iterator end);
    Iterator current_;
    Iterator end_;

    friend class Warehouse;
};
