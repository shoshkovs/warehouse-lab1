#include "Console.h"

#include "ProductFactory.h"
#include "Warehouse.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool readInteger(const std::string& prompt, int& value,
                 int minimum, int maximum) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            return false;
        }
        std::istringstream input(line);
        int number;
        char extra;
        if ((input >> number) && !(input >> extra) &&
            number >= minimum && number <= maximum) {
            value = number;
            return true;
        }
        std::cout << "Enter an integer from " << minimum
                  << " to " << maximum << ".\n";
    }
}

bool readWeight(double& value) {
    std::string line;
    while (true) {
        std::cout << "Weight: ";
        if (!std::getline(std::cin, line)) {
            return false;
        }
        std::istringstream input(line);
        double number;
        char extra;
        if ((input >> number) && !(input >> extra) &&
            std::isfinite(number) && number >= 0.0) {
            value = number;
            return true;
        }
        std::cout << "Enter a finite non-negative weight.\n";
    }
}

bool readName(std::string& name) {
    while (true) {
        std::cout << "Name: ";
        if (!std::getline(std::cin, name)) {
            return false;
        }
        std::size_t first = name.find_first_not_of(" \t\r");
        if (first != std::string::npos) {
            std::size_t last = name.find_last_not_of(" \t\r");
            name = name.substr(first, last - first + 1);
            return true;
        }
        std::cout << "Name cannot be empty.\n";
    }
}

void printProducts(const Warehouse& warehouse) {
    if (warehouse.getSize() == 0) {
        std::cout << "Warehouse is empty.\n";
        return;
    }
    ConstWarehouseIterator iterator = warehouse.begin();
    while (iterator != warehouse.end()) {
        std::cout << (*iterator).getInfo() << '\n';
        ++iterator;
    }
}

bool addFromConsole(Warehouse& warehouse) {
    if (warehouse.getSize() >= warehouse.getMaxSize()) {
        throw std::overflow_error("Warehouse is full");
    }
    const int maxInteger = std::numeric_limits<int>::max();
    int type, id, price, quantity;
    double weight;
    std::string name;
    std::cout << "1. Smartphone\n2. Laptop\n3. TShirt\n"
                 "4. Jacket\n5. Milk\n6. Bread\n";
    if (!readInteger("Product type: ", type, 1, 6) ||
        !readInteger("ID: ", id, 1, maxInteger - 1) ||
        !readName(name) ||
        !readInteger("Price: ", price, 0, maxInteger) ||
        !readInteger("Quantity: ", quantity, 0, maxInteger) ||
        !readWeight(weight)) {
        return false;
    }

    SmartphoneFactory smartphone;
    LaptopFactory laptop;
    TShirtFactory tshirt;
    JacketFactory jacket;
    MilkFactory milk;
    BreadFactory bread;
    ProductFactory* factory = nullptr;
    switch (type) {
        case 1: factory = &smartphone; break;
        case 2: factory = &laptop; break;
        case 3: factory = &tshirt; break;
        case 4: factory = &jacket; break;
        case 5: factory = &milk; break;
        case 6: factory = &bread; break;
        default: throw std::invalid_argument("Unknown product type");
    }
    warehouse.addProduct(
        factory->createProduct(id, name, price, quantity, weight));
    std::cout << "Added product ID " << id << ".\n";
    return true;
}

bool removeFromConsole(Warehouse& warehouse) {
    int method, value;
    std::cout << "1. Remove by ID\n2. Remove by index (starting at 0)\n";
    if (!readInteger("Method: ", method, 1, 2) ||
        !readInteger(method == 1 ? "ID: " : "Index: ", value,
                     method == 1 ? 1 : 0,
                     std::numeric_limits<int>::max() - 1)) {
        return false;
    }
    if (method == 1) {
        if (!warehouse.removeById(value)) {
            throw std::invalid_argument("Product ID not found");
        }
        std::cout << "Removed product ID " << value << ".\n";
    } else {
        warehouse.removeByIndex(static_cast<std::size_t>(value));
        std::cout << "Removed product at index " << value << ".\n";
    }
    return true;
}

