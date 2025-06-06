
#include "LinkedList.h"
#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <algorithm>  // For std::transform to do case-insensitive comparison
#include <cctype>     // For std::tolower
using namespace std;


//Get the size of a vehicle linked list
int LinkedList::getSize() const { return size; }


// destructor
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete->data;
        delete toDelete;
    }
}

// Add a car or truck to a LinkedList object

void LinkedList::add(Vehicle* vehicle) {
    Node* newNode = new Node(vehicle);
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void LinkedList::display() const {
    Node* current = head;
    while (current != nullptr) {
        current->data->print();
        current = current->next;
    }
}



// Function to remove a vehicle by its index from a LinkedList object

    void LinkedList::removeByIndex(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index." << endl;
            return;
        }
        Node* current = head;
        Node* previous = nullptr;
        for (int i = 0; i < index; ++i) {
            previous = current;
            current = current->next;
        }

        if (previous) {
            previous->next = current->next;
        } else {
            head = current->next;
        }
        delete current->data;
        delete current;
        --size;
    }


// Count the number of cars and trucks available in a Linked list
void LinkedList::countVehicles() const {
    int carCount = 0;
    int truckCount = 0;

    Node* current = head;
    while (current != nullptr) {
        // Assuming you have a `getType` method in Vehicle class
        if (current->data->getType() == "Car") {
            carCount++;
        } else if (current->data->getType() == "Truck") {
            truckCount++;
        }
        current = current->next;
    }

    // Output the result
     cout << "Total number of Cars: " << carCount << endl;
     cout << "Total number of Trucks: " << truckCount << endl;
}


// Load vehicle from a file to an object of LinkedList class

void LinkedList::loadFromFile(const string& filename) {
     ifstream file(filename);
     string line;

    if (file.is_open()) {
        while (getline(file, line)) {
             stringstream ss(line);
             string model, type, engine, loadCapacity;

            // Example line format:
            // Model: Honda Civic, Type: Car, Engine: 1.8L
            // Model: Ford F-150, Type: Truck, Load Capacity: 3.5 tons

            // Parsing model
            getline(ss, model, ',');  // Read up to the first comma
            model = model.substr(model.find(":") + 2);  // Strip "Model: "

            // Parsing type (Car or Truck)
            getline(ss, type, ',');
            type = type.substr(type.find(":") + 2);  // Strip "Type: "

            // Check if it's a Car or Truck and parse accordingly
            if (type == "Car") {
                getline(ss, engine);  // Read the engine
                engine = engine.substr(engine.find(":") + 2);  // Strip "Engine: "
                add(new Car(model, engine));
            } else if (type == "Truck") {
                getline(ss, loadCapacity);  // Read the load capacity
                loadCapacity = loadCapacity.substr(loadCapacity.find(":") + 2);  // Strip "Load Capacity: "
                add(new Truck(model, loadCapacity));
            }
        }
         cout << "Vehicles loaded successfully from the file." << endl;
    } else {
         cerr << "Failed to open file." << endl;
    }
}



// Search and sort by vehicle type

