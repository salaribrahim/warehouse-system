#include "ProductFactory.h"

std::unique_ptr<Product> StandardProductFactory::createProduct(int id, const std::string& name,
                                                               int minStock) const {
    return std::make_unique<StandardProduct>(id, name, minStock);
}

PerishableProductFactory::PerishableProductFactory(int shelfLifeDays)
    : shelfLifeDays_(shelfLifeDays) {}

std::unique_ptr<Product> PerishableProductFactory::createProduct(int id, const std::string& name,
                                                                 int minStock) const {
    return std::make_unique<PerishableProduct>(id, name, minStock, shelfLifeDays_);
}

std::unique_ptr<Product> FragileProductFactory::createProduct(int id, const std::string& name,
                                                              int minStock) const {
    return std::make_unique<FragileProduct>(id, name, minStock);
}