bool findFromConsole(Warehouse& warehouse) {
    const int maxInteger = std::numeric_limits<int>::max();
    int method, value;
    std::cout << "1. Find by ID\n2. Find by category\n3. Find by price\n";
    if (!readInteger("Method: ", method, 1, 3)) {
        return false;
    }
    if (method == 1) {
        if (!readInteger("ID: ", value, 1, maxInteger - 1)) {
            return false;
        }
        Product* product = warehouse.findById(value);
        if (product == nullptr) {
            throw std::invalid_argument("Product ID not found");
        }
        std::cout << product->getInfo() << '\n';
        return true;
    }

    std::vector<Product*> matches;
    if (method == 2) {
        std::cout << "1. Electronics\n2. Clothing\n3. Food\n";
        if (!readInteger("Category: ", value, 1, 3)) {
            return false;
        }
        std::string category;
        switch (value) {
            case 1: category = "Electronics"; break;
            case 2: category = "Clothing"; break;
            case 3: category = "Food"; break;
        }
        matches = warehouse.findByCategory(category);
    } else {
        if (!readInteger("Price: ", value, 0, maxInteger)) {
            return false;
        }
        matches = warehouse.findByPrice(Price(value));
    }
    std::cout << "Found " << matches.size() << " product(s).\n";
    for (Product* product : matches) {
        std::cout << product->getInfo() << '\n';
    }
    return true;
}

bool editFromConsole(Warehouse& warehouse) {
    const int maxInteger = std::numeric_limits<int>::max();
    int id, method, value;
    if (!readInteger("ID: ", id, 1, maxInteger - 1)) {
        return false;
    }
    Product* product = warehouse.findById(id);
    if (product == nullptr) {
        throw std::invalid_argument("Product ID not found");
    }
    std::cout << "1. Set price\n2. Change quantity\n";
    if (!readInteger("Action: ", method, 1, 2)) {
        return false;
    }
    if (method == 1) {
        if (!readInteger("New price: ", value, 0, maxInteger)) {
            return false;
        }
        product->setPrice(Price(value));
    } else {
        if (!readInteger("Quantity delta: ", value,
                         std::numeric_limits<int>::min(), maxInteger)) {
            return false;
        }
        int current = product->getQuantity().getValue();
        if (value < -current ||
            (value > 0 && current > maxInteger - value)) {
            throw std::invalid_argument("Quantity change is out of range");
        }
        product->changeQuantity(value);
    }
    std::cout << "Updated product ID " << id << ".\n";
    return true;
}

bool transferFromConsole(Warehouse& source, Warehouse& target) {
    int id;
    if (!readInteger("ID: ", id, 1, std::numeric_limits<int>::max() - 1)) {
        return false;
    }
    Product* product = source.findById(id);
    if (product == nullptr) {
        throw std::invalid_argument("Product ID not found");
    }
    product->transferTo(target);
    std::cout << "Transferred product ID " << id << ".\n";
    return true;
}

int runConsole() {
    int firstCapacity, secondCapacity;
    const int maxInteger = std::numeric_limits<int>::max();
    std::cout << "Warehouse menu\nData is kept only until exit.\n";
    if (!readInteger("Warehouse 1 capacity: ", firstCapacity, 1, maxInteger) ||
        !readInteger("Warehouse 2 capacity: ", secondCapacity, 1, maxInteger)) {
        return 0;
    }
    Warehouse first(firstCapacity);
    Warehouse second(secondCapacity);
    Warehouse* active = &first;
    bool running = true;
    while (running) {
        std::cout << "\nActive warehouse: " << (active == &first ? 1 : 2)
                  << "\nProducts: " << active->getSize() << " / "
                  << active->getMaxSize()
                  << "\n1. Show products\n2. Add product\n3. Remove product\n"
                     "4. Find product\n5. Edit product\n"
                     "6. Transfer to the other warehouse\n"
                     "7. Switch warehouse\n8. Copy to the other warehouse\n0. Exit\n";
        int command;
        if (!readInteger("Command: ", command, 0, 8)) {
            break;
        }
        try {
            switch (command) {
                case 0: running = false; break;
                case 1: printProducts(*active); break;
                case 2: running = addFromConsole(*active); break;
                case 3: running = removeFromConsole(*active); break;
                case 4: running = findFromConsole(*active); break;
                case 5: running = editFromConsole(*active); break;
                case 6:
                    running = transferFromConsole(
                        *active, active == &first ? second : first);
                    break;
                case 7: active = active == &first ? &second : &first; break;
                case 8: {
                    int confirmation;
                    if (!readInteger("Replace the other warehouse contents and capacity? (1=yes, 0=no): ",
                                     confirmation, 0, 1)) {
                        running = false;
                        break;
                    }
                    if (confirmation == 1) {
                        Warehouse& target = active == &first ? second : first;
                        target = *active;
                        std::cout << "Warehouse copied.\n";
                    } else {
                        std::cout << "Copy cancelled.\n";
                    }
                    break;
                }
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }
    std::cout << "Goodbye.\n";
    return 0;
}