Vehicle* LinkedList::searchByType(const std::string& vehicleType) {
     string lowerVehicleType = vehicleType; 

    // Convert the input vehicleType to lowercase
    std::transform(lowerVehicleType.begin(), lowerVehicleType.end(), lowerVehicleType.begin(), ::tolower);

    Node* current = head;
    while (current != nullptr) {
        std::string vehicleTypeLower = current->data->getType();
        
        // Convert the vehicle type to lowercase
        std::transform(vehicleTypeLower.begin(), vehicleTypeLower.end(), vehicleTypeLower.begin(), ::tolower);

        // Compare the types case-insensitively
        if (vehicleTypeLower == lowerVehicleType) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::sortByType(const std::string& vehicleType) {
     string lowerVehicleType = vehicleType;

    // Convert the input vehicleType to lowercase
      transform(lowerVehicleType.begin(), lowerVehicleType.end(), lowerVehicleType.begin(), ::tolower);

    vector<Vehicle*> filteredVehicles;

    // Step 1: Filter vehicles based on the type (case-insensitive comparison)
    Node* current = head;
    while (current != nullptr) {
        string vehicleTypeLower = current->data->getType();
        
        // Convert the vehicle type to lowercase
        transform(vehicleTypeLower.begin(), vehicleTypeLower.end(), vehicleTypeLower.begin(), ::tolower);

        if (vehicleTypeLower == lowerVehicleType) {
            filteredVehicles.push_back(current->data);
        }
        current = current->next;
    }

    // Step 2: Sort the filtered vehicles by their model
     sort(filteredVehicles.begin(), filteredVehicles.end(), [](Vehicle* v1, Vehicle* v2) {
        return v1->getModel() < v2->getModel();
    });

    // Step 3: Display the sorted vehicles of the selected type
    if (filteredVehicles.empty()) {
        cout << "No vehicles of type " << vehicleType << " found." << endl;
    } else {
        for (auto vehicle : filteredVehicles) {
            vehicle->print();
        }
    }
}


  // Search and sort by model
  
   Vehicle* LinkedList::searchByModel(const std::string& model) const {
    Node* current = head;

    // Trim and convert the input model to lowercase for case-insensitive comparison
    string trimmedModel = trim(model);
    transform(trimmedModel.begin(), trimmedModel.end(), trimmedModel.begin(), ::tolower);  // Convert to lowercase

    while (current != nullptr) {
        // Trim and convert the stored vehicle model to lowercase
        string vehicleModel = current->data->getModel();
        vehicleModel = trim(vehicleModel);
        transform(vehicleModel.begin(), vehicleModel.end(), vehicleModel.begin(), ::tolower);  // Convert to lowercase

        // Compare the input model with the vehicle model
        if (vehicleModel == trimmedModel) {
            return current->data;  // If a match is found, return the vehicle data
        }
        current = current->next;  // Move to the next node
    }
    return nullptr;  // If no match is found, return nullptr
}


void LinkedList::sortByModel() {
    if (!head) return;

    vector<Vehicle*> vehicleVector;
    Node* current = head;
    while (current != nullptr) {
        vehicleVector.push_back(current->data);
        current = current->next;
    }

    // Sort vehicles by model in a case-insensitive way
    sort(vehicleVector.begin(), vehicleVector.end(), [](Vehicle* a, Vehicle* b) {
        // Convert both model names to lowercase for comparison
        string modelA = a->getModel();
        string modelB = b->getModel();
        transform(modelA.begin(), modelA.end(), modelA.begin(), ::tolower);
        transform(modelB.begin(), modelB.end(), modelB.begin(), ::tolower);
        return modelA < modelB;
    });

    // Reassign sorted vehicles back to the linked list
    current = head;
    for (auto vehicle : vehicleVector) {
        current->data = vehicle;
        current = current->next;
    }
}


string LinkedList::trim(const string& str) const {
    size_t first = str.find_first_not_of(" \t\n\r");  // Find first non-space character
    size_t last = str.find_last_not_of(" \t\n\r");   // Find last non-space character

    // If no non-space characters, return an empty string
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }

    return str.substr(first, (last - first + 1));  // Return the substring containing no leading/trailing spaces
}



// Search and sort by engine type

vector<Vehicle*> LinkedList::searchByEngine(const std::string& engineType) const {
    string lowerEngineType = trim(engineType);  // Trim and convert input to lowercase
    transform(lowerEngineType.begin(), lowerEngineType.end(), lowerEngineType.begin(), ::tolower);

    Node* current = head;
    vector<Vehicle*> matchingVehicles;

    while (current) {
        Car* car = dynamic_cast<Car*>(current->data);  // Check if the vehicle is a Car
        if (car) {
            string carEngineLower = trim(car->getEngine()); // Trim and lowercase engine string
            transform(carEngineLower.begin(), carEngineLower.end(), carEngineLower.begin(), ::tolower);

            // If the engine matches, add the vehicle to the vector
            if (carEngineLower == lowerEngineType) {
                matchingVehicles.push_back(car);  // Add matching car to the vector
            }
        }

        Truck* truck = dynamic_cast<Truck*>(current->data); // Check if the vehicle is a Truck
        if (truck) {
            string truckEngineLower = trim(truck->getEngine()); // Trim and lowercase engine string
            transform(truckEngineLower.begin(), truckEngineLower.end(), truckEngineLower.begin(), ::tolower);

            // If the engine matches, add the vehicle to the vector
            if (truckEngineLower == lowerEngineType) {
                matchingVehicles.push_back(truck);  // Add matching truck to the vector
            }
        }

        current = current->next;  // Move to the next node
    }

    return matchingVehicles;  // Return the vector of matching vehicles
}



void LinkedList::sortByEngine() {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            Car* car1 = dynamic_cast<Car*>(i->data);
            Car* car2 = dynamic_cast<Car*>(j->data);

            if (car1 && car2) {
               string engine1 = trim(car1->getEngine());  // Trim both engine strings
                string engine2 = trim(car2->getEngine());

                // Convert both engine types to lowercase for case-insensitive comparison
                transform(engine1.begin(), engine1.end(), engine1.begin(), ::tolower);
                transform(engine2.begin(), engine2.end(), engine2.begin(), ::tolower);

                // Swap if engine1 > engine2
                if (engine1 > engine2) {
                    swap(i->data, j->data);
                }
            }
        }
    }
}


