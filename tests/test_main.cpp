#include "TestHarness.h"

#include "Bread.h"
#include "Jacket.h"
#include "Laptop.h"
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

void testWarehouseValidatesCapacityAndNullProducts() {
    for (int capacity : {-1, -100, (-2147483647 - 1)}) {
        bool caught = false;
        try {
            Warehouse invalid(capacity);
        } catch (const std::invalid_argument&) {
            caught = true;
        }
        check(caught, "Negative warehouse capacity must be rejected");
    }

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

    Product* beforeMove = copy.findById(401);
    Warehouse moved(std::move(copy));
    check(moved.findById(401) == beforeMove, "Move keeps the same product");
    check(moved.getSize() == 1U, "moved.getSize() == 1U");
    check(copy.getSize() == 0U, "copy.getSize() == 0U");

    Warehouse moveAssigned(2);
    moveAssigned = std::move(moved);
    check(moveAssigned.findById(401) == beforeMove, "Move assignment keeps the same product");
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

int main() {
    int failures = 0;
    try {
        testValueClassesValidateAndChangeValues();
        std::cout << "[PASS] testValueClassesValidateAndChangeValues\n";
    } catch (const std::exception& error) {
        ++failures;
        std::cerr << "[FAIL] testValueClassesValidateAndChangeValues: " << error.what() << '\n';
    }

    try {
        testAllFactoriesCreateTheCorrectProduct();
        std::cout << "[PASS] testAllFactoriesCreateTheCorrectProduct\n";
    } catch (const std::exception& error) {
        ++failures;
        std::cerr << "[FAIL] testAllFactoriesCreateTheCorrectProduct: " << error.what() << '\n';
    }

    try {
        testWarehouseValidatesCapacityAndNullProducts();
        std::cout << "[PASS] testWarehouseValidatesCapacityAndNullProducts\n";
    } catch (const std::exception& error) {
        ++failures;
        std::cerr << "[FAIL] testWarehouseValidatesCapacityAndNullProducts: " << error.what() << '\n';
    }

    try {
        testWarehouseRuleOfFiveKeepsDeepCopiesIndependent();
        std::cout << "[PASS] testWarehouseRuleOfFiveKeepsDeepCopiesIndependent\n";
    } catch (const std::exception& error) {
        ++failures;
        std::cerr << "[FAIL] testWarehouseRuleOfFiveKeepsDeepCopiesIndependent: " << error.what() << '\n';
    }

    try {
        testIteratorsTraverseMutableAndConstWarehouses();
        std::cout << "[PASS] testIteratorsTraverseMutableAndConstWarehouses\n";
    } catch (const std::exception& error) {
        ++failures;
        std::cerr << "[FAIL] testIteratorsTraverseMutableAndConstWarehouses: " << error.what() << '\n';
    }

    std::cout << (5 - failures) << "/5 tests passed\n";
    return failures == 0 ? 0 : 1;
}
