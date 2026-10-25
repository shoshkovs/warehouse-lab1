#pragma once

#include "Clothing.h"

class TShirt : public Clothing {

public:

    TShirt(const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight);

    TShirt(int id,

           const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight);

    std::unique_ptr<Product> clone() const override;

    std::string getInfo() const override;

    void transferTo(Warehouse& other) override;

};
