// Node.cpp

#include "Node.h"
#include "Node.h"
#include "Car.h"   // Include Car class header
#include "Truck.h" // Include Truck class header


 // Comparison operator for Node based on the data (Vehicle) in the node


bool Node::operator<(const Node& other) const {
    // Case 1: Both nodes are of the same type (Car to Car)
    if (Car* carData = dynamic_cast<Car*>(data)) {
        if (Car* otherCarData = dynamic_cast<Car*>(other.data)) {
            return *otherCarData < *carData;  // Use Car's operator<
        }
    }

    // Case 2: Both nodes are of the same type (Truck to Truck)
    if (Truck* truckData = dynamic_cast<Truck*>(data)) {
        if (Truck* otherTruckData = dynamic_cast<Truck*>(other.data)) {
            return *truckData < *otherTruckData;  // Use Truck's operator<
        }
    }

    // Case 3: Nodes are of different types (Car vs Truck or Truck vs Car)
    // For now, return false or implement a custom fallback comparison rule.
    return false;
}


