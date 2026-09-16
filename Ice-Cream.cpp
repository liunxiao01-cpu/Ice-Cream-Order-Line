#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Order Structure
struct Order {
    int orderID;
    string item;
    int quantity;
    double total_price;
};

// KIM

// Avoiding case-sensitive
string toLower(string text) {
    for (int i = 0; i < (int)text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

// SEARCHING FUNCTION : Search by Item name (Ice Cream Flavour)
int searchByItem(Order orders[], int size, string targetItem) {

    string targetLower = toLower(targetItem);
    
     for (int i = 0; i < size; i++) {
        if (toLower(orders[i].item) == targetLower) {
            return i;
        }
    }
    return -1;
}

// SORTING FUNCTION : Sort by Order ID (Ascending ID)
void sortByOrderID(Order orders[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (orders[j].orderID > orders[j + 1].orderID) {
                Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
    cout << "\n>>> Sorted by Order ID:\n";
}

// DISPLAY FUNCTION : print every order
void printOrders(Order orders[], int size) {
    for (int i = 0; i < size; i++) {
        cout << orders[i].orderID << " | "
             << orders[i].item << " | "
             << orders[i].quantity << " | $"
             << orders[i].total_price << "\n";
    }
}

int main() {

    // Sample Order Data
    Order sampleOrders[] = {
        {103, "Coconut",     2, 3.00},
        {104, "Chocolate",   1, 3.25},
        {106, "Strawberry",  3, 8.25},
        {101, "Coffee",      1, 2.00},
        {102, "Mocha",       2, 9.00},
        {105, "Vanilla",     1, 1.50},
        {107, "Matcha",      4, 10.00}
    };

    int totalSampleOrders = 7;

    // KIM

    // Searching for Ice Cream Flavour Ordering
    string item;
    int pos;

    cout << "Enter the Ice Cream Flavour Ordering: ";
    cin >> item;
    pos = searchByItem(sampleOrders, totalSampleOrders, item);

    if (pos != -1) {
        cout << "\n- \"" << item << "\" is found" << " at the position \"" << pos + 1 << "\"" << endl;
        cout << "- Price: " << sampleOrders[pos].total_price << " $" << endl;
    } else {
        cout << "Item \"" << item << "\" not found.\n";
    }

    // Sorting by Order ID
    sortByOrderID(sampleOrders, totalSampleOrders);
    printOrders(sampleOrders, totalSampleOrders);

    return 0;
}
