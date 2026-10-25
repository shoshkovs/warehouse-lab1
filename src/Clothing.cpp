#include "Clothing.h"

Clothing::Clothing(const std::string& name,
                   const Price& price,
                   const Quantity& quantity,
                   const Weight& weight)
    : Product(name, price, quantity, weight, "Clothing") {}

Clothing::Clothing(int id,
                   const std::string& name,
                   const Price& price,
                   const Quantity& quantity,
                   const Weight& weight)
    : Product(id, name, price, quantity, weight, "Clothing") {}
