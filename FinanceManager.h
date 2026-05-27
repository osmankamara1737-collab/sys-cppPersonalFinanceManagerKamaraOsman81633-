#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include <vector>
#include <string>
#include "Account.h"
#include "Transaction.h"
#include "Budget.h"

using namespace std;

class FinanceManager {
public:
    FinanceManager(string managerName);
    
    string getManagerName() const;
    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getNetSavings() const;
    double getSavingsRate() const;
    double getNetWorth() const;
    
    // Entity management
    void addAccount(const Account& acc);
    void addTransaction(const Transaction& tx);
    void setBudget(string category, double limit);
    
    // Search
    Account* findAccount(string accountID);
    Budget* findBudget(string category);
    Transaction* findTransaction(string transactionID);
    
    // Core processes
    bool recordTransaction(string accountID, string category, string description, double amount, string type, string date);
    bool transferFunds(string fromAccountID, string toAccountID, double amount, string date);
    
    // Listings
    void listAccounts() const;
    void listTransactions() const;
    void listBudgets() const;
    void listTransactionsByAccount(string accountID) const;
    void listTransactionsByCategory(string category) const;
    
    // Reports & Analytics
    void displayFinancialReport() const;
    void displayFullStatus() const;
    void displayCategoryBreakdown() const;
    
    // Administrative
    void clearData();

private:
    string managerName;
    vector<Account> accounts;
    vector<Transaction> transactions;
    vector<Budget> budgets;
    double totalIncome;
    double totalExpenses;
};

#endif // FINANCEMANAGER_H
