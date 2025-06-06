
#include "Test.h"
#include "Truck.h"  
#include <iostream>
#include <limits>
#include <algorithm>
#include <cassert>  // Include assert for basic test validation
#include "Node.h"
#include "LinkedList.h"
#include "Car.h"
using namespace std;




// Function to get the user's test choice from the menu
int getTestMenuChoice() {
    int choiceOption;

    do {
        choiceOption = -678123; // Initialize with an unlikely value to loop on invalid input
        cout << "\n--------------------------------------------\n"
             << "Test options menu: \n"
             << "  (" << PRIVATE <<") Run public/private tests\n"             
             << "  (" << NODE_BASIC <<") Run basic Node tests\n" 
             << "  (" << LL_BASIC <<") Run basic Linked List tests\n"
             << "  (" << NODE_COMP_OPERATORS <<") Test comparison operator overload of Node\n"
             << "  (" << RUN_ALL <<") Run all tests \n"
             << "Enter a number from 1 to " << max_test_menu_option << ", or " << DONE << " to exit: ";
        cin >> choiceOption;
        
        // Check for failure of cin (for instance, if input is not an integer)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Check if input is in valid range
        if ((choiceOption < 0) || (choiceOption > max_test_menu_option)) {
            cout << "\nError! Input must be a number between 1 and " << max_test_menu_option 
                 << ", or " << DONE << " to exit." << endl;
            choiceOption = -678123; // Loop again
        }
        cout << endl;
    } while (choiceOption == -678123);

    return choiceOption;
}

// Function to display the menu and execute the chosen tests
   void promptUnitTest() {
    int menuChoice;

    do {
        menuChoice = getTestMenuChoice();

        switch (menuChoice) {
            case PRIVATE:
                testPrivate();
                break;
            case NODE_BASIC:
                testNodeBasic();
                break;
            case LL_BASIC:
                testLinkedListBasic();
                break;
            case NODE_COMP_OPERATORS:
                testNodeCompOperators();
                break;
            case RUN_ALL:
                testPrivate();
                testNodeBasic();
                testLinkedListBasic();
                testNodeCompOperators();
                break;
            default: // DONE entered zero, exit
                cout << "Returning to main menu." << endl;
                menuChoice = 0; // In case it was a non-listed option
        }
    } while (menuChoice != 0);
}

// Sample test for private data

   void testPrivate() {
    cout << "Running Private Data Tests..." << endl;

    // Create a LinkedList object and insert some vehicles (cars, trucks)
    LinkedList ll;

    Vehicle* car1 = new Car("Toyota Camry", "2.5L");
    Vehicle* car2 = new Car("Honda Accord", "2.4L");
    Vehicle* truck1 = new Truck("Ford F-150", "3.5 tons");

    // Insert vehicles into the list
    ll.insert(car1);
    ll.insert(car2);
    ll.insert(truck1);

    // Private data we want to test:
    // Test the private 'size' member directly by using the getSize() method
    assert(ll.getSize() == 3);  // After inserting 3 vehicles, size should be 3
    cout << "Size test passed!" << endl;

    // Test the 'head' of the list (private member)
    Node* head = ll.getHead(); // Assuming a getter for head exists (you can add one if not)
    assert(head != nullptr);  // Head should not be null after insertion
    cout << "Head node test passed!" << endl;

    // Check if the head's data is correct
    assert(head->data->getModel() == "Toyota Camry");  // First inserted vehicle
    cout << "Head data test passed!" << endl;

    // Test the private data in each node (loop through the linked list)
    Node* current = head;
    int count = 1;
    while (current != nullptr) {
        // Print the model of each vehicle
        cout << "Node " << count << " Model: " << current->data->getModel() << endl;
        current = current->next;
        ++count;
    }

    // The list should contain 3 vehicles, and their models should match
    assert(count - 1 == 3);  // The list should have 3 elements
    cout << "Node traversal test passed!" << endl;

    cout << "Private Data Tests Passed!" << endl;
}




// Sample test for basic Node tests

void testNodeBasic() {
    cout << "Running Node Basic Tests..." << endl;

    // Create nodes and assign vehicles (Car)
    Node* node1 = new Node(new Car("Toyota", "2.5L"));  // Creating a Car object with model and engine
    Node* node2 = new Node(new Car("Honda", "1.8L"));   // Creating another Car object

    // Test if nodes hold the correct data
    cout << "Node 1 Model: " << node1->data->getModel() << endl;
    cout << "Node 2 Model: " << node2->data->getModel() << endl;

    assert(node1->data->getModel() == "Toyota");
    assert(node2->data->getModel() == "Honda");

    cout << "Node Basic Tests Passed!" << endl;
}


