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

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class ShoppingCart {
private:
    vector<CartItem> items;

public:
    double total;

    bool productInCart(const string& productId) const {
        for (const auto& item : items) {
            if (toLowerCase(item.product.id) == toLowerCase(productId)) {
                return true;  
            }
        }
        return false;  
    }

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
            if (toLowerCase(items[i].product.id) == toLowerCase(productId)) {
                if (items[i].quantity > quantity) {
                    items[i].quantity -= quantity;
                } else {
                    items.erase(items.begin() + i);
                }
                cout << "Product removed successfully!\n";
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
    }

    float calculateTotal() const {
        float total = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i].product.price * items[i].quantity;
        }
        return total;
    }

    const vector<CartItem>& getItems() const {
        return items;
    }

    void clearCart() {
        items.clear();
    }
};

class Customer {
public:
    string name;
    string address;
    string deliveryDate;

    void getDetails() {
        cin.ignore();
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your address: ";
        getline(cin, address);
        cout << "Enter preferred delivery date: ";
        getline(cin, deliveryDate);
    }

    void displayDetails() const {
        cout << "Customer Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Delivery Date: " << deliveryDate << endl;
    }
};

class Order {
public:
    int orderID;
    vector<CartItem> items;
    float totalAmount;
    Customer customer;

    Order(int id, const vector<CartItem> &items, float total, const Customer &cust) : orderID(id), items(items), totalAmount(total), customer(cust) {}

    void displayOrderDetails() const {
        cout << "\nOrder ID: " << orderID << endl;
        customer.displayDetails();
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Order Details:\n";
        cout << left << setw(12) << "Product ID" << setw(12) << "Name" << setw(8) << "Price" << "Quantity" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << left << setw(12) << items[i].product.id << setw(12) << items[i].product.name << setw(8) << items[i].product.price << items[i].quantity << endl;
        }
    }
};

void displayProducts(const vector<Product>& products) {
    cout << "\nAvailable Products:\n";
    cout << left << setw(12) << "Product ID" << setw(12) << "Name" << "Price" << endl;
    for (size_t i = 0; i < products.size(); ++i) {
        cout << left << setw(12) << products[i].id << setw(12) << products[i].name << products[i].price << endl;
    }
}

void clearScreen() {
    system("cls");
}

Product* findProductById(vector<Product>& products, const string& id) {
    string lowerId = toLowerCase(id);
    for (size_t i = 0; i < products.size(); ++i) {
        if (toLowerCase(products[i].id) == lowerId) {
            return &products[i];
        }
    }
    return nullptr;
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
    vector<Order> orders;
    int orderCount = 0;
    bool myCondition = true;

    while (myCondition) {
        cout << "\nMenu:\n1. View/Add Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\n\nEnter your choice: ";
        int choice;

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        clearScreen();

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
            };
            case 2: {
                cart.viewCart();
                float total = cart.calculateTotal();
                cout << "Total Amount: " << total << endl;
            
                while (!cart.getItems().empty()) {
                    cout << "Do you want to remove an item from the cart? (y/n): ";
                    char removeChoice;
                    cin >> removeChoice;
            
                    if (tolower(removeChoice) == 'n') {
                        break;  
                    } else if (tolower(removeChoice) == 'y') {
                        string productId;
                        int quantity;
            
                      
                        while (true) {
                            cout << "Enter the Product ID to remove: ";
                            cin >> productId;
            
                            
                            if (!cart.productInCart(productId)) {
                                cout << "Error: Product ID not found in the cart. Try again.\n";
                                continue;  
                            }
            
                            cout << "Enter the quantity to remove: ";
                            if (!(cin >> quantity) || quantity <= 0) {
                                cout << "Invalid quantity. Try again.\n\n";
                                cin.clear();  
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                continue;
                            }
            
                            cart.removeProduct(productId, quantity);
                            cout << "Item removed successfully.\n";
                            break;  
                        }
            
                       
                        cart.viewCart();
                        total = cart.calculateTotal();
                        cout << "Updated Total Amount: " << total << endl;
                    } else {
                        cout << "Invalid input. Please enter 'y' or 'n'.\n";
                    }
                }
            
                if (!cart.getItems().empty()) {
                    cout << "Do you want to check out? (y/n): ";
                    char checkoutChoice;
                    cin >> checkoutChoice;
            
                    if (tolower(checkoutChoice) == 'y') {
                        Customer customer;
                        customer.getDetails();
            
                        orderCount++;
                        orders.emplace_back(orderCount, cart.getItems(), total, customer);
            
                        cout << "\nOrder placed successfully!\n";
                        cart.clearCart();
                    }
                }
                break;
            
                    cout << "Do you want to check out? (y/n): ";
                    char checkoutChoice;
                    cin >> checkoutChoice;
            
                    if (tolower(checkoutChoice) == 'y') {
                        Customer customer;
                        customer.getDetails();
            
                        orderCount++;
                        orders.emplace_back(orderCount, cart.getItems(), cart.total, customer);
            
                        cout << "\nOrder placed successfully!\n";
                        cart.clearCart();
                    }
                break;
            }
            case 3: {
                if (orders.empty()) {
                    cout << "No orders available.\n";
                } else {
                    for (const auto& order : orders) {
                        order.displayOrderDetails();
                    }
                }
                break;
            }
            case 4: {
                myCondition = false;
                cout << "Exiting the program.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }
return 0;
}