#include <iostream>
#include <string>

using namespace std;

struct Order {
    int orderID;
    string item;
    int quantity;
    double total_price;
};

// W1: OOP + private data + constructor / destructor
class IceCream {
private:
    int orderID;
    string flavor;
    int quantity;

public:
    IceCream(int id, string f, int q) {
        orderID = id;
        flavor = f;
        quantity = q;
        cout << "[System] Constructor: Ice Cream object initialized.\n";
    }

    int getOrderID() { return orderID; }
    string getFlavor() { return flavor; }
    int getQuantity() { return quantity; }

    void display() {
        cout << "  Order ID: " << orderID << endl;
        cout << "  Flavor: " << flavor << endl;
        cout << "  Quantity: " << quantity << endl;
    }

    ~IceCream() {
        cout << "[System] Destructor: Memory freed.\n";
    }
};

// Queue node (does NOT delete IceCream – ownership can be transferred)
class QueueNode {
public:
    IceCream* iceCreamData;
    double price;
    QueueNode* next;

    QueueNode(IceCream* orderObj, double pr) {
        iceCreamData = orderObj;
        price = pr;
        next = nullptr;
    }
};

// W4: Hand-built FIFO Queue with O(1) enqueue / dequeue
class IceCreamQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    IceCreamQueue() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    IceCream* getFrontOrder() {
        if (front == nullptr) return nullptr;
        return front->iceCreamData;
    }

    double getFrontPrice() {
        if (front == nullptr) return 0.0;
        return front->price;
    }

    // O(1) enqueue
    void enqueue(IceCream* orderObj, double pr) {
        QueueNode* newNode = new QueueNode(orderObj, pr);

        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // O(1) dequeue – only deletes the node.
    // Ownership of iceCreamData must already have been transferred(or will be cleaned by the destructor if still waiting).
    void dequeue() {
        if (isEmpty()) return;

        QueueNode* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        // Clear the pointer so we never double-delete
        temp->iceCreamData = nullptr;
        delete temp;
        temp = nullptr;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "\nNotice: The ice cream queue line is empty!\n";
            return;
        }
        QueueNode* current = front;
        cout << "\n--- CURRENT LIVE QUEUE LINE (O(1) Tracked) ---\n";
        while (current != nullptr) {
            current->iceCreamData->display();
            cout << "  Total Price: $" << current->price << "\n";
            cout << "--------------------------------------------\n";
            current = current->next;
        }
    }

    int convertToArray(Order orders[]) {
        int count = 0;
        QueueNode* current = front;
        while (current != nullptr) {
            orders[count].orderID = current->iceCreamData->getOrderID();
            orders[count].item = current->iceCreamData->getFlavor();
            orders[count].quantity = current->iceCreamData->getQuantity();
            orders[count].total_price = current->price;
            count++;
            current = current->next;
        }
        return count;
    }

    // CRITICAL FIX: Destructor frees any orders still waiting in the queue
    ~IceCreamQueue() {
        while (!isEmpty()) {
            QueueNode* temp = front;
            front = front->next;

            if (temp->iceCreamData != nullptr) {
                delete temp->iceCreamData;   // free the IceCream
                temp->iceCreamData = nullptr;
            }
            delete temp;
            temp = nullptr;
        }
        rear = nullptr;
        cout << "[System] IceCreamQueue destructor: all remaining orders freed.\n";
    }
};

// W3: Hand-built Linked List for sales history
class ListNode {
public:
    IceCream* archivedData;
    double finalPrice;
    ListNode* next;

    ListNode(IceCream* orderObj, double pr) {
        archivedData = orderObj;
        finalPrice = pr;
        next = nullptr;
    }
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() { head = nullptr; }

    void insertHistory(IceCream* orderObj, double pr) {
        ListNode* newNode = new ListNode(orderObj, pr);
        if (head == nullptr) {
            head = newNode;
        } else {
            ListNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void displayHistory() {
        if (head == nullptr) {
            cout << "\nNotice: Sales history archive log is currently empty.\n";
            return;
        }
        ListNode* current = head;
        cout << "\n--- COMPLETED SALES LOG (Linked List Archive) ---\n";
        while (current != nullptr) {
            current->archivedData->display();
            cout << "  Revenue Tracked: $" << current->finalPrice << "\n";
            cout << "------------------------------------------------\n";
            current = current->next;
        }
    }

    // History is the final owner of served IceCream objects
    ~LinkedList() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* nextNode = current->next;

            if (current->archivedData != nullptr) {
                delete current->archivedData;
                current->archivedData = nullptr;
            }
            delete current;
            current = nextNode;
        }
        head = nullptr;
        cout << "[System] LinkedList destructor: sales history freed.\n";
    }
};

