/*************************************

COMSC 210 | Lab 22 | Skylar Robinson | IDE Used: Eclipse

*************************************/

#include <iostream>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void delete_pos(int pos) {
    	if (!head) return; // Empty list

    	//find node to delete
    	Node* temp = head;
    	for (int i = 0; i < pos && temp; i++)
    		temp = temp->next;

    	if (!temp) return; // Position not found

    	if (temp->prev) { //if not the head
    		temp->prev->next = temp->next;
    	} else {
    		head = temp->next; // Deleting the head
    	}

    	if (temp->next) { //if not the tail
    	    temp->next->prev = temp->prev;
    	} else {
    	    tail = temp->prev; // Deleting the tail
    	}

    	delete temp;
    }

    //delete the head node
    void pop_front() {
    	Node* temp = head;
    	head = temp->next;
    	temp->next->prev = nullptr;
    	delete temp;
    }

    //delete the tail node
    void pop_back() {
    	Node* temp = tail;
    	tail = temp->prev;
    	temp->prev->next = nullptr;
    	delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
	srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List: ";
    list.print();

    cout << "After deleting the fifth item: ";
    list.delete_pos(4);
    list.print();

    cout << "Adding '5' to the beginning of the list: ";
    list.push_front(5);
    list.print();

    cout << "Deleting '5' by value: ";
    list.delete_val(5);
    list.print();

    cout << "Deleting the last value of the list: ";
    list.pop_back();
    list.print();

    cout << "Deleting the first value of the list: ";
    list.pop_front();
    list.print();

    cout << "Deleting the first value of the list by position: ";
    list.delete_pos(0);
    list.print();

    return 0;
}
