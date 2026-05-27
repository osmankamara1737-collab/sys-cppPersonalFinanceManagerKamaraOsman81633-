#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

using namespace std;

class Account {
public:
    Account(string id, string name, string type, double initialBalance = 0.0);
    
    string getAccountID() const;
    string getName() const;
    string getType() const;
    double getBalance() const;
    double getInitialBalance() const;
    
    void deposit(double amount);
    bool withdraw(double amount); // Returns true if successful, false otherwise
    void display() const;

private:
    string accountID;
    string name;
    string type; // Checking, Savings, Credit Card
    double balance;
    double initialBalance;
};

#endif // ACCOUNT_H
