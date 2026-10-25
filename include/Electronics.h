#pragma once

#include "Product.h"

class Electronics : public Product {

public:

    Electronics(const std::string& name,

                const Price& price,

                const Quantity& quantity,

                const Weight& weight);

    Electronics(int id,

                const std::string& name,

                const Price& price,

                const Quantity& quantity,

                const Weight& weight);

};
