#include <iostream>
#include <memory>
#include <vector>

#include "ProductFactory.h"

int main() {
    std::cout << "====== WAREHOUSE SYSTEM ======\n\n";

    // Each factory knows how to build one kind of product
    StandardProductFactory standardFactory;
    PerishableProductFactory perishableFactory(7);  // 7 days shelf life
    FragileProductFactory fragileFactory;

    std::vector<std::unique_ptr<Product>> products;
    products.push_back(standardFactory.createProduct(1, "Office chair", 5));
    products.push_back(perishableFactory.createProduct(2, "Milk", 20));
    products.push_back(fragileFactory.createProduct(3, "Glass cups", 10));

    for (const auto& product : products) {
        std::cout << "#" << product->id() << "  " << product->name()
                  << "  [" << product->type() << "]\n"
                  << "    " << product->handlingInstructions() << "\n";
    }
    return 0;
}
