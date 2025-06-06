// CustomerManager.cpp



#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include<fstream>
#include <vector>
#include <utility>
#include "Node.h"
#include "LinkedList.h"
#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include "CustomerManager.h"
#include "Customer.h"
#include "Test.h"
#include<sstream>
using namespace std;



// Enum for menu actions
enum Actions {
    	QUIT = 0, ADD_CUSTOMER = 1, CUSTOMER_LIST, VEHICLE_LIST_SIZE,
    	SEARCH_BY_MODEL, SEARCH_BY_TYPE, SEARCH_BY_ENGINE, SEARCH_BY_CAPACITY,
    	SEARCH_BY_MODEL_AND_ENGINE, SEARCH_BY_MODEL_AND_CAPACITY,
    	ADD_CAR, ADD_TRUCK, REMOVE_VEHICLE, OPEN_VEHICLE_LIST, TEST
};


const int min_menu_option = 1;
const int max_menu_option = TEST;

// Constructor
CustomerManager::CustomerManager() {    
     loadCustomersFromFile();    
}

// Destructor
   CustomerManager::~CustomerManager() {}

// Method to add a customer (now with address as an optional field)

void CustomerManager::addCustomer(const string& name, const string& contact, const string& address, const string& email, int usageCount) {
    customers.emplace_back(name, contact, address, email, usageCount); // Create a Customer with name, contact, and address

}

void CustomerManager:: Start() { 
    
   loadCustomersFromFile();
   
    cout << endl;
    cout<< endl;
    cout << "\t\t\t\t\t WELCOME TO OUR VEHICLE SEARCH PROGRAMME!" << endl;
    cout << endl;	
    cout << "\t\t\t\t\t Please register or sign in to access the services." << endl;
     cout << endl;
     cout << endl;

    while (true) {
      string choice;
       cout << "Type 'register' to create an account, 'sign in' to log in, or 'exit' to quit: ";
	  cout << endl;
          getline(std::cin, choice);

          if (choice == "register") {
           registerForAccount(); // Register a new account
           } else if (choice == "sign in") {
            if (signIn()) {
                 openMenu(); // Open the menu after successful sign-in
                  break; // Exit the loop after opening the menu
                  } else {
                    cout << "Sign-in failed. Please try again." << endl;
                    }
                 } else if (choice == "exit") {
                   cout << "Exiting program." << endl;
                   break; // Exit the program
                  } else {
                 cout << "Invalid choice. Please try again." << endl;
             }
       }
       
}









// Method to remove a customer by index
   void CustomerManager::removeCustomer(int index) {
    if (index >= 0 && index < customers.size()) {
        customers.erase(customers.begin() + index);
    } else {
        cout << "Invalid index. No customer removed." << endl;
    }
}

// Method to display all customers
   void CustomerManager::displayCustomers() const {
    if (customers.empty()) {
        cout << "No customers to display." << endl;
        return;
    }
    cout << "Displaying all customers:\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << "Customer " << i + 1 << ": ";
        customers[i].display(); // Call the display function of Customer class
    }
}


void CustomerManager::registerForAccount() {
    string name, contact, address, email, usageCountInput, username, password, response;
    int usageCount = 0;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your contact number: ";
    getline(cin, contact);

    cout << "Enter your address (or press Enter to skip): ";
    getline(cin, address);

    cout << "Enter your email (or press Enter to skip): ";
    getline(cin, email);

    cout << "Enter a username: ";
    getline(cin, username);

    cout << "Enter a password: ";
    getline(cin, password);

    cout << "Enter the number of times you have used the program (or press Enter to skip): ";
    getline(cin, usageCountInput);

    if (!usageCountInput.empty()) {
        usageCount = std::stoi(usageCountInput);
    }

    // Create and add the new Customer
    Customer newCustomer(name, contact, address, email, usageCount, username, password);
    customers.emplace_back(newCustomer);
    
    // Save the new customer to file
    saveCustomerToFile(newCustomer);

    cout << "Would you like to sign in? (yes/no): ";
    getline(cin, response);

    if (response == "yes" || response == "Yes") {
        if (signIn()) {
            openMenu(); // If sign-in is successful, open the menu
        } else {
            cout << "Sign-in failed. Exiting program." << std::endl;
            exit(1);
        }
    } else {
        cout << "Thank you for registering! Exiting program." << std::endl;
        exit(0);
    }
}

bool CustomerManager::signIn() {
    string username, password;

    cout << "Enter your username: ";
    getline(cin, username);

    cout << "Enter your password: ";
    getline(cin, password);

    // Check if the username and password match any registered customer
    for (const auto& customer : customers) {
        if (customer.getUsername() == username && customer.getPassword() == password) {
            cout << "Sign-in successful!\n";
            return true; // Sign-in successful
        }
    }

    cout << "Invalid username or password. Please try again.\n";
    return false; // Sign-in failed
}

