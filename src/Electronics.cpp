#include "Electronics.h"

Electronics::Electronics(const std::string& name,
                         const Price& price,
                         const Quantity& quantity,
                         const Weight& weight)
    : Product(name, price, quantity, weight, "Electronics") {}

Electronics::Electronics(int id,
                         const std::string& name,
                         const Price& price,
                         const Quantity& quantity,
                         const Weight& weight)
    : Product(id, name, price, quantity, weight, "Electronics") {}
