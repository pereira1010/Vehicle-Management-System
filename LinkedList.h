
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<string>
#include "Node.h"
#include <vector>
#include "Car.h"
#include "Truck.h"
using namespace std;



class LinkedList {
    

private:
   	     Node* head;
    	 int size;

   	    vector<Vehicle*> vehicles; // Container to hold vehicles (Car, Truck)
    
public:
    	LinkedList() : head(nullptr), size(0) {}

     	~LinkedList();

    	void add(Vehicle* vehicle);
    
    	void display() const;
       
    	void loadFromFile(const std::string& filename);
    
    	Vehicle* searchByModel(const std::string& model) const; 
   
   	    void sortByModel();

    	Vehicle* searchByType(const std::string& vehicleType);  
  
    	void sortByType(const std::string& vehicleType);
    	
    	vector<Vehicle*> searchByEngine(const std::string& engineType) const;
     
        void sortByEngine();
    	
    	 vector<Vehicle*>searchByCapacity(const std::string& capacity) const;
    	 
         void sortByCapacity();
    	
       
        void displayByType(const std::string& vehicleType) const;
      
        string trim(const std::string& str) const;
   
     	void countVehicles() const;
    
    	void addCar();

        void addTruck();
    
    	void insert(Vehicle* v);

    	void printList();

    	void removeByIndex(int index);
    
    	int getSize() const; 

    	Node* getHead() const;
    
        pair<Car*, int>searchByModelAndEngine(const std::string& model, const std::string& engineType) const; 
        
        void sortByModelAndEngine();

        pair<Truck*, int>searchByModelAndCapacity(const std::string& model, const string& loadCapacity) const;
      
        void sortByModelAndCapacity();
        
    
    
    
    
};

#endif // LINKEDLIST_H