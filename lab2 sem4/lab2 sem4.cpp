#include <iostream>
#include <vector>

class Category;

class Product {
private:
    std::string name;
    double price;
    Category* category;

public:
    Product(const std::string& name, double price, Category* category)
        : name(name), price(price), category(category) {}

    const std::string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    Category* getCategory() const;
};

class Category {
private:
    std::string name;
    std::vector<Product*> products;

public:
    Category(const std::string& name) : name(name) {}

    void addProduct(Product* product) {
        products.push_back(product);
    }

    const std::string& getName() const {
        return name;
    }

    const std::vector<Product*>& getProducts() const {
        return products;
    }
};

Category* Product::getCategory() const {
    return category;
}

class AbstractFactory {
public:
    virtual std::vector<Product*> getProductsByCategory(const Category* category) const = 0;
};

class ConcreteFactory : public AbstractFactory {
public:
    std::vector<Product*> getProductsByCategory(const Category* category) const override {
        return category->getProducts();
    }
};

class Catalog {
private:
    std::vector<Category*> categories;
    AbstractFactory* factory;

public:
    Catalog() {
        factory = new ConcreteFactory();
    }

    ~Catalog() {
        delete factory;
        for (Category* category : categories) {
            delete category;
        }
    }

    void addCategory(Category* category) {
        categories.push_back(category);
    }

    void addProductToCategory(Product* product, Category* category) {
        category->addProduct(product);
    }

    std::vector<Category*> getCategories() const {
        return categories;
    }

    std::vector<Product*> getProductsByCategory(const Category* category) const {
        return factory->getProductsByCategory(category);
    }

    void printAllProducts() const {
        std::cout << "All Products:" << std::endl;
        for (const Category* category : categories) {
            std::vector<Product*> products = getProductsByCategory(category);
            for (const Product* product : products) {
                std::cout << "Category: " << category->getName() << ", Product: " << product->getName() << ", Price: " << product->getPrice() << std::endl;
            }
        }
    }
};

int main() {
    // Создание категорий
    Category* category1 = new Category("Electronics");
    Category* category2 = new Category("Clothing");

    // Создание товаров
    Product* product1 = new Product("Smartphone1", 500.0, category1);
    Product* product2 = new Product("Laptop1", 700.0, category1);
    Product* product3 = new Product("Smartphone2", 600.0, category1);
    Product* product4 = new Product("Laptop2", 900.0, category1);
    Product* product5 = new Product("Smartphone3", 800.0, category1);
    Product* product6 = new Product("Laptop3", 1111.0, category1);
    Product* product7 = new Product("Smartphone4", 1000.0, category1);
    Product* product8 = new Product("Laptop4", 1500.0, category1);
    Product* product9 = new Product("T-Shirt", 20.0, category2);
    Product* product10 = new Product("Jeans", 50.0, category2);

    // Создание каталога
    Catalog catalog;
    catalog.addCategory(category1);
    catalog.addCategory(category2);

    // Добавление товаров в категории
    catalog.addProductToCategory(product1, category1);
    catalog.addProductToCategory(product2, category1);
    catalog.addProductToCategory(product3, category1);
    catalog.addProductToCategory(product4, category1);
    catalog.addProductToCategory(product5, category1);
    catalog.addProductToCategory(product6, category1);
    catalog.addProductToCategory(product7, category1);
    catalog.addProductToCategory(product8, category1);
    catalog.addProductToCategory(product9, category2);
    catalog.addProductToCategory(product10, category2);

    // Вывод всех товаров
    catalog.printAllProducts();

    return 0;
}