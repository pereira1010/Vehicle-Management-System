#include "Car.h"
using namespace std;



    	Car::Car(const string& model, const string& engine) : Vehicle(model, "Car"), engine(engine) {}

    	void Car::print() const {
        cout << "Model: " << model << ", Type: Car, Engine: " << engine << std::endl;
    	}
    
     	string Car::getEngine() const { return engine; }
          
    	string Car::getModel() const  { return model; }

    	string Car::getType() const { return "Car"; }
    
     	string Car::getLoadCapacity() const {
        return "N/A"; // Cars typically don't have a load capacity
    	}
        
    	// Comparison operator for Car class (compare by model)

     	bool Car::operator<(const Vehicle& other) const {
        const Car& otherCar = dynamic_cast<const Car&>(other);
        return this->model < otherCar.model;
    	}     
    


