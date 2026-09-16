#include <iostream>
#include <string>
using namespace std;

// Blueprint describing an ice cream order
class IceCream {
private:
    int orderID;
    string flavor;
    int quantity;

public:
    // Runs automatically when object is created
    IceCream(int id, string f, int q) {
        orderID = id;
        flavor = f;
        quantity = q;
        cout << "Constructor called!" << endl;
    }

    void display() {
        cout << "Order ID: " << orderID << endl;
        cout << "Flavor: " << flavor << endl;
        cout << "Quantity: " << quantity << endl;
    }

    // Runs automatically when object is deleted
    ~IceCream() {
        cout << "Destructor called! Memory freed." << endl;
    }
};

int main() {
    int id, qty;
    string flav;

    cout << "Enter Order ID: ";
    cin >> id;

    cout << "Enter Flavor: ";
    cin >> flav; // only reads one word, no spaces

    cout << "Enter Quantity: ";
    cin >> qty;

    // "order" is a pointer - it stores the address of the object, not the object itself
    IceCream* order = new IceCream(id, flav, qty);
    order->display();

    delete order;      // frees the memory since we used "new"
    order = nullptr;   // avoids accidentally using a deleted pointer

    cout << "Pointer is now nullptr." << endl;
    return 0;
}