// search by load capacity with vector container 

vector<Vehicle*> LinkedList::searchByCapacity(const string& capacity) const {
    string lowerCapacity = trim(capacity);  // Trim and convert input to lowercase
    transform(lowerCapacity.begin(), lowerCapacity.end(), lowerCapacity.begin(), ::tolower);

    Node* current = head;
    vector<Vehicle*> matchingVehicles;  // Use Vehicle* to handle both Truck and Car

    while (current) {
        // Check if the vehicle is a Truck
        Truck* truck = dynamic_cast<Truck*>(current->data);
        if (truck) {
            string truckCapacityLower = trim(truck->getLoadCapacity());
            transform(truckCapacityLower.begin(), truckCapacityLower.end(), truckCapacityLower.begin(), ::tolower);

            if (truckCapacityLower == lowerCapacity) {
                matchingVehicles.push_back(truck);  // Add matching truck to the vector
            }
        }

        // Check if the vehicle is a Car
        Car* car = dynamic_cast<Car*>(current->data);
        if (car) {
            string carCapacityLower = trim(car->getLoadCapacity());  // Assuming Car has load capacity or similar attribute
            transform(carCapacityLower.begin(), carCapacityLower.end(), carCapacityLower.begin(), ::tolower);

            if (carCapacityLower == lowerCapacity) {
                matchingVehicles.push_back(car);  // Add matching car to the vector (if applicable)
            }
        }

        current = current->next;  // Move to the next node
    }

    return matchingVehicles;  // Return the vector of matching vehicles
}


void LinkedList::sortByCapacity() {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            Truck* truck1 = dynamic_cast<Truck*>(i->data);
            Truck* truck2 = dynamic_cast<Truck*>(j->data);

            if (truck1 && truck2) {
                string capacity1 = trim(truck1->getLoadCapacity());  // Trim both truck capacities
                string capacity2 = trim(truck2->getLoadCapacity());

                // Convert both capacities to lowercase for case-insensitive comparison
                transform(capacity1.begin(), capacity1.end(), capacity1.begin(), ::tolower);
                transform(capacity2.begin(), capacity2.end(), capacity2.begin(), ::tolower);

                // Swap if truck1's capacity > truck2's capacity
                if (capacity1 > capacity2) {
                    swap(i->data, j->data);
                }
            }
        }
    }
}


