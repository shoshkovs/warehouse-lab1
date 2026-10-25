#pragma once

#include "Price.h"
#include "Quantity.h"
#include "Weight.h"

#include <memory>
#include <string>

class Warehouse;

class Product {
public:
    Product(const std::string& name,
            const Price& price,
            const Quantity& quantity,
            const Weight& weight,
            const std::string& category);
    Product(int id,
            const std::string& name,
            const Price& price,
            const Quantity& quantity,
            const Weight& weight,
            const std::string& category);
    Product(const Product& other);
    virtual ~Product();

    int getId() const;
    const std::string& getName() const;
    const Price& getPrice() const;
    const Quantity& getQuantity() const;
    const Weight& getWeight() const;
    const std::string& getCategory() const;

    void changeQuantity(int delta);
    void setPrice(const Price& newPrice);

    virtual std::unique_ptr<Product> clone() const = 0;
    virtual std::string getInfo() const = 0;
    virtual void transferTo(Warehouse& other) = 0;

protected:
    std::string makeInfo(const std::string& type) const;
    void transferToWarehouse(Warehouse& other);

private:
    void setWarehouse(Warehouse* warehouse);

    static int nextId_;
    int id_;
    std::string name_;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::string category_;
    Warehouse* warehouse_;

    friend class Warehouse;
};
