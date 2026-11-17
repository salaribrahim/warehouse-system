#pragma once
#include <memory>
#include <string>

#include "Product.h"

// ============================================================
//  FACTORY METHOD pattern (GoF, creational)
//
//  ProductFactory is the "Creator". It declares the factory
//  method createProduct(). Each subclass decides WHICH concrete
//  Product class gets created. Code that uses a factory only
//  knows the ProductFactory and Product interfaces.
// ============================================================
class ProductFactory {
public:
    virtual ~ProductFactory() = default;

    // The factory method
    virtual std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                                   int minStock) const = 0;
};

class StandardProductFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                           int minStock) const override;
};

class PerishableProductFactory : public ProductFactory {
public:
    explicit PerishableProductFactory(int shelfLifeDays);
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                           int minStock) const override;

private:
    int shelfLifeDays_;
};

class FragileProductFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name,
                                           int minStock) const override;
};
