#pragma once

#include "Food.h"

class Milk : public Food {
public:
    Milk(const std::string& name,
         const Price& price,
         const Quantity& quantity,
         const Weight& weight);
    Milk(int id,
         const std::string& name,
         const Price& price,
         const Quantity& quantity,
         const Weight& weight);

    std::unique_ptr<Product> clone() const override;
    std::string getInfo() const override;
    void transferTo(Warehouse& other) override;
};
