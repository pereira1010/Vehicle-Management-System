//Truck.h

#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"
#include<iostream>
using namespace std;



class Truck : public Vehicle {

private:
    	string loadCapacity;

public:
        Truck(const string& model, const string& loadCapacity);

        void print() const override;
    
   	string getModel() const override;

    	string getType() const override;
    
    	string getLoadCapacity() const override;
    
     	string getEngine() const override;
     
     	bool operator<(const Vehicle& other) const override;
         
         
};

#endif // TRUCK_H