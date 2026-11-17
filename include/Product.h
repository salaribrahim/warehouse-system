#pragma once
#include <string>

// Base class for every product in the warehouse.
// It is abstract: you cannot create a plain "Product",
// only one of the concrete types below.
class Product {
public:
    Product(int id, std::string name, int minStock);
    virtual ~Product() = default;

    int id() const { return id_; }
    const std::string& name() const { return name_; }
    int minStock() const { return minStock_; }  // below this -> low-stock alert (later)

    // Each product type answers these differently (polymorphism)
    virtual std::string type() const = 0;
    virtual std::string handlingInstructions() const = 0;

private:
    int id_;
    std::string name_;
    int minStock_;
};

// A normal product, e.g. an office chair
class StandardProduct : public Product {
public:
    using Product::Product;  // reuse the base constructor
    std::string type() const override;
    std::string handlingInstructions() const override;
};

// Food or anything that expires
class PerishableProduct : public Product {
public:
    PerishableProduct(int id, std::string name, int minStock, int shelfLifeDays);
    int shelfLifeDays() const { return shelfLifeDays_; }
    std::string type() const override;
    std::string handlingInstructions() const override;

private:
    int shelfLifeDays_;
};

// Breakable items, e.g. glass
class FragileProduct : public Product {
public:
    using Product::Product;
    std::string type() const override;
    std::string handlingInstructions() const override;
};
