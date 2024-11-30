#include "Node.h"
#include <iostream>

Node::Node(const string& data) 
    : data(data), next(nullptr), prev(nullptr) {
    // Constructor initializes pointers to null
}

Node::~Node() {
    // Destructor
    cout << "Node with data \"" << data << "\" destroyed." << std::endl;
}