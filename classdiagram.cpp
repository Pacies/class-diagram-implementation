#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

class Product {
public:
    string id, name;
    float price;

    Product(string id, string name, float price) : id(id), name(name), price(price) {}
};

class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product product, int quantity) : product(product), quantity(quantity) {}
};

class ShoppingCart {
private:
    vector<CartItem> items;

public:
    void addProduct(const Product &product, int quantity) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].product.id == product.id) {
                items[i].quantity += quantity;
                return;
            }
        }
        items.push_back(CartItem(product, quantity));
    }

    void removeProduct(const string &productId, int quantity) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].product.id == productId) {
                if (quantity >= items[i].quantity) {
                    items.erase(items.begin() + i);  // Remove if quantity is zero or less
                } else {
                    items[i].quantity -= quantity;  // Decrease quantity
                }
                cout << "Product updated successfully!\n";
                return;
            }
        }
        cout << "Product not found in cart.\n";
    }

    void viewCart() const {
        if (items.empty()) {
            cout << "\nYour cart is empty.\n";
            return;
        }

        cout << "\nShopping Cart:\n";
        cout << left << setw(12) << "Product ID" << setw(12) << "Name" << setw(8) << "Price" << "Quantity" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << left << setw(12) << items[i].product.id << setw(12) << items[i].product.name << setw(8) << items[i].product.price << items[i].quantity << endl;
        }

        cout << "\nTotal Amount: " << calculateTotal() << "\n";
    }

    float calculateTotal() const {
        float total = 0;
        for (const auto &item : items) {
            total += item.product.price * item.quantity;
        }
        return total;
    }

    const vector<CartItem>& getItems() const {
        return items;
    }

    void clearCart() {
        items.clear();
        cout << "Cart has been cleared.\n";
    }
};

Product* findProductById(vector<Product>& products, const string& id) {
    for (auto& product : products) {
        if (product.id == id) {
            return &product;
        }
    }
    return nullptr;
}

void displayProducts(const vector<Product>& products) {
    cout << "\nAvailable Products:\n";
    cout << left << setw(12) << "Product ID" << setw(12) << "Name" << "Price" << endl;
    for (const auto& product : products) {
        cout << left << setw(12) << product.id << setw(12) << product.name << product.price << endl;
    }
}

int main() {
    vector<Product> products = {
        {"ABC", "Paper", 20},
        {"DEF", "Pencil", 10},
        {"GHI", "Ballpen", 35},
        {"JKL", "Eraser", 5},
        {"MNO", "Tape", 25},
        {"PQR", "Notebook", 15},
        {"STU", "Ruler", 10},
        {"VWX", "Mouse", 20},
        {"YZ", "Keyboard", 25},
    };

    ShoppingCart cart;
    bool myCondition = true;

    while (myCondition) {
        cout << "\nMenu:\n1. View/Add Products\n2. View Shopping Cart\n3. Remove Items from Cart\n4. Clear Cart\n5. Exit\n\nEnter your choice: ";
        int choice;

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                displayProducts(products);
                while (true) {
                    cout << "\nEnter product ID to add (or '0' to go back): ";
                    string productId;
                    cin >> productId;
                    if (productId == "0") break;

                    Product* product = findProductById(products, productId);
                    if (product) {
                        cout << "Enter quantity: ";
                        int quantity;
                        if (!(cin >> quantity) || quantity <= 0) {
                            cout << "Invalid quantity. Try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        cart.addProduct(*product, quantity);
                        cout << "Product added successfully!\n";
                    } else {
                        cout << "Invalid product ID.\n";
                    }
                }
                break;
            }

            case 2:
                cart.viewCart();
                break;

            case 3: {
                cart.viewCart();
                if (!cart.getItems().empty()) {
                    cout << "\nEnter product ID to remove (or '0' to go back): ";
                    string productId;
                    cin >> productId;
                    if (productId == "0") break;

                    cout << "Enter quantity to remove: ";
                    int quantity;
                    if (!(cin >> quantity) || quantity <= 0) {
                        cout << "Invalid quantity. Try again.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    cart.removeProduct(productId, quantity);
                }
                break;
            }

            case 4:
                cart.clearCart();
                break;

            case 5:
                cout << "Exiting program.\n";
                myCondition = false;
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
} 
