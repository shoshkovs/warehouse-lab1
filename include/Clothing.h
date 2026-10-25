#pragma once

#include "Product.h"

class Clothing : public Product {
public:
    Clothing(const std::string& name,
             const Price& price,
             const Quantity& quantity,
             const Weight& weight);
    Clothing(int id,
             const std::string& name,
             const Price& price,
             const Quantity& quantity,
             const Weight& weight);
};
