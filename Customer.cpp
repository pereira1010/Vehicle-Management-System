// Customer.cpp

#include<sstream>
#include <fstream> 
#include "Customer.h" 
using namespace std;


// Constructor
Customer::Customer(const string& name, const string& contact, const string& address,
                   const string& email, int usageCount, const string& userName,
                   const string& passWord)
    : name(name), contact(contact), address(address), email(email),
      usageCount(usageCount), userName(userName), passWord(passWord) {}

// Display customer information
void Customer::display() const {
    	cout << "Name: " << name << ", Contact: " << contact;
        if (!address.empty()) {
        cout << ", Address: " << address;  // Display address only if provided
    }
    cout << ", Email: " << email << ", Usage Count: " << usageCount << endl;
}

// Getters
 string Customer::getName() const { return name; }
 string Customer::getContact() const { return contact; }
 string Customer::getAddress() const { return address; }
 string Customer::getEmail() const { return email; }
 int Customer::getUsageCount() const { return usageCount; }
 string Customer::getUsername() const { return userName; }
 string Customer::getPassword() const { return passWord; }

// Update methods
 void Customer::updateContact(const string& newContact) {
    contact = newContact;
}

void Customer::updateAddress(const string& newAddress) {
    address = newAddress;
}

void Customer::updateEmail(const string& newEmail) {
    email = newEmail;
}

// Convert customer details to a string
   string Customer::toString() const {
    return name + "|" + contact + "|" + address + "|" + email + "|" +
           std::to_string(usageCount) + "|" + userName + "|" + passWord;
}