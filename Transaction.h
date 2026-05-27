#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>

using namespace std;

class Transaction {
public:
    Transaction(string id, string accountId, string category, string description, double amount, string type, string date);
    
    string getTransactionID() const;
    string getAccountID() const;
    string getCategory() const;
    string getDescription() const;
    double getAmount() const;
    string getType() const;
    string getDate() const;
    
    void display() const;

private:
    string transactionID;
    string accountID;
    string category;
    string description;
    double amount;
    string type; // Income, Expense, Transfer
    string date; // YYYY-MM-DD
};

#endif // TRANSACTION_H
