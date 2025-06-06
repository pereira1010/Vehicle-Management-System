#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
using namespace std;




class Vehicle {
    
protected:
    	  string model;
    	  string type;

public:
    Vehicle(const std::string& model, const std::string& type) : model(model), type(type) {}

    virtual ~Vehicle() {}
    virtual void print() const = 0;
    virtual string getModel() const = 0 ;

    virtual string getType() const = 0 ;
    
    
    // Pure virtual function for derived classes to implement
     virtual string getEngine() const = 0;

    // You can also add a virtual function for loadCapacity
     virtual string getLoadCapacity() const = 0;
        
    // Comparison operator to be overridden in derived classes
     virtual bool operator<(const Vehicle& other) const = 0;
    
       
};

#endif // VEHICLE_