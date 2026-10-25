#pragma once

#include "Product.h"

#include <memory>
#include <vector>

class Warehouse;

class WarehouseIterator {
public:
    Product& operator*() const;
    WarehouseIterator& operator++();
    bool operator==(const WarehouseIterator& other) const;
    bool operator!=(const WarehouseIterator& other) const;

private:
    using Iterator = std::vector<std::unique_ptr<Product>>::iterator;

    WarehouseIterator(Iterator current, Iterator end);
    Iterator current_;
    Iterator end_;

    friend class Warehouse;
};