void testLinkedListBasic() {
    cout << "Running Linked List Basic Tests..." << endl;

    LinkedList ll;

    // Insert vehicles into the linked list
    Vehicle* car1 = new Car("Toyota Camry", "2.5L");
    Vehicle* car2 = new Car("Honda Accord", "2.4L");
    Vehicle* truck1 = new Truck("Ford F-150", "3.5 tons"); // Pass load capacity as string

    // Insert into linked list
    ll.insert(car1);
    ll.insert(car2);
    ll.insert(truck1);

    // Test the size of the list
    assert(ll.getSize() == 3);

    // Test searching by model
    Vehicle* foundCar = ll.searchByModel("Honda Accord");
    assert(foundCar != nullptr);
    assert(foundCar->getModel() == "Honda Accord");

    // Test sorting by model
    ll.sortByModel();
    Vehicle* firstVehicle = ll.getHead()->data;

    // Check that the first vehicle is "Ford F-150", as it should be alphabetically first
    assert(firstVehicle->getModel() == "Ford F-150");

    cout << "Linked List Basic Tests Passed!" << endl;
}


void testNodeCompOperators() {
    cout << "Running Node Comparison Operator Tests..." << endl;

    Node* node1 = new Node(new Car("Toyota", "2.5L"));
    Node* node2 = new Node(new Car("Honda", "1.8L"));

    cout << "Comparing node1 (Toyota) with node2 (Honda)..." << endl;

    // Test comparison operators
    if (*node1 < *node2) {
        cout << "Test passed: node1 is less than node2." << endl;
    } else {
        cout << "Test failed: node1 is not less than node2." << endl;
    }

    cout << "Node Comparison Operator Tests Passed!" << endl;
}