// Search & Sort
string toLower(string text) {
    for (int i = 0; i < (int)text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

int searchByItem(Order orders[], int size, string targetItem) {
    string targetLower = toLower(targetItem);
    for (int i = 0; i < size; i++) {
        if (toLower(orders[i].item) == targetLower) {
            return i;
        }
    }
    return -1;
}

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
    cout << "\n>>> Sorted List by Order ID:\n";
}

// Print Orders
void printOrders(Order orders[], int size) {
    cout << "ID  | Flavor       | Qty | Total Price\n";
    cout << "---------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << orders[i].orderID << " | "
             << orders[i].item << " | "
             << orders[i].quantity << " | $"
             << orders[i].total_price << "\n";
    }
}

// Menu
void displayMenu() {
    cout << "\n=== ICE CREAM ORDER QUEUE ==="
         << "\n1. Take New Order"
         << "\n2. Serve Next Customer"
         << "\n3. Display Live Order Queue"
         << "\n4. View Processed Sales Log"
         << "\n5. Search Active Queue by Flavor"
         << "\n6. Sort & View Active Orders"
         << "\n7. Exit"
         << "\nChoice: ";
}

void handleEnqueue(IceCreamQueue& q, IceCream* newIceCream, double price) {
    q.enqueue(newIceCream, price);
    cout << "-> Success: Added to the order line.\n";
}

void handleDequeue(IceCreamQueue& q, LinkedList& history) {
    if (q.isEmpty()) {
        cout << "\nNotice: No orders waiting to be served.\n";
        return;
    }

    // 1. Get the data
    IceCream* frontOrder = q.getFrontOrder();
    double frontPrice = q.getFrontPrice();

    cout << "\n--- Serving Order Now ---\n";
    frontOrder->display();

    // 2. Transfer ownership to history FIRST
    history.insertHistory(frontOrder, frontPrice);

    // 3. Remove the node from the queue (does NOT delete the IceCream)
    q.dequeue();

    cout << "-> Success: Customer served. Record shifted to history log.\n";
}

int main() {
    IceCreamQueue activeQueue;
    LinkedList saleHistory;
    int choice = 0;

    int id, qty;
    string flav, searchItem;
    double price;

    // Seed data for easy demo
    activeQueue.enqueue(new IceCream(103, "Coconut", 2), 3.00);
    activeQueue.enqueue(new IceCream(104, "Chocolate", 1), 3.25);
    activeQueue.enqueue(new IceCream(101, "Coffee", 1), 2.00);
    activeQueue.enqueue(new IceCream(106, "Strawberry", 3), 8.25);
    activeQueue.enqueue(new IceCream(102, "Mocha", 2), 9.00);
    activeQueue.enqueue(new IceCream(105, "Vanilla", 1), 1.50);
    activeQueue.enqueue(new IceCream(107, "Matcha", 4), 10.00);

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "\n[Error] Enter a valid menu option number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        Order tempArray[50];
        int activeSize = 0;

        switch (choice) {
            case 1: {
                cout << "\nEnter Order ID: ";
                cin >> id;
                cin.ignore();                       // clear leftover newline
                cout << "Enter Flavor: ";
                getline(cin, flav);                 // supports multi-word flavors
                cout << "Enter Quantity: ";
                cin >> qty;
                cout << "Enter Total Price ($): ";
                cin >> price;

                IceCream* order = new IceCream(id, flav, qty);
                handleEnqueue(activeQueue, order, price);
                break;
            }

            case 2:
                handleDequeue(activeQueue, saleHistory);
                break;

            case 3:
                activeQueue.displayQueue();
                break;

            case 4:
                saleHistory.displayHistory();
                break;

            case 5: {
                activeSize = activeQueue.convertToArray(tempArray);
                if (activeSize == 0) {
                    cout << "\nNotice: Order line is empty.\n";
                    break;
                }
                cout << "Enter the Ice Cream Flavour to find: ";
                getline(cin, searchItem);

                int pos = searchByItem(tempArray, activeSize, searchItem);
                if (pos != -1) {
                    cout << "\n- \"" << searchItem << "\" found at line position: " << pos + 1 << "\n";
                    cout << "- Total Price: $" << tempArray[pos].total_price << "\n";
                } else {
                    cout << "Item \"" << searchItem << "\" not found in the queue.\n";
                }
                break;
            }

            case 6:
                activeSize = activeQueue.convertToArray(tempArray);
                if (activeSize == 0) {
                    cout << "\nNotice: No orders to sort.\n";
                } else {
                    sortByOrderID(tempArray, activeSize);
                    printOrders(tempArray, activeSize);
                }
                break;

            case 7:
                cout << "\nShutting down system. Have a nice day!\n";
                break;

            default:
                cout << "\n[Error] Please choose a number between 1 and 7.\n";
                break;
        }
    } while (choice != 7);

    // No manual cleanup needed anymore.
    // Destructors of activeQueue and saleHistory will run automatically and free every remaining IceCream object safely.
    return 0;
}
