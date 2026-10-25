#pragma once

#include "Electronics.h"

class Smartphone : public Electronics {
public:
    Smartphone(const std::string& name,
               const Price& price,
               const Quantity& quantity,
               const Weight& weight);
    Smartphone(int id,
               const std::string& name,
               const Price& price,
               const Quantity& quantity,
               const Weight& weight);

    std::unique_ptr<Product> clone() const override;
    std::string getInfo() const override;
    void transferTo(Warehouse& other) override;
};
