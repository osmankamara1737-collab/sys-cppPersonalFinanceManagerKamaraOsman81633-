#include "Transaction.h"
#include <iomanip>

Transaction::Transaction(string id, string accountId, string category, string description, double amount, string type, string date)
    : transactionID(id), accountID(accountId), category(category), description(description),
      amount(amount), type(type), date(date) {}

string Transaction::getTransactionID() const { return transactionID; }
string Transaction::getAccountID() const { return accountID; }
string Transaction::getCategory() const { return category; }
string Transaction::getDescription() const { return description; }
double Transaction::getAmount() const { return amount; }
string Transaction::getType() const { return type; }
string Transaction::getDate() const { return date; }

void Transaction::display() const {
    string typeIndicator = (type == "Income") ? " [+] " : ((type == "Expense") ? " [-] " : " [~] ");
    cout << "  TX ID: " << left << setw(8) << transactionID 
         << " | Date: " << setw(11) << date 
         << " | Account: " << setw(8) << accountID 
         << " | " << typeIndicator << "NLe" << setw(8) << fixed << setprecision(2) << amount 
         << " | Category: " << setw(14) << category 
         << " | Desc: " << description << endl;
}
