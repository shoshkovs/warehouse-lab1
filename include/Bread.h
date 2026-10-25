#pragma once

#include "Food.h"

class Bread : public Food {
public:
    Bread(const std::string& name,
          const Price& price,
          const Quantity& quantity,
          const Weight& weight);
    Bread(int id,
          const std::string& name,
          const Price& price,
          const Quantity& quantity,
          const Weight& weight);

    std::unique_ptr<Product> clone() const override;
    std::string getInfo() const override;
    void transferTo(Warehouse& other) override;
};
