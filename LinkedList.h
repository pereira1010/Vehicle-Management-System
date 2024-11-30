#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

using namespace std;

class LinkedList {
private:
    Node* head; // Pointer to the first node
    Node* tail; // Pointer to the last node
    int size;   // Number of elements in the list

public:
    LinkedList();                 // Constructor
    ~LinkedList();                // Destructor

    void push_back(const string& data); // Add element to the end
    void push_front(const string& data); // Add element to the front
    void display_forward() const;           // Print elements from head to tail
    void display_backward() const;          // Print elements from tail to head
    int get_size() const;                   // Get the size of the list
    void clear();                           // Remove all elements
};

#endif