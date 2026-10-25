#include "Warehouse.h"
#include "ProductFactory.h"
#include <iostream>
#include <utility>

int main() {
    LaptopFactory factory;
    Warehouse source(2);
    source.addProduct(factory.createProduct(90, "Laptop", 1200, 2, 1.5));
    const Product* before = source.findById(90);
    Warehouse moved(std::move(source));
    bool constructorKeptAddress = moved.findById(90) == before;
    bool sourceEmpty = source.getSize() == 0;
    Warehouse assigned(1);
    assigned = std::move(moved);
    bool assignmentKeptAddress = assigned.findById(90) == before;
    bool movedEmpty = moved.getSize() == 0;
    std::cout << "move_constructor_same_address=" << constructorKeptAddress << '\n'
              << "source_size_zero=" << sourceEmpty << '\n'
              << "move_assignment_same_address=" << assignmentKeptAddress << '\n'
              << "moved_size_zero=" << movedEmpty << '\n';
    return constructorKeptAddress && sourceEmpty && assignmentKeptAddress && movedEmpty ? 0 : 1;
}
