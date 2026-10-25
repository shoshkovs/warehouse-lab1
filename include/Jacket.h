#pragma once

#include "Clothing.h"

class Jacket : public Clothing {

public:

    Jacket(const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight);

    Jacket(int id,

           const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight);

    std::unique_ptr<Product> clone() const override;

    std::string getInfo() const override;

    void transferTo(Warehouse& other) override;

};
