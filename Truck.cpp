// Truck.h

#include "Truck.h"
using namespace std;


 // Constructor      
Truck::Truck(const string& model, const string& loadCapacity) : Vehicle(model, "Truck"), loadCapacity(loadCapacity) {}

   void Truck::print() const {
   cout << "Model: " << model << ", Type: Truck, Load Capacity: " << loadCapacity << endl;
    }
    
   	string Truck::getModel() const { return model; }

    	string Truck::getType() const { return "Truck"; }
    
    	string Truck::getLoadCapacity() const { return loadCapacity; }
    
     	string Truck::getEngine() const { return "";  }
     
     	bool Truck::operator<(const Vehicle& other) const {
      	const Truck& otherTruck = dynamic_cast<const Truck&>(other);
      	return this->model < otherTruck.model;
    }
         


/*
// for comparing a truck to a car
    const Truck* otherTruck = dynamic_cast<const Truck*>(&other);
    if (otherTruck) {
     return this->getModel() < otherTruck->getModel(); // Compare models lexicographically
    } else {
        // Return false if other is not a Truck
        return false;
    }
}        

*/