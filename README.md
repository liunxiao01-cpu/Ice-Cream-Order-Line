//# Ice-Cream
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int OrderID;
    string type;
    string flavors[10];
    int flavorCount;
    Node* next;

    Node(int id, string t) {
        OrderID = id;
        type = t;
        flavorCount = 0;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:

    LinkedList() {
        head = nullptr;
    }

    void insertOrder(int id, string type, string flavors[], int count) {

        Node* NewNode = new Node(id, type);

        NewNode->OrderID = id;
        NewNode->flavorCount = count;

        for (int i = 0; i < count; i++) {
            NewNode->flavors[i] = flavors[i];
        }

        NewNode->next = nullptr;

        if (head == nullptr) {
            head = NewNode;
        }
        else {
            Node* temp = head;

            while (temp->next != nullptr) {
                temp = temp->next;
            }

            temp->next = NewNode;
        }
    }

    void deleteOrder(int id) {

        if (head == nullptr) {
            return;
        }

        if (head->OrderID == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;

        while (current->next != nullptr &&
               current->next->OrderID != id) {

            current = current->next;
        }

        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    void displayOrder() {

        Node* current = head;

        cout << "# Order ID: " << current->OrderID << endl;

        while (current != nullptr) {

            cout <<endl<< "  - Type: " << current->type << endl;

            cout << "  - Flavors: "<<endl;

            for (int i = 0; i < current->flavorCount; i++) {
                cout <<"    . "<< current->flavors[i]<< endl;

            }

            current = current->next;
        }
    }
};

int main() {
    
    return 0;
}
