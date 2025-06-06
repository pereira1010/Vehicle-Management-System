#ifndef NODE_H
#define NODE_H
#include "Vehicle.h"
using namespace std;


class Node {

public:
       Vehicle* data;  // Pointer to the Vehicle object
       Node* next;     // Pointer to the next node
        
        
       // Constructor that allows creating an empty node (no vehicle assigned yet)
       Node() : data(nullptr), next(nullptr) {}

       Node(Vehicle* vehicle) : data(vehicle), next(nullptr) {}
                
      // Define comparison operator for Node
       
       bool operator<(const Node& other) const;
 
                             
};

#endif // NODE_