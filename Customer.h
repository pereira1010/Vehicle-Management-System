//Customer.h


#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <iostream>
using namespace std;


class Customer {
public:
     // Constructor to initialize customer details
    Customer(const string& name, const string& contact, const string& address = "",
             const string& email = "N/A", int usageCount = 0, 
             const string& userName = "", const string& passWord = "");

    // Method to display all customer information
    void display() const;

    // Getters for customer information
    string getName() const;
    string getContact() const;
    string getAddress() const;
    string getEmail() const;
    int getUsageCount() const;
    string getUsername() const;
    string getPassword() const;

    // Update methods
    void updateContact(const string& newContact);
    void updateAddress(const string& newAddress);
    void updateEmail(const string& newEmail);

    // Method to convert customer details to a string for saving
    string toString() const;

private:
    string name;    // Customer's name
    string contact; // Customer's contact information
    string address; // Customer's address (optional)
    string email;   // Customer's email
    int usageCount;      // Count of usage
    string userName; // Username for the account
    string passWord; // Password for the account
};

#endif // CUSTOMER_H