pair<Car*, int> LinkedList::searchByModelAndEngine(const string& model, const  string& engineType) const {
    // Trim and convert to lowercase for case-insensitive comparison
    string lowerModel = trim(model);
    transform(lowerModel.begin(), lowerModel.end(), lowerModel.begin(), ::tolower);

    string lowerEngineType = trim(engineType);
    transform(lowerEngineType.begin(), lowerEngineType.end(), lowerEngineType.begin(), ::tolower);

    Node* current = head;
    int index = 0;  // Initialize the index

    while (current) {
        Car* car = dynamic_cast<Car*>(current->data);  // Check if the vehicle is a Car
        if (car) {
            // Trim and convert both the car's model and engine type to lowercase
            string carModelLower = trim(car->getModel());
            transform(carModelLower.begin(), carModelLower.end(), carModelLower.begin(), ::tolower);

            string carEngineLower = trim(car->getEngine());
            transform(carEngineLower.begin(), carEngineLower.end(), carEngineLower.begin(), ::tolower);

            // If both model and engine match (case-insensitive), return the car and its index
            if (carModelLower == lowerModel && carEngineLower == lowerEngineType) {
                return std::make_pair(car, index);  // Return the car and its index
            }
        }

        current = current->next;  // Move to the next node
        index++;  // Increment the index
    }

    return std::make_pair(nullptr, -1);  // Return nullptr and -1 if no matching car is found
}



void LinkedList::sortByModelAndEngine() {
    // Traverse through the linked list and collect all the Car* objects into a vector
    vector<Car*> cars;

    Node* current = head;  // Start from the head of the linked list
    while (current) {
        Car* car = dynamic_cast<Car*>(current->data);  // Make sure it's a Car object
        if (car) {
            cars.push_back(car);  // Add car to the vector
        }
        current = current->next;  // Move to the next node
    }

    // Sort the vector of cars using a lambda function that compares both model and engine
    sort(cars.begin(), cars.end(), [this](Car* car1, Car* car2) {
        // Trim and convert to lowercase for case-insensitive comparison
        string model1 = trim(car1->getModel());
        string model2 = trim(car2->getModel());
        string engine1 = trim(car1->getEngine());
        string engine2 = trim(car2->getEngine());

        transform(model1.begin(), model1.end(), model1.begin(), ::tolower);
        transform(model2.begin(), model2.end(), model2.begin(), ::tolower);
        transform(engine1.begin(), engine1.end(), engine1.begin(), ::tolower);
        transform(engine2.begin(), engine2.end(), engine2.begin(), ::tolower);

        // Compare models, and if they match, compare engines
        if (model1 == model2) {
            return engine1 < engine2;  // If models match, compare engines
        } else {
            return model1 < model2;  // If models differ, compare models
        }
    });

    // After sorting the vector, reassign the sorted cars back to the linked list
    current = head;  // Start again from the head
    size_t index = 0;
    while (current && index < cars.size()) {
        current->data = cars[index];  // Update the node data with the sorted car
        current = current->next;
        index++;
    }
}


