#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H
#include <string>
#include <vector>
#include "Customer.h"
#include "LinkedList.h"
using namespace std;


class CustomerManager {
public:
    	CustomerManager();  // Constructor
    	~CustomerManager(); // Destructor

    	void addCustomer(const string& name, const string& contact, const         	string& address, const string& email = "N/A", int usageCount = 0);
     
    	void removeCustomer(int index);
    	void displayCustomers() const;
    	void openMenu(); // Declaration of openMenu method   
    	void registerForAccount();
	//bool signIn();
	
	bool signIn();
	
	void loadCustomersFromFile();
	
	void saveCustomerToFile(const Customer& customer);
    
private:
    	vector<Customer> customers; // Container for customers
    	int getMenuChoice(); // Declaration of getMenuChoice method
};

#endif // CUSTOMERMANAGER_H











