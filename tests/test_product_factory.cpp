#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <vector>

#include "ProductFactory.h"

// ----- Each factory creates the right product type -----

TEST(ProductFactoryTest, StandardFactoryCreatesStandardProduct) {
    StandardProductFactory factory;
    auto product = factory.createProduct(1, "Office chair", 5);

    EXPECT_EQ(product->type(), "Standard");
    EXPECT_EQ(product->id(), 1);
    EXPECT_EQ(product->name(), "Office chair");
    EXPECT_EQ(product->minStock(), 5);
}

TEST(ProductFactoryTest, PerishableFactoryCreatesPerishableProductWithShelfLife) {
    PerishableProductFactory factory(7);
    auto product = factory.createProduct(2, "Milk", 20);

    EXPECT_EQ(product->type(), "Perishable");
    // The real object behind the Product pointer is a PerishableProduct
    auto* perishable = dynamic_cast<PerishableProduct*>(product.get());
    ASSERT_NE(perishable, nullptr);
    EXPECT_EQ(perishable->shelfLifeDays(), 7);
}

TEST(ProductFactoryTest, FragileFactoryCreatesFragileProduct) {
    FragileProductFactory factory;
    auto product = factory.createProduct(3, "Glass cups", 10);

    EXPECT_EQ(product->type(), "Fragile");
}

// ----- The calling code only needs the ProductFactory interface -----

TEST(ProductFactoryTest, FactoriesCanBeUsedThroughTheBaseInterface) {
    std::vector<std::unique_ptr<ProductFactory>> factories;
    factories.push_back(std::make_unique<StandardProductFactory>());
    factories.push_back(std::make_unique<PerishableProductFactory>(5));
    factories.push_back(std::make_unique<FragileProductFactory>());

    std::vector<std::string> types;
    for (const auto& factory : factories) {
        types.push_back(factory->createProduct(1, "Item", 0)->type());
    }

    EXPECT_EQ(types, (std::vector<std::string>{"Standard", "Perishable", "Fragile"}));
}

// ----- Invalid data is rejected -----

TEST(ProductTest, EmptyNameIsRejected) {
    StandardProductFactory factory;
    EXPECT_THROW(factory.createProduct(1, "", 5), std::invalid_argument);
}

TEST(ProductTest, NegativeMinimumStockIsRejected) {
    StandardProductFactory factory;
    EXPECT_THROW(factory.createProduct(1, "Chair", -1), std::invalid_argument);
}

TEST(ProductTest, NonPositiveIdIsRejected) {
    FragileProductFactory factory;
    EXPECT_THROW(factory.createProduct(0, "Glass", 1), std::invalid_argument);
}

TEST(ProductTest, ZeroShelfLifeIsRejected) {
    PerishableProductFactory factory(0);
    EXPECT_THROW(factory.createProduct(1, "Milk", 1), std::invalid_argument);
}
