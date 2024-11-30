#include "LinkedList.h"
#include <iostream>

int main() {
    LinkedList list;

    // Adding elements to the list
    list.push_back("Node1");
    list.push_back("Node2");
    list.push_front("Node0");

    // Display elements
    cout << "List (forward): ";
    list.display_forward();

    cout << "List (backward): ";
    list.display_backward();

    // Get size
    cout << "Size of list: " << list.get_size() << endl;

    // Clear the list
    list.clear();
    cout << "List cleared. Size: " << list.get_size() << endl;

    return 0;
}