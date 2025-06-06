
#ifndef CAR_H
#define CAR_H
#include<iostream>
#include "Vehicle.h"
using namespace std;


class Car : public Vehicle {
    
private:
           string engine;

public:
    	Car(const string& model, const string& engine);
    	void print() const override;
    
     	string getEngine() const override;
          
    	string getModel() const override;

    	string getType() const override;
    
     	string getLoadCapacity() const override;
        
    	// Comparison operator for Car class (compare by model)

     	bool operator<(const Vehicle& other) const override;
    
};

#endif