#include "Price.h"

#include "ProductFactory.h"

#include "Warehouse.h"

#include <exception>

#include <iostream>

#include <utility>

#include <vector>

void printWarehouse(Warehouse& warehouse) {

    WarehouseIterator iterator = warehouse.begin();

    while (iterator != warehouse.end()) {

        std::cout << "  " << (*iterator).getInfo() << '\n';

        ++iterator;

    }

}

void scenario1() {

    std::cout << "Scenario 1: factories and iterator\n";

    Warehouse warehouse(6);

    SmartphoneFactory smartphoneFactory;

    LaptopFactory laptopFactory;

    TShirtFactory tshirtFactory;

    JacketFactory jacketFactory;

    MilkFactory milkFactory;

    BreadFactory breadFactory;

    warehouse.addProduct(

        smartphoneFactory.createProduct(1, "Smartphone", 800, 5, 0.2));

    warehouse.addProduct(

        laptopFactory.createProduct(2, "Laptop", 1500, 3, 1.7));

    warehouse.addProduct(

        tshirtFactory.createProduct(3, "T-Shirt", 40, 10, 0.3));

    warehouse.addProduct(

        jacketFactory.createProduct(4, "Jacket", 120, 6, 0.9));

    warehouse.addProduct(

        milkFactory.createProduct(5, "Milk", 3, 20, 1.0));

    warehouse.addProduct(

        breadFactory.createProduct(6, "Bread", 2, 15, 0.5));

    printWarehouse(warehouse);

}

void scenario2() {

    std::cout << "Scenario 2: deep copy\n";

    SmartphoneFactory factory;

    Warehouse original(2);

    original.addProduct(factory.createProduct(10, "Phone", 700, 4, 0.2));

    Warehouse copy(original);

    copy.findById(10)->changeQuantity(3);

    copy.findById(10)->setPrice(Price(750));

    std::cout << "  Original: " << original.findById(10)->getInfo() << '\n';

    std::cout << "  Copy:     " << copy.findById(10)->getInfo() << '\n';

}

void scenario3() {

    std::cout << "Scenario 3: move constructor\n";

    LaptopFactory factory;

    Warehouse source(2);

    source.addProduct(factory.createProduct(20, "Laptop", 1200, 2, 1.5));

    Warehouse moved(std::move(source));

    std::cout << "  Source size: " << source.getSize() << '\n';

    std::cout << "  Moved size: " << moved.getSize() << '\n';

}

void scenario4() {

    std::cout << "Scenario 4: search and removal\n";

    Warehouse warehouse(4);

    SmartphoneFactory smartphoneFactory;

    LaptopFactory laptopFactory;

    BreadFactory breadFactory;

    warehouse.addProduct(

        smartphoneFactory.createProduct(30, "Phone", 500, 3, 0.2));

    warehouse.addProduct(

        laptopFactory.createProduct(31, "Laptop", 1000, 2, 1.4));

    warehouse.addProduct(

        breadFactory.createProduct(32, "Bread", 2, 8, 0.5));

    Product* foundById = warehouse.findById(31);

    std::vector<Product*> electronics =

        warehouse.findByCategory("Electronics");

    std::vector<Product*> priceMatches = warehouse.findByPrice(Price(2));

    std::cout << "  Found by ID: " << foundById->getName() << '\n';

    std::cout << "  Electronics: " << electronics.size() << '\n';

    std::cout << "  Products with price 2: " << priceMatches.size() << '\n';

    warehouse.removeById(31);

    warehouse.removeByIndex(0);

    std::cout << "  Size after removal: " << warehouse.getSize() << '\n';

}

void scenario5() {

    std::cout << "Scenario 5: product transfer\n";

    MilkFactory factory;

    Warehouse first(2);

    Warehouse second(2);

    first.addProduct(factory.createProduct(40, "Milk", 3, 10, 1.0));

    Product* milk = first.findById(40);

    milk->transferTo(second);

    milk->changeQuantity(-2);

    milk->setPrice(Price(4));

    std::cout << "  First warehouse size: " << first.getSize() << '\n';

    std::cout << "  Second warehouse: " << milk->getInfo() << '\n';

}

int main() {

    try {

        scenario1();

        scenario2();

        scenario3();

        scenario4();

        scenario5();

        return 0;

    } catch (const std::exception& exception) {

        std::cerr << "Error: " << exception.what() << '\n';

        return 1;

    }

}
