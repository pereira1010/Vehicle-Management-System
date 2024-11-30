#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {
public:
    string data; // Data contained in the node
    Node* next;       // Pointer to the next node
    Node* prev;       // Pointer to the previous node

    Node(const string& data); // Constructor
    ~Node();                  // Destructor
};

#endif