pair<Truck*, int> LinkedList::searchByModelAndCapacity(const std::string& model, const string& loadCapacity) const {
    // Trim and convert to lowercase for case-insensitive comparison
    string lowerModel = trim(model);
    transform(lowerModel.begin(), lowerModel.end(), lowerModel.begin(), ::tolower);

    string lowerLoadCapacity = trim(loadCapacity);
    transform(lowerLoadCapacity.begin(), lowerLoadCapacity.end(), lowerLoadCapacity.begin(), ::tolower);

    Node* current = head;
    int index = 0;  // Initialize the index

    while (current) {
        Truck* truck = dynamic_cast<Truck*>(current->data);  // Check if the vehicle is a Truck
        if (truck) {
            // Trim and convert both the truck's model and load capacity to lowercase
            string truckModelLower = trim(truck->getModel());
            transform(truckModelLower.begin(), truckModelLower.end(), truckModelLower.begin(), ::tolower);

            string truckCapacityLower = trim(truck->getLoadCapacity());  // Assuming getLoadCapacity returns a string
            transform(truckCapacityLower.begin(), truckCapacityLower.end(), truckCapacityLower.begin(), ::tolower);

            // If both model and load capacity match (case-insensitive), return the truck and its index
            if (truckModelLower == lowerModel && truckCapacityLower == lowerLoadCapacity) {
                return std::make_pair(truck, index);  // Return the truck and its index
            }
        }

        current = current->next;  // Move to the next node
        index++;  // Increment the index
    }

    return std::make_pair(nullptr, -1);  // Return nullptr and -1 if no matching truck is found
}




void LinkedList::sortByModelAndCapacity() {
    // Traverse through the linked list and collect all the Truck* objects into a vector
    vector<Truck*> trucks;

    Node* current = head;  // Start from the head of the linked list
    while (current) {
        Truck* truck = dynamic_cast<Truck*>(current->data);  // Make sure it's a Truck object
        if (truck) {
            trucks.push_back(truck);  // Add truck to the vector
        }
        current = current->next;  // Move to the next node
    }

    // Sort the vector of trucks using a lambda function that compares both model and load capacity
    std::sort(trucks.begin(), trucks.end(), [this](Truck* truck1, Truck* truck2) {
        // Trim and convert to lowercase for case-insensitive comparison
        string model1 = trim(truck1->getModel());
        string model2 = trim(truck2->getModel());
        string capacity1 = trim(truck1->getLoadCapacity());
        string capacity2 = trim(truck2->getLoadCapacity());

        transform(model1.begin(), model1.end(), model1.begin(), ::tolower);
        transform(model2.begin(), model2.end(), model2.begin(), ::tolower);
        transform(capacity1.begin(), capacity1.end(), capacity1.begin(), ::tolower);
        transform(capacity2.begin(), capacity2.end(), capacity2.begin(), ::tolower);

        // Compare models, and if they match, compare load capacities
        if (model1 == model2) {
            return capacity1 < capacity2;  // If models match, compare load capacities
        } else {
            return model1 < model2;  // If models differ, compare models
        }
    });

    // After sorting the vector, reassign the sorted trucks back to the linked list
    current = head;  // Start again from the head
    size_t index = 0;
    while (current && index < trucks.size()) {
        current->data = trucks[index];  // Update the node data with the sorted truck
        current = current->next;
        index++;
    }
}        



// Add a car to the list

void LinkedList::addTruck() {
    string model, cargoCapacity;
    cout << "Enter truck model: ";
    getline(std::cin, model);
    cout << "Enter truck cargo capacity: ";
    getline(std::cin, cargoCapacity);

    // Create a new Truck object
    Truck* newTruck = new Truck(model, cargoCapacity);

    // Insert the new Truck into the current list (this list)
    insert(newTruck);
}


// Add a car to the linked list

void LinkedList::addCar() {
    string model, engineType;
    cout << "Enter car model: ";
    getline(std::cin, model);
    cout << "Enter car engine type: ";
    getline(std::cin, engineType);

    // Create a new Car object
    Car* newCar = new Car(model, engineType);

    // Insert the new Car into the current list (this list)
    insert(newCar);
}


// Insert an added car/truck into the LinkedList object

void LinkedList::insert(Vehicle* v) {
    Node* newNode = new Node(v);
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    ++size;
}


               
       // Method to print all vehicles in the list
       void LinkedList::printList() {
        Node* current = head;
        while (current) {
            cout << current->data->getModel() << endl;
            current = current->next;
           }
    }
                                                                                                                                                                                            
      
Node* LinkedList::getHead() const {
    return head;
}
      
      
      
      
    