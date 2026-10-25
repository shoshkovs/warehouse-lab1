#include "TestHarness.h"

#include "Bread.h"

#include "Jacket.h"

#include "Laptop.h"

#include "LoggingProxy.h"

#include "Milk.h"

#include "Price.h"

#include "ProductFactory.h"

#include "Quantity.h"

#include "Smartphone.h"

#include "TShirt.h"

#include "Warehouse.h"

#include "WarehouseIterator.h"

#include "Weight.h"

#include <exception>

#include <iostream>

#include <memory>

#include <sstream>

#include <stdexcept>

#include <string>

#include <utility>

#include <vector>

void testValueClassesValidateAndChangeValues() {

    Price price(100);

    price.setValue(150);

    check(price.getValue() == 150, "price.getValue() == 150");

    {

        bool caught = false;

        try {

            Price(-1);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    {

        bool caught = false;

        try {

            price.setValue(-1);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    Quantity quantity(5);

    quantity.change(-2);

    check(quantity.getValue() == 3, "quantity.getValue() == 3");

    quantity.setValue(10);

    check(quantity.getValue() == 10, "quantity.getValue() == 10");

    {

        bool caught = false;

        try {

            Quantity(-1);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    {

        bool caught = false;

        try {

            quantity.change(-11);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    Weight weight(0.0);

    weight.setValue(1.5);

    check(weight.getValue() == 1.5, "weight.getValue() == 1.5");

    {

        bool caught = false;

        try {

            Weight(-0.1);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    {

        bool caught = false;

        try {

            weight.setValue(-0.1);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

}

void testProductHierarchyHasExactTypesCategoriesAndIds() {

    Smartphone phone("Phone", Price(100), Quantity(2), Weight(0.2));

    Laptop laptop("Laptop", Price(200), Quantity(3), Weight(1.5));

    TShirt shirt("T-Shirt", Price(30), Quantity(4), Weight(0.3));

    Jacket jacket("Jacket", Price(80), Quantity(5), Weight(0.8));

    Milk milk("Milk", Price(3), Quantity(6), Weight(1.0));

    Bread bread("Bread", Price(2), Quantity(7), Weight(0.5));

    check(laptop.getId() == phone.getId() + 1, "laptop.getId() == phone.getId() + 1");

    check(phone.getCategory() == std::string("Electronics"),

          "phone.getCategory() == std::string(\"Electronics\")");

    check(laptop.getCategory() == std::string("Electronics"),

          "laptop.getCategory() == std::string(\"Electronics\")");

    check(shirt.getCategory() == std::string("Clothing"),

          "shirt.getCategory() == std::string(\"Clothing\")");

    check(jacket.getCategory() == std::string("Clothing"),

          "jacket.getCategory() == std::string(\"Clothing\")");

    check(milk.getCategory() == std::string("Food"), "milk.getCategory() == std::string(\"Food\")");

    check(bread.getCategory() == std::string("Food"),

          "bread.getCategory() == std::string(\"Food\")");

    check(dynamic_cast<Smartphone*>(phone.clone().get()) != nullptr,

          "dynamic_cast<Smartphone*>(phone.clone().get()) != nullptr");

    check(dynamic_cast<Laptop*>(laptop.clone().get()) != nullptr,

          "dynamic_cast<Laptop*>(laptop.clone().get()) != nullptr");

    check(dynamic_cast<TShirt*>(shirt.clone().get()) != nullptr,

          "dynamic_cast<TShirt*>(shirt.clone().get()) != nullptr");

    check(dynamic_cast<Jacket*>(jacket.clone().get()) != nullptr,

          "dynamic_cast<Jacket*>(jacket.clone().get()) != nullptr");

    check(dynamic_cast<Milk*>(milk.clone().get()) != nullptr,

          "dynamic_cast<Milk*>(milk.clone().get()) != nullptr");

    check(dynamic_cast<Bread*>(bread.clone().get()) != nullptr,

          "dynamic_cast<Bread*>(bread.clone().get()) != nullptr");

}

void testProductChangesQuantityAndPrice() {

    Smartphone phone("Phone", Price(100), Quantity(2), Weight(0.2));

    phone.changeQuantity(3);

    phone.setPrice(Price(120));

    check(phone.getQuantity().getValue() == 5, "phone.getQuantity().getValue() == 5");

    check(phone.getPrice().getValue() == 120, "phone.getPrice().getValue() == 120");

    {

        bool caught = false;

        try {

            phone.changeQuantity(-6);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    check(phone.getInfo().find("Phone") != std::string::npos,

          "phone.getInfo().find(\"Phone\") != std::string::npos");

}

void testAllFactoriesCreateTheCorrectProduct() {

    SmartphoneFactory smartphoneFactory;

    LaptopFactory laptopFactory;

    TShirtFactory tshirtFactory;

    JacketFactory jacketFactory;

    MilkFactory milkFactory;

    BreadFactory breadFactory;

    std::unique_ptr<Product> phone =

        smartphoneFactory.createProduct(101, "Phone", 100, 2, 0.2);

    std::unique_ptr<Product> laptop =

        laptopFactory.createProduct(102, "Laptop", 200, 3, 1.5);

    std::unique_ptr<Product> shirt =

        tshirtFactory.createProduct(103, "T-Shirt", 30, 4, 0.3);

    std::unique_ptr<Product> jacket =

        jacketFactory.createProduct(104, "Jacket", 80, 5, 0.8);

    std::unique_ptr<Product> milk =

        milkFactory.createProduct(105, "Milk", 3, 6, 1.0);

    std::unique_ptr<Product> bread =

        breadFactory.createProduct(106, "Bread", 2, 7, 0.5);

    check(dynamic_cast<Smartphone*>(phone.get()) != nullptr,

          "dynamic_cast<Smartphone*>(phone.get()) != nullptr");

    check(dynamic_cast<Laptop*>(laptop.get()) != nullptr,

          "dynamic_cast<Laptop*>(laptop.get()) != nullptr");

    check(dynamic_cast<TShirt*>(shirt.get()) != nullptr,

          "dynamic_cast<TShirt*>(shirt.get()) != nullptr");

    check(dynamic_cast<Jacket*>(jacket.get()) != nullptr,

          "dynamic_cast<Jacket*>(jacket.get()) != nullptr");

    check(dynamic_cast<Milk*>(milk.get()) != nullptr, "dynamic_cast<Milk*>(milk.get()) != nullptr");

    check(dynamic_cast<Bread*>(bread.get()) != nullptr,

          "dynamic_cast<Bread*>(bread.get()) != nullptr");

    check(phone->getId() == 101, "phone->getId() == 101");

    check(bread->getId() == 106, "bread->getId() == 106");

}

void testWarehouseAddsSearchesAndRemovesProducts() {

    Warehouse warehouse(6);

    SmartphoneFactory smartphoneFactory;

    LaptopFactory laptopFactory;

    BreadFactory breadFactory;

    warehouse.addProduct(

        smartphoneFactory.createProduct(201, "Phone", 100, 2, 0.2));

    warehouse.addProduct(

        laptopFactory.createProduct(202, "Laptop", 200, 3, 1.5));

    warehouse.addProduct(

        breadFactory.createProduct(203, "Bread", 100, 7, 0.5));

    check(warehouse.getSize() == 3U, "warehouse.getSize() == 3U");

    check(warehouse.getMaxSize() == 6U, "warehouse.getMaxSize() == 6U");

    check(warehouse.findById(202) != nullptr, "warehouse.findById(202) != nullptr");

    check(warehouse.findById(999) == nullptr, "warehouse.findById(999) == nullptr");

    std::vector<Product*> electronics = warehouse.findByCategory("Electronics");

    std::vector<Product*> samePrice = warehouse.findByPrice(Price(100));

    check(electronics.size() == 2U, "electronics.size() == 2U");

    check(samePrice.size() == 2U, "samePrice.size() == 2U");

    check(warehouse.removeById(202), "warehouse.removeById(202)");

    check(!warehouse.removeById(999), "!warehouse.removeById(999)");

    check(warehouse.removeByIndex(0), "warehouse.removeByIndex(0)");

    check(warehouse.getSize() == 1U, "warehouse.getSize() == 1U");

    {

        bool caught = false;

        try {

            warehouse.removeByIndex(10);

        } catch (const std::out_of_range&) {

            caught = true;

        }

        check(caught, "Expected std::out_of_range");

    }

}

void testWarehouseValidatesCapacityAndNullProducts() {

    {

        bool caught = false;

        try {

            Warehouse(0);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    Warehouse warehouse(1);

    {

        bool caught = false;

        try {

            warehouse.addProduct(nullptr);

        } catch (const std::invalid_argument&) {

            caught = true;

        }

        check(caught, "Expected std::invalid_argument");

    }

    BreadFactory factory;

    warehouse.addProduct(factory.createProduct(301, "Bread", 2, 1, 0.5));

    {

        bool caught = false;

        try {

            warehouse.addProduct(factory.createProduct(302, "Bread", 2, 1, 0.5));

        } catch (const std::overflow_error&) {

            caught = true;

        }

        check(caught, "Expected std::overflow_error");

    }

}

void testWarehouseRuleOfFiveKeepsDeepCopiesIndependent() {

    SmartphoneFactory factory;

    Warehouse original(3);

    original.addProduct(factory.createProduct(401, "Phone", 100, 2, 0.2));

    Warehouse copy(original);

    copy.findById(401)->changeQuantity(5);

    check(original.findById(401)->getQuantity().getValue() == 2,

          "original.findById(401)->getQuantity().getValue() == 2");

    check(copy.findById(401)->getQuantity().getValue() == 7,

          "copy.findById(401)->getQuantity().getValue() == 7");

    check(original.findById(401) != copy.findById(401),

          "original.findById(401) != copy.findById(401)");

    Warehouse assigned(1);

    assigned = original;

    check(assigned.findById(401) != original.findById(401),

          "assigned.findById(401) != original.findById(401)");

    Warehouse* sameAssigned = &assigned;

    assigned = *sameAssigned;

    check(assigned.getSize() == 1U, "assigned.getSize() == 1U");

    Warehouse moved(std::move(copy));

    check(moved.getSize() == 1U, "moved.getSize() == 1U");

    check(copy.getSize() == 0U, "copy.getSize() == 0U");

    Warehouse moveAssigned(2);

    moveAssigned = std::move(moved);

    check(moveAssigned.getSize() == 1U, "moveAssigned.getSize() == 1U");

    check(moved.getSize() == 0U, "moved.getSize() == 0U");

    Warehouse* sameMoved = &moveAssigned;

    moveAssigned = std::move(*sameMoved);

    check(moveAssigned.getSize() == 1U, "moveAssigned.getSize() == 1U");

}

void testIteratorsTraverseMutableAndConstWarehouses() {

    BreadFactory factory;

    Warehouse warehouse(2);

    warehouse.addProduct(factory.createProduct(501, "Bread A", 2, 1, 0.5));

    warehouse.addProduct(factory.createProduct(502, "Bread B", 3, 2, 0.6));

    WarehouseIterator iterator = warehouse.begin();

    check((*iterator).getId() == 501, "(*iterator).getId() == 501");

    ++iterator;

    check((*iterator).getId() == 502, "(*iterator).getId() == 502");

    check(iterator != warehouse.end(), "iterator != warehouse.end()");

    ++iterator;

    check(iterator == warehouse.end(), "iterator == warehouse.end()");

    const Warehouse& constantWarehouse = warehouse;

    ConstWarehouseIterator constIterator = constantWarehouse.begin();

    int totalQuantity = 0;

    while (constIterator != constantWarehouse.end()) {

        totalQuantity += (*constIterator).getQuantity().getValue();

        ++constIterator;

    }

    check(totalQuantity == 3, "totalQuantity == 3");

}

void testProductTransferMovesOwnershipBetweenWarehouses() {

    MilkFactory factory;

    Warehouse source(2);

    Warehouse target(2);

    source.addProduct(factory.createProduct(601, "Milk", 3, 5, 1.0));

    Product* product = source.findById(601);

    product->transferTo(target);

    check(source.getSize() == 0U, "source.getSize() == 0U");

    check(target.getSize() == 1U, "target.getSize() == 1U");

    check(target.findById(601) == product, "target.findById(601) == product");

    target.findById(601)->changeQuantity(-1);

    target.findById(601)->setPrice(Price(4));

    check(target.findById(601)->getQuantity().getValue() == 4,

          "target.findById(601)->getQuantity().getValue() == 4");

    check(target.findById(601)->getPrice().getValue() == 4,

          "target.findById(601)->getPrice().getValue() == 4");

}

void testLoggingFormat() {

    std::ostringstream output;

    LoggingProxy::log("WAREHOUSE", "add", "Bread", output);

    LoggingProxy::log("PRODUCT", "set price", "Bread", output);

    LoggingProxy::log("FACTORY", "create Bread", "Bread", output);

    check(output.str() ==

          "[WAREHOUSE] add: Bread\n"

          "[PRODUCT] set price: Bread\n"

          "[FACTORY] create Bread: Bread\n",

          "Logging preserves the source, operation and result");

}

int main() {

    int failures = 0;

    try {

        testValueClassesValidateAndChangeValues();

        std::cout << "[PASS] testValueClassesValidateAndChangeValues\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testValueClassesValidateAndChangeValues: "

                  << exception.what() << '\n';

    }

    try {

        testProductHierarchyHasExactTypesCategoriesAndIds();

        std::cout << "[PASS] testProductHierarchyHasExactTypesCategoriesAndIds\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testProductHierarchyHasExactTypesCategoriesAndIds: "

                  << exception.what() << '\n';

    }

    try {

        testProductChangesQuantityAndPrice();

        std::cout << "[PASS] testProductChangesQuantityAndPrice\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testProductChangesQuantityAndPrice: "

                  << exception.what() << '\n';

    }

    try {

        testAllFactoriesCreateTheCorrectProduct();

        std::cout << "[PASS] testAllFactoriesCreateTheCorrectProduct\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testAllFactoriesCreateTheCorrectProduct: "

                  << exception.what() << '\n';

    }

    try {

        testWarehouseAddsSearchesAndRemovesProducts();

        std::cout << "[PASS] testWarehouseAddsSearchesAndRemovesProducts\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testWarehouseAddsSearchesAndRemovesProducts: "

                  << exception.what() << '\n';

    }

    try {

        testWarehouseValidatesCapacityAndNullProducts();

        std::cout << "[PASS] testWarehouseValidatesCapacityAndNullProducts\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testWarehouseValidatesCapacityAndNullProducts: "

                  << exception.what() << '\n';

    }

    try {

        testWarehouseRuleOfFiveKeepsDeepCopiesIndependent();

        std::cout << "[PASS] testWarehouseRuleOfFiveKeepsDeepCopiesIndependent\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testWarehouseRuleOfFiveKeepsDeepCopiesIndependent: "

                  << exception.what() << '\n';

    }

    try {

        testIteratorsTraverseMutableAndConstWarehouses();

        std::cout << "[PASS] testIteratorsTraverseMutableAndConstWarehouses\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testIteratorsTraverseMutableAndConstWarehouses: "

                  << exception.what() << '\n';

    }

    try {

        testProductTransferMovesOwnershipBetweenWarehouses();

        std::cout << "[PASS] testProductTransferMovesOwnershipBetweenWarehouses\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testProductTransferMovesOwnershipBetweenWarehouses: "

                  << exception.what() << '\n';

    }

    try {

        testLoggingFormat();

        std::cout << "[PASS] testLoggingFormat\n";

    } catch (const std::exception& exception) {

        ++failures;

        std::cerr << "[FAIL] testLoggingFormat: "

                  << exception.what() << '\n';

    }

    std::cout << (10 - failures) << "/10 tests passed\n";

    return failures == 0 ? 0 : 1;

}
