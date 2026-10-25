#pragma once

#include "Product.h"

class Food : public Product {

public:

    Food(const std::string& name,

         const Price& price,

         const Quantity& quantity,

         const Weight& weight);

    Food(int id,

         const std::string& name,

         const Price& price,

         const Quantity& quantity,

         const Weight& weight);

};
