#include "ProductFactory.h"

#include "Bread.h"
#include "Jacket.h"
#include "Laptop.h"
#include "LoggingProxy.h"
#include "Milk.h"
#include "Smartphone.h"
#include "TShirt.h"

std::unique_ptr<Product> SmartphoneFactory::createProduct(
    int id, const std::string& name, int price,
    int quantity, double weight) const {
    LoggingProxy::log("FACTORY", "create Smartphone", name);
    return std::make_unique<Smartphone>(
        id, name, Price(price), Quantity(quantity), Weight(weight));
}

std::unique_ptr<Product> LaptopFactory::createProduct(
    int id, const std::string& name, int price,
    int quantity, double weight) const {
    LoggingProxy::log("FACTORY", "create Laptop", name);
    return std::make_unique<Laptop>(
        id, name, Price(price), Quantity(quantity), Weight(weight));
}

std::unique_ptr<Product> TShirtFactory::createProduct(
    int id, const std::string& name, int price,
    int quantity, double weight) const {
    LoggingProxy::log("FACTORY", "create TShirt", name);
    return std::make_unique<TShirt>(
        id, name, Price(price), Quantity(quantity), Weight(weight));
}

std::unique_ptr<Product> JacketFactory::createProduct(
    int id, const std::string& name, int price,
    int quantity, double weight) const {
    LoggingProxy::log("FACTORY", "create Jacket", name);
    return std::make_unique<Jacket>(
        id, name, Price(price), Quantity(quantity), Weight(weight));
}

std::unique_ptr<Product> MilkFactory::createProduct(
    int id, const std::string& name, int price,
    int quantity, double weight) const {
    LoggingProxy::log("FACTORY", "create Milk", name);
    return std::make_unique<Milk>(
        id, name, Price(price), Quantity(quantity), Weight(weight));
}

std::unique_ptr<Product> BreadFactory::createProduct(
    int id, const std::string& name, int price,
    int quantity, double weight) const {
    LoggingProxy::log("FACTORY", "create Bread", name);
    return std::make_unique<Bread>(
        id, name, Price(price), Quantity(quantity), Weight(weight));
}
