#include "Account.h"
#include <iomanip>

Account::Account(string id, string name, string type, double initialBalance)
    : accountID(id), name(name), type(type), balance(initialBalance), initialBalance(initialBalance) {}

string Account::getAccountID() const { return accountID; }
string Account::getName() const { return name; }
string Account::getType() const { return type; }
double Account::getBalance() const { return balance; }
double Account::getInitialBalance() const { return initialBalance; }

void Account::deposit(double amount) {
    if (amount <= 0) {
        cout << "  Error: Deposit amount must be positive." << endl;
        return;
    }
    
    if (type == "Credit Card") {
        balance -= amount; // Decreases credit card debt
        cout << "  Success: Paid off NLe" << amount << " of credit debt on " << name << "." << endl;
    } else {
        balance += amount; // Increases checking/savings
        cout << "  Success: Deposited NLe" << amount << " into " << name << "." << endl;
    }
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        cout << "  Error: Transaction amount must be positive." << endl;
        return false;
    }
    
    if (type == "Savings") {
        if (balance - amount < 0) {
            cout << "  Error: Insufficient funds in Savings account " << name << ". Transaction rejected." << endl;
            return false;
        }
        balance -= amount;
    } else if (type == "Credit Card") {
        double creditLimit = 5000.0; // Standard credit limit
        if (balance + amount > creditLimit) {
            cout << "  Error: Transaction exceeds credit limit of NLe" << creditLimit << " on " << name << ". Transaction rejected." << endl;
            return false;
        }
        balance += amount; // Increases debt
    } else { // Checking or others
        if (balance - amount < 0) {
            cout << "  Warning: Account " << name << " is overdrafted! Current Balance: NLe" << (balance - amount) << endl;
        }
        balance -= amount;
    }
    
    cout << "  Success: Charged NLe" << amount << " to account " << name << "." << endl;
    return true;
}

void Account::display() const {
    cout << "  Account ID: " << left << setw(8) << accountID 
         << " | Name: " << setw(20) << name 
         << " | Type: " << setw(12) << type;
    
    if (type == "Credit Card") {
        cout << " | Debt: NLe" << fixed << setprecision(2) << balance << " (Owed)";
    } else {
        cout << " | Balance: NLe" << fixed << setprecision(2) << balance;
    }
    cout << endl;
}