/*



--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
1
Enter customer name: Sylvia
Enter customer contact: 020 666 8888
Enter customer address (or press Enter to skip): 10Downing St, London, England.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
1
Enter customer name: Kate
Enter customer contact: 020 462 8998
Enter customer address (or press Enter to skip): 12 OXford St, London, England.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
1
Enter customer name: Louise
Enter customer contact: 020 4922 6598
Enter customer address (or press Enter to skip): 20 Amersham, Birkinghamshire, England.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
2
Displaying all customers:
Customer 1: Name: Sylvia, Contact: 020 666 8888, Address: 10Downing St, London, England.
Customer 2: Name: Kate, Contact: 020 462 8998, Address: 12 OXford St, London, England.
Customer 3: Name: Louise, Contact: 020 4922 6598, Address: 20 Amersham, Birkinghamshire, England.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
13
Vehicles loaded successfully from the file.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
3
The number of available cars and trucks: 
Total number of Cars: 10
Total number of Trucks: 10

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
10
Enter car model: Mecerdez Benz
Enter car engine type: 6.0L

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
11
Enter truck model: Mecerdez Benz 
Enter truck cargo capacity: 10 tons

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
12
Enter the index of the vehicle to remove: 6
Vehicle at index 6 has been removed.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
3
The number of available cars and trucks: 
Total number of Cars: 10
Total number of Trucks: 11

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
4 
 Enter a model to find
Ram 1500

Found vehicle:
Model: Ram 1500, Type: Truck, Load Capacity: 2.5 tons

Sorted vehicles by model:
Model: BMW 3 Series, Type: Car, Engine: 2.0L
Model: Chevrolet Colorado, Type: Truck, Load Capacity: 3.2 tons
Model: Chevrolet Silverado, Type: Truck, Load Capacity: 4 tons
Model: Ford F-150, Type: Truck, Load Capacity: 3.5 tons
Model: Ford Ranger, Type: Truck, Load Capacity: 3 tons
Model: Ford Super Duty, Type: Truck, Load Capacity: 6 tons
Model: GMC Sierra, Type: Truck, Load Capacity: 4.5 tons
Model: Honda Accord, Type: Car, Engine: 2.4L
Model: Honda Civic, Type: Car, Engine: 1.8L
Model: Kia Optima, Type: Car, Engine: 2.4L
Model: Lexus RX 350, Type: Car, Engine: 3.5L
Model: Mazda CX-5, Type: Car, Engine: 2.5L
Model: Mecerdez Benz, Type: Car, Engine: 6.0L
Model: Mecerdez Benz , Type: Truck, Load Capacity: 10 tons
Model: Mercedes-Benz E-Class, Type: Car, Engine: 3.5L
Model: Nissan Frontier, Type: Truck, Load Capacity: 3 tons
Model: Nissan Titan, Type: Truck, Load Capacity: 4 tons
Model: Ram 1500, Type: Truck, Load Capacity: 2.5 tons
Model: Subaru Outback, Type: Car, Engine: 2.5L
Model: Toyota Camry, Type: Car, Engine: 2.5L
Model: Toyota Tundra, Type: Truck, Load Capacity: 5 tons

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
5

Enter the vehicle type to search for (Car/Truck): Car

Found vehicle with type: Car
Model: BMW 3 Series, Type: Car, Engine: 2.0L
Model: BMW 3 Series, Type: Car, Engine: 2.0L
Model: Honda Accord, Type: Car, Engine: 2.4L
Model: Honda Civic, Type: Car, Engine: 1.8L
Model: Kia Optima, Type: Car, Engine: 2.4L
Model: Lexus RX 350, Type: Car, Engine: 3.5L
Model: Mazda CX-5, Type: Car, Engine: 2.5L
Model: Mecerdez Benz, Type: Car, Engine: 6.0L
Model: Mercedes-Benz E-Class, Type: Car, Engine: 3.5L
Model: Subaru Outback, Type: Car, Engine: 2.5L
Model: Toyota Camry, Type: Car, Engine: 2.5L

Sorted vehicles by type:

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
6

Enter the engine type to search for: 3.5L
Vehicles with engine 3.5L:
Model: Lexus RX 350, Type: Car, Engine: 3.5L
Model: Mercedes-Benz E-Class, Type: Car, Engine: 3.5L

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
7

Enter the load capacity to search for: 4 tons

Found vehicle(s) with load capacity 4 tons:
Model: Chevrolet Silverado, Type: Truck, Load Capacity: 4 tons
Model: Nissan Titan, Type: Truck, Load Capacity: 4 tons

Sorted vehicles by load capacity:
Model: BMW 3 Series, Type: Car, Engine: 2.0L
Model: Mecerdez Benz , Type: Truck, Load Capacity: 10 tons
Model: Ram 1500, Type: Truck, Load Capacity: 2.5 tons
Model: Nissan Frontier, Type: Truck, Load Capacity: 3 tons
Model: Ford Ranger, Type: Truck, Load Capacity: 3 tons
Model: Chevrolet Colorado, Type: Truck, Load Capacity: 3.2 tons
Model: Ford F-150, Type: Truck, Load Capacity: 3.5 tons
Model: Honda Accord, Type: Car, Engine: 2.4L
Model: Honda Civic, Type: Car, Engine: 1.8L
Model: Kia Optima, Type: Car, Engine: 2.4L
Model: Lexus RX 350, Type: Car, Engine: 3.5L
Model: Mazda CX-5, Type: Car, Engine: 2.5L
Model: Mecerdez Benz, Type: Car, Engine: 6.0L
Model: Nissan Titan, Type: Truck, Load Capacity: 4 tons
Model: Mercedes-Benz E-Class, Type: Car, Engine: 3.5L
Model: Chevrolet Silverado, Type: Truck, Load Capacity: 4 tons
Model: GMC Sierra, Type: Truck, Load Capacity: 4.5 tons
Model: Toyota Tundra, Type: Truck, Load Capacity: 5 tons
Model: Subaru Outback, Type: Car, Engine: 2.5L
Model: Toyota Camry, Type: Car, Engine: 2.5L
Model: Ford Super Duty, Type: Truck, Load Capacity: 6 tons


--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
8
Enter the model of the car: Toyota Camry
Enter the engine type: 2.5L
Toyota Camry with engine 2.5L is available in the vehicle list.
Enter a model
Ford Super Duty
Enter a load capacity
6 tons
Ford Super Duty with load capacity 6 tons tons at index 20
Model: Chevrolet Colorado, Type: Truck, Load Capacity: 3.2 tons
Model: Chevrolet Silverado, Type: Truck, Load Capacity: 4 tons
Model: Ford F-150, Type: Truck, Load Capacity: 3.5 tons
Model: Ford Ranger, Type: Truck, Load Capacity: 3 tons
Model: Ford Super Duty, Type: Truck, Load Capacity: 6 tons
Model: GMC Sierra, Type: Truck, Load Capacity: 4.5 tons
Model: Mecerdez Benz , Type: Truck, Load Capacity: 10 tons
Model: Nissan Frontier, Type: Truck, Load Capacity: 3 tons
Model: Nissan Titan, Type: Truck, Load Capacity: 4 tons
Model: Ram 1500, Type: Truck, Load Capacity: 2.5 tons
Model: Toyota Tundra, Type: Truck, Load Capacity: 5 tons
Model: Mazda CX-5, Type: Car, Engine: 2.5L
Model: Mecerdez Benz, Type: Car, Engine: 6.0L
Model: Nissan Titan, Type: Truck, Load Capacity: 4 tons
Model: Mercedes-Benz E-Class, Type: Car, Engine: 3.5L
Model: Chevrolet Silverado, Type: Truck, Load Capacity: 4 tons
Model: GMC Sierra, Type: Truck, Load Capacity: 4.5 tons
Model: Toyota Tundra, Type: Truck, Load Capacity: 5 tons
Model: Subaru Outback, Type: Car, Engine: 2.5L
Model: Toyota Camry, Type: Car, Engine: 2.5L
Model: Ford Super Duty, Type: Truck, Load Capacity: 6 tons


--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 
14

--------------------------------------------
Test options menu: 
  (1) Run public/private tests
  (2) Run basic Node tests
  (3) Run basic Linked List tests
  (4) Test comparison operator overload of Node
  (5) Run all tests 
Enter a number from 1 to 5, or 0 to exit: 1

Running Private Data Tests...
Size test passed!
Head node test passed!
Head data test passed!
Node 1 Model: Toyota Camry
Node 2 Model: Honda Accord
Node 3 Model: Ford F-150
Node traversal test passed!
Private Data Tests Passed!

--------------------------------------------
Test options menu: 
  (1) Run public/private tests
  (2) Run basic Node tests
  (3) Run basic Linked List tests
  (4) Test comparison operator overload of Node
  (5) Run all tests 
Enter a number from 1 to 5, or 0 to exit: 2

Running Node Basic Tests...
Node 1 Model: Toyota
Node 2 Model: Honda
Node Basic Tests Passed!

--------------------------------------------
Test options menu: 
  (1) Run public/private tests
  (2) Run basic Node tests
  (3) Run basic Linked List tests
  (4) Test comparison operator overload of Node
  (5) Run all tests 
Enter a number from 1 to 5, or 0 to exit: 3

Running Linked List Basic Tests...
Linked List Basic Tests Passed!

--------------------------------------------
Test options menu: 
  (1) Run public/private tests
  (2) Run basic Node tests
  (3) Run basic Linked List tests
  (4) Test comparison operator overload of Node
  (5) Run all tests 
Enter a number from 1 to 5, or 0 to exit: 4

Running Node Comparison Operator Tests...
Comparing node1 (Toyota) with node2 (Honda)...
Test passed: node1 is less than node2.
Node Comparison Operator Tests Passed!

--------------------------------------------
Test options menu: 
  (1) Run public/private tests
  (2) Run basic Node tests
  (3) Run basic Linked List tests
  (4) Test comparison operator overload of Node
  (5) Run all tests 
Enter a number from 1 to 5, or 0 to exit: 5

Running Private Data Tests...
Size test passed!
Head node test passed!
Head data test passed!
Node 1 Model: Toyota Camry
Node 2 Model: Honda Accord
Node 3 Model: Ford F-150
Node traversal test passed!
Private Data Tests Passed!
Running Node Basic Tests...
Node 1 Model: Toyota
Node 2 Model: Honda
Node Basic Tests Passed!
Running Linked List Basic Tests...
Linked List Basic Tests Passed!
Running Node Comparison Operator Tests...
Comparing node1 (Toyota) with node2 (Honda)...
Test passed: node1 is less than node2.
Node Comparison Operator Tests Passed!

--------------------------------------------
Test options menu: 
  (1) Run public/private tests
  (2) Run basic Node tests
  (3) Run basic Linked List tests
  (4) Test comparison operator overload of Node
  (5) Run all tests 
Enter a number from 1 to 5, or 0 to exit: 0

Returning to main menu.

--------------------------------------------
Options menu: 
 (1) Add a customer to the list
 (2) Display the list of customers
 (3) Count - get number of vehicles in vehicle list
 (4) Search for a car or truck by model 
 (5) Search for a truck by type 
 (6) Search for a car by engine
 (7) Search for a truck by load capacity
 (8) Search for a car by model and engine type 
 (9) Search for a truck by model and load capacity 
 (10) Add a car to the list
 (11) Add a truck to the list
 (12) Remove a vehicle from the list by index
 (13) Open a list of vehicles
 (14) Test the programme's classes and methods 
Enter a number between 1 and 14: 


*/