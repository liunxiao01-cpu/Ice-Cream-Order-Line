#include <iostream>
#include <string>

using namespace std;


struct Order {
    int orderID;
    string item; 
    int quantity;
    double total_price;
};

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
        cout <<  "Constructor called!" << endl;
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
        cout <<  "Destructor called! Memory freed." << endl;
    }
};
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
    void dequeue() {
        if (isEmpty()) return;
        
        QueueNode* temp = front;
        front = front->next; 
        
        if (front == nullptr) {
            rear = nullptr; 
        }

        delete temp->iceCreamData; 
        delete temp;               
    }
     void displayQueue() {
        if (isEmpty()) {
            cout << "\nNotice: The ice cream queue line is empty!\n";
            return;
        }
        QueueNode* current = front;
        cout << "\nCURRENT LIVE QUEUE LINE \n";
        while (current != nullptr) {
            current->iceCreamData->display();
            cout << "  Total Price: $" << current->price << "\n";
            cout << "--------------------------------------------\n";
            current = current->next;
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
};
class Node {
public:
    IceCream* iceCreamData;
    double price; 
    Node* next;

    Node(IceCream* orderObj, double pr) {
        iceCreamData = orderObj;
        price = pr;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() { head = nullptr; }

    bool isEmpty() { return head == nullptr; }
    
    IceCream* getFrontOrder() {
        if (head == nullptr) return nullptr;
        return head->iceCreamData;
    }

    void insertHistory(IceCream* orderObj, double pr) {
        Node* NewNode = new Node(orderObj, pr);

        if (head == nullptr) {
            head = NewNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = NewNode;
        }
    }
    void displayHistory() {
        if (head == nullptr) {
            cout << "\nNotice: Sales history archive log is currently empty.\n";
            return;
        }
        ListNode* current = head;
        cout << "\nCOMPLETED SALES LOG \n";
        while (current != nullptr) {
            current->archivedData->display();
            cout << "  Revenue Tracked: $" << current->finalPrice << "\n";
            cout << "------------------------------------------------\n";
            current = current->next;
        }
    }
     ~LinkedList() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* nextNode = current->next;
            delete current->archivedData;  
            delete current;             
            current = nextNode;
        }
    }
    
};


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


void displayMenu() {
    cout << "\nFULLY INTEGRATED MASTER MENU"
         << "\n1. Take New Order "
         << "\n2. Serve Next Customer "
         << "\n3. Display Order Queue"
         << "\n4. View Processed Sales Log"
         << "\n5. Search Order by Flavor"
         << "\n6. Sort & View Total Orders"
         << "\n7. Exit"
         << "\nChoice: ";
}

void handleEnqueue(LinkedList& list, IceCream* newIceCream, double price) {
    list.insertOrder(newIceCream, price);
    cout << "-> Success: Added to the order line.\n";
}

void handleDequeue(LinkedList& list) {
    if (list.isEmpty()) {
        cout << "\nNotice: No orders waiting to be served.\n";
        return;
    }

    IceCream* frontOrder = list.getFrontOrder();
    cout << "\n--- Serving Order Now ---\n";
    frontOrder->display();
    history.insertHistory(frontOrder, frontPrice);
    q.dequeue(); 
    cout << "-> Success: Customer served. Record shifted to history log.\n";
}

int main() {
    IceCreamQueue activeQueue;
    LinkedListed saleHistory;
    int choice = 0;

    int id, qty;
    string flav;
    double price; 
    string searchItem;

    activeQueue.insertOrder(new IceCream(103, "Coconut", 2), 3.00);
    activeQueue.insertOrder(new IceCream(104, "Chocolate", 1), 3.25);
    activeQueue.insertOrder(new IceCream(101, "Coffee", 1), 2.00);
    activeQueue.insertOrder(new IceCream(106, "Strawberry", 3), 8.25);
    activeQueue.insertOrder(new IceCream(102, "Mocha", 2), 9.00);
    activeQueue.insertOrder(new IceCream(105, "Vanilla", 1), 1.50);
    activeQueue.insertOrder(new IceCream(107, "Matcha", 4), 10.00);

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "\n[Error] Enter a valid menu option number.\n";
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }
        cin.ignore(); 

        Order tempArray[50]; 
        int activeSize = 0;

        switch (choice) {
            case 1:
                cout << "\nEnter Order ID: "; cin >> id;
                cout << "Enter Flavor: "; cin >> flav; 
                cout << "Enter Quantity: "; cin >> qty;
                cout << "Enter Total Price ($): "; cin >> price;

                {
                    IceCream* order = new IceCream(id, flav, qty);
                    handleEnqueue(activeQueue, order, price);
                }
                break;

            case 2:
                handleDequeue(activeQueue);
                break;

            case 3:
                activeQueue.displayOrder();
                break;
            case 4:
                salesHistory.displayHistory();
                break;

            case 5:
                activeSize = activeQueue.convertToArray(tempArray);
                if (activeSize == 0) {
                    cout << "\nNotice: Order line is empty.\n";
                    break;
                }
                cout << "Enter the Ice Cream Flavour to find: ";
                getline(cin, searchItem);
                
                {
                    int pos = searchByItem(tempArray, activeSize, searchItem);
                    if (pos != -1) {
                        cout << "\n- \"" << searchItem << "\" found at line position: " << pos + 1 << "\n";
                        cout << "- Total Price: $" << tempArray[pos].total_price << "\n";
                    } else {
                        cout << "Item \"" << searchItem << "\" not found in the queue.\n";
                    }
                }
                break;

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
                cout << "\nShutting down system.\n";
                break;
        }
    } while (choice != 7);

    while (!activeQueue.isEmpty()) {
        activeQueue.deleteFront();
    }

    return 0;
}