void CustomerManager::loadCustomersFromFile() {
    ifstream inFile("customers.txt");
    string line;

    while (getline(inFile, line)) {
        istringstream ss(line);
        string name, contact, address, email, userName, passWord;
        int usageCount;

        getline(ss, name, '|');
        getline(ss, contact, '|');
        getline(ss, address, '|');
        getline(ss, email, '|');
        ss >> usageCount;
        ss.ignore(); // Ignore the comma after usageCount
        getline(ss, userName, '|');
        getline(ss, passWord); // Read until the end of the line

        // Create and add the new Customer
        customers.emplace_back(name, contact, address, email, usageCount, userName, passWord);
    }
}

void CustomerManager::saveCustomerToFile(const Customer& customer) {
    ofstream outFile("customers.txt", std::ios::app); // Append mode
    if (outFile.is_open()) {
        outFile << customer.toString() << endl; // Save using toString()
        outFile.close();
    	} else {
        cerr << "Unable to open file for writing." << endl;
    }
}



void CustomerManager:: openMenu() {
   
  
     LinkedList vehicleList;

    // Load vehicles from the file
    //vehicleList.loadFromFile("Vehicle.txt");
  
     string name, contact, address, model, type, engineType, capacityToSearch;
    
     string modelSearch, capacitySearch, modelA, engineA, email, usageCountInput;
    
     Vehicle* foundVehicle, *foundVehicle1,  *foundVehicle2,  *foundVehicle3;
    
            vector<Vehicle*> foundVehicles;
            
            vector<Vehicle*> foundTruck;
            
             pair<Car*, int> result;
    
             pair<Truck*, int> result1;
    
             int usageCount= 0;
    
    

    int choice;
    
    do {
        choice = getMenuChoice(); // Get user choice from menu
        
     	cin.ignore(numeric_limits<streamsize>::max(), '\n');


        switch (choice) {

           case ADD_CUSTOMER:
               cout << "Enter customer name, please? ";
               getline(cin, name);

               cout << "Enter customer contact, please? ";
               getline(cin, contact);

               cout << "Enter customer address (or press Enter to skip), please: ";
               getline(cin, address);

               cout << "Enter customer email (or press Enter to skip), please? ";
               getline(cin, email);

               cout << "Enter the number you have used the program (or press Enter to skip), please? ";

               //string usageCountInput;
                getline(std::cin, usageCountInput);

               // Convert usageCountInput to an integer if not empty, otherwise use default value
                // usageCount = 0; // Default value
                if (!usageCountInput.empty()) {
                usageCount = std::stoi(usageCountInput); // Convert to integer
                }

                // Call the addCustomer function with optional parameters
                addCustomer(name, contact, address, email, usageCount);             
                break;
                  
            case CUSTOMER_LIST:
                // << "Displaying all customers:\n";
                displayCustomers();
                break;

            case VEHICLE_LIST_SIZE:
            	cout << "The number of available cars and trucks: " << endl;
            	vehicleList.countVehicles(); 
                break;

            case SEARCH_BY_MODEL: 
                 // Search for a specific vehicle by its model
               cout << "Enter a vehicle model to find, please" << endl;   
               getline(cin, model);    
               foundVehicle = vehicleList.searchByModel(model);
               if (foundVehicle) {
               cout << "\nFound vehicle:\n";
               foundVehicle->print();
               } else {
               cout << "\nVehicle not found!" << endl;
               }
               // Sort the vehicles by model
               vehicleList.sortByModel();
               cout << "\nSorted vehicles by model:\n";
               vehicleList.display();
                break;

             case SEARCH_BY_TYPE:                               
             	cout << "\nEnter the vehicle type to search for (Car/Truck): ";
             	getline(cin, type);  // Get the type input from user
             	//vehicleList.displayByType(type);
             	foundVehicle2 = vehicleList.searchByType(type);
             	// If a vehicle is found, print its details
             	if (foundVehicle2) {
             	cout << "\nFound vehicle with type: " <<  type  << endl;
             	foundVehicle2->print();
             	} else {
             	cout << "\nNo vehicle found with type: " << type << endl;
             	}
             	vehicleList.sortByType(type);
             	cout << "\nSorted vehicles by type:\n";
             	//vehicleList.displayByType(type);  
                    break;
                     
            case SEARCH_BY_ENGINE:                  
            	// Search by engine type    
            	
            	
           
                cout << "\nEnter the engine type to search for: ";
                getline(std::cin, engineType);  // Get the engine type input from user

                // Get all vehicles with the specified engine type
                foundVehicles = vehicleList.searchByEngine(engineType);

                 cout << "Vehicles with engine " << engineType << ":\n";
    
                // Check if any vehicles were found
                 if (foundVehicles.empty()) {
                 cout << "No vehicles found with engine " << engineType << ".\n";
                } else {
                 // Loop through and print each matching vehicle
                     for (Vehicle* vehicle : foundVehicles) {
                      vehicle->print();  // Virtual function call (Car or Truck)
                     }
                } 	
            	
                break;
            
            case SEARCH_BY_CAPACITY:
            
                 //Search by  capacity
    
                cout << "\nEnter the load capacity to search for: ";
                getline(cin, capacityToSearch);  // Get the load capacity input from user

                // Search for a truck with a specific capacity
   
                foundTruck = vehicleList.searchByCapacity(capacityToSearch);

                // If a vehicle is found, print its details
                if (!foundTruck.empty()) {
                cout << "\nFound vehicle(s) with load capacity " << capacityToSearch << ":" << endl;
                for (Vehicle* truck : foundTruck)
                truck->print();  
                } else {
                cout << "\nNo vehicle found with load capacity: " << capacityToSearch << endl;
                 }

                // Sort the vehicles by load capacity
                vehicleList.sortByCapacity();
                cout << "\nSorted vehicles by load capacity:\n";
                vehicleList.display();  // Display the vehicles after sorting by load capacity
                cout << endl;           
                break;
         
            case SEARCH_BY_MODEL_AND_ENGINE:
  
                cout << "Enter the model of the car: ";
                getline(cin, modelA);  // Get model input

                cout << "Enter the engine type: ";
                getline(cin, engineA);  // Get engine type input

                // Call the searchByModelAndEngine() function
                result = vehicleList.searchByModelAndEngine(modelA, engineA);

                // Check if a matching car was found and display it along with its index
                if (result.first) {
                cout << modelA << " with engine " << engineA << " is available in the vehicle list." << endl;
              
                } else {
                cout << "No car found with model " << modelA << " and engine " << engineA << std::endl;
                }
   
            case SEARCH_BY_MODEL_AND_CAPACITY:
            
                //search by model and load capacity

                cout << "Enter a truck model, please?" << endl;
                getline(cin, modelSearch);

                cout << "Enter a load capacity" << endl;
                getline(cin, capacitySearch);

                result1 = vehicleList.searchByModelAndCapacity(modelSearch, capacitySearch);

                if (result1.first != nullptr) {
                cout << modelSearch << " with load capacity " << capacitySearch << " tons at index " << result1.second << endl;
                 } else {
                cout << "Truck not found." << endl;
                }

                // Sort trucks by model and load capacity
                 vehicleList.sortByModelAndCapacity();

                // Display all trucks
                 vehicleList.display();             
                break; 

            case ADD_CAR: 
                vehicleList.addCar(); 
                break;

            case ADD_TRUCK: 
                vehicleList.addTruck();    
                break;
               
            case REMOVE_VEHICLE:
                int index;
                cout << "Enter the index of the vehicle to remove: ";
    	    	cin >> index;
    	    	// Check if the list is empty
   	        	if (vehicleList.getSize() == 0) {
            	cout << "The vehicle list is empty. No vehicles to remove." << endl;
            	} else if (index < 0 || index >= vehicleList.getSize()) {
            	// Invalid index check
            	cout << "Invalid index. Please enter a valid index between 0 and " << vehicleList.getSize() - 1 << "." << endl;
                } else {
            	// Proceed with removal
           	    vehicleList.removeByIndex(index);
           	    cout << "Vehicle at index " << index << " has been removed." << endl;
                }
                break;
            
	        case OPEN_VEHICLE_LIST:    
            	// Load vehicles from the file
            	vehicleList.loadFromFile("Vehicle.txt");
                break; 

            case TEST:
            	promptUnitTest();
                break;
            case QUIT:
                cout << "Thank you! Bye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
     } while (choice != QUIT);
}


	// Function to get the user's menu choice
	int CustomerManager::getMenuChoice() {
        int choice;
    	do {
        cout << endl;
        cout << "--------------------------------------------\n";
        cout << "Options menu: \n";
        cout << " (" << ADD_CUSTOMER << ") Add a customer to the list\n";
        cout << " (" << CUSTOMER_LIST << ") Display the list of customers\n";
        cout << " (" << VEHICLE_LIST_SIZE << ") Count - get number of vehicles in vehicle list\n";
        cout << " (" << SEARCH_BY_MODEL << ") Search for a car or truck by model \n";
        cout << " (" << SEARCH_BY_TYPE << ") Search for a vehicle by type \n";
        cout << " (" << SEARCH_BY_ENGINE << ") Search for a car by engine\n";
        cout << " (" << SEARCH_BY_CAPACITY << ") Search for a truck by load capacity\n";
        cout << " (" << SEARCH_BY_MODEL_AND_ENGINE << ") Search for a car by model and engine type \n";
        cout << " (" << SEARCH_BY_MODEL_AND_CAPACITY << ") Search for a truck by model and load capacity \n";
        cout << " (" << ADD_CAR << ") Add a car to the list\n";
        cout << " (" << ADD_TRUCK << ") Add a truck to the list\n";
        cout << " (" << REMOVE_VEHICLE << ") Remove a vehicle from the list by index\n";
        cout << " (" << OPEN_VEHICLE_LIST << ") Open a list of vehicles\n";
        cout << " (" << TEST << ") Test the programme's classes and methods \n";
        
 cout << "Enter a number between " << min_menu_option << " and " << max_menu_option << ", or 0 to exit: " << endl;
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > max_menu_option) {
 cout << "Error! Input must be a number between " << min_menu_option << " and " << max_menu_option << ".\n";
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice < 0 || choice > max_menu_option);

    return choice;
}

