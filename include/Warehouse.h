#pragma once

#include "ConstWarehouseIterator.h"
#include "Price.h"
#include "Product.h"
#include "WarehouseIterator.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Warehouse {
public:
    explicit Warehouse(std::size_t maxSize);
    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;
    ~Warehouse();

    void addProduct(std::unique_ptr<Product> product);
    bool removeById(int id);
    bool removeByIndex(std::size_t index);

    Product* findById(int id);
    const Product* findById(int id) const;
    std::vector<Product*> findByCategory(const std::string& category);
    std::vector<const Product*> findByCategory(
        const std::string& category) const;
    std::vector<Product*> findByPrice(const Price& price);
    std::vector<const Product*> findByPrice(const Price& price) const;

    std::size_t getSize() const;
    std::size_t getMaxSize() const;

    WarehouseIterator begin();
    WarehouseIterator end();
    ConstWarehouseIterator begin() const;
    ConstWarehouseIterator end() const;

private:
    void transferProduct(int id, Warehouse& other);
    void updateOwners();

    std::vector<std::unique_ptr<Product>> products_;
    std::size_t maxSize_;
    std::size_t currentSize_;

    friend class Product;
};
