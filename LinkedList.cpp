#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {
    // Constructor initializes an empty list
}

LinkedList::~LinkedList() {
    // Destructor
    clear();
}

void LinkedList::push_back(const string& data) {
    Node* newNode = new Node(data);
    if (!head) { // If list is empty
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

void LinkedList::push_front(const string& data) {
    Node* newNode = new Node(data);
    if (!head) { // If list is empty
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++size;
}

void LinkedList::display_forward() const {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::display_backward() const {
    Node* current = tail;
    while (current) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}

int LinkedList::get_size() const {
    return size;
}

void LinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = tail = nullptr;
    size = 0;
}