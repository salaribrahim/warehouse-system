#include "Product.h"

#include <stdexcept>
#include <utility>

Product::Product(int id, std::string name, int minStock)
    : id_(id), name_(std::move(name)), minStock_(minStock) {
    if (id_ <= 0) {
        throw std::invalid_argument("Product id must be positive");
    }
    if (name_.empty()) {
        throw std::invalid_argument("Product name must not be empty");
    }
    if (minStock_ < 0) {
        throw std::invalid_argument("Minimum stock must not be negative");
    }
}

// ----- StandardProduct -----
std::string StandardProduct::type() const { return "Standard"; }

std::string StandardProduct::handlingInstructions() const {
    return "Store on regular shelves.";
}

// ----- PerishableProduct -----
PerishableProduct::PerishableProduct(int id, std::string name, int minStock, int shelfLifeDays)
    : Product(id, std::move(name), minStock), shelfLifeDays_(shelfLifeDays) {
    if (shelfLifeDays_ <= 0) {
        throw std::invalid_argument("Shelf life must be at least 1 day");
    }
}

std::string PerishableProduct::type() const { return "Perishable"; }

std::string PerishableProduct::handlingInstructions() const {
    return "Keep cool. Shelf life: " + std::to_string(shelfLifeDays_) + " days.";
}

// ----- FragileProduct -----
std::string FragileProduct::type() const { return "Fragile"; }

std::string FragileProduct::handlingInstructions() const {
    return "Handle with care. Do not stack heavy items on top.";
}
