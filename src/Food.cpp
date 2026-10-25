#include "Food.h"

Food::Food(const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight)

    : Product(name, price, quantity, weight, "Food") {}

Food::Food(int id,

           const std::string& name,

           const Price& price,

           const Quantity& quantity,

           const Weight& weight)

    : Product(id, name, price, quantity, weight, "Food") {}
