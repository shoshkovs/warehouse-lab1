#pragma once

#include "Product.h"

#include <memory>

#include <string>

class ProductFactory {

public:

    virtual ~ProductFactory() = default;

    virtual std::unique_ptr<Product> createProduct(

        int id,

        const std::string& name,

        int price,

        int quantity,

        double weight) const = 0;

};

class SmartphoneFactory : public ProductFactory {

public:

    std::unique_ptr<Product> createProduct(

        int id, const std::string& name, int price,

        int quantity, double weight) const override;

};

class LaptopFactory : public ProductFactory {

public:

    std::unique_ptr<Product> createProduct(

        int id, const std::string& name, int price,

        int quantity, double weight) const override;

};

class TShirtFactory : public ProductFactory {

public:

    std::unique_ptr<Product> createProduct(

        int id, const std::string& name, int price,

        int quantity, double weight) const override;

};

class JacketFactory : public ProductFactory {

public:

    std::unique_ptr<Product> createProduct(

        int id, const std::string& name, int price,

        int quantity, double weight) const override;

};

class MilkFactory : public ProductFactory {

public:

    std::unique_ptr<Product> createProduct(

        int id, const std::string& name, int price,

        int quantity, double weight) const override;

};

class BreadFactory : public ProductFactory {

public:

    std::unique_ptr<Product> createProduct(

        int id, const std::string& name, int price,

        int quantity, double weight) const override;

};
