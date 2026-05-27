#include "FinanceManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

FinanceManager::FinanceManager(string managerName)
    : managerName(managerName), totalIncome(0.0), totalExpenses(0.0) {}

string FinanceManager::getManagerName() const { return managerName; }
double FinanceManager::getTotalIncome() const { return totalIncome; }
double FinanceManager::getTotalExpenses() const { return totalExpenses; }
double FinanceManager::getNetSavings() const { return totalIncome - totalExpenses; }

double FinanceManager::getSavingsRate() const {
    if (totalIncome <= 0) return 0.0;
    return (getNetSavings() / totalIncome) * 100.0;
}

double FinanceManager::getNetWorth() const {
    double netWorth = 0.0;
    for (const auto& acc : accounts) {
        if (acc.getType() == "Credit Card") {
            netWorth -= acc.getBalance(); // Subtract credit card debt
        } else {
            netWorth += acc.getBalance(); // Add checking/savings
        }
    }
    return netWorth;
}

// Entity management
void FinanceManager::addAccount(const Account& acc) {
    for (const auto& existing : accounts) {
        if (existing.getAccountID() == acc.getAccountID()) {
            cout << "  \033[1;31mError: Account ID " << acc.getAccountID() << " already exists.\033[0m" << endl;
            return;
        }
    }
    accounts.push_back(acc);
    cout << "  \033[1;32mSuccess: Created account " << acc.getAccountID() << " (" << acc.getName() << ")\033[0m" << endl;
}

void FinanceManager::addTransaction(const Transaction& tx) {
    transactions.push_back(tx);
    
    // Aggregate overall totals based on new transaction
    if (tx.getType() == "Income") {
        totalIncome += tx.getAmount();
    } else if (tx.getType() == "Expense") {
        totalExpenses += tx.getAmount();
        
        // Also update the budget spent if it matches
        Budget* b = findBudget(tx.getCategory());
        if (b) {
            b->addExpense(tx.getAmount());
        }
    }
}

void FinanceManager::setBudget(string category, double limit) {
    Budget* existing = findBudget(category);
    if (existing) {
        existing->setLimit(limit);
        cout << "  \033[1;32mSuccess: Updated budget for " << category << " to NLe" << limit << ".\033[0m" << endl;
    } else {
        budgets.push_back(Budget(category, limit));
        cout << "  \033[1;32mSuccess: Created new budget for " << category << " with limit NLe" << limit << ".\033[0m" << endl;
    }
}

// Search
Account* FinanceManager::findAccount(string accountID) {
    for (auto& acc : accounts) {
        if (acc.getAccountID() == accountID) return &acc;
    }
    return nullptr;
}

Budget* FinanceManager::findBudget(string category) {
    // Case-insensitive/exact match helper
    for (auto& b : budgets) {
        if (b.getCategory() == category) return &b;
    }
    return nullptr;
}

Transaction* FinanceManager::findTransaction(string transactionID) {
    for (auto& tx : transactions) {
        if (tx.getTransactionID() == transactionID) return &tx;
    }
    return nullptr;
}

// Core processes
bool FinanceManager::recordTransaction(string accountID, string category, string description, double amount, string type, string date) {
    Account* acc = findAccount(accountID);
    if (!acc) {
        cout << "  \033[1;31mError: Account " << accountID << " not found.\033[0m" << endl;
        return false;
    }
    
    // Execute balance change
    if (type == "Expense") {
        if (!acc->withdraw(amount)) {
            cout << "  \033[1;31mError: Transaction failed due to account constraints.\033[0m" << endl;
            return false;
        }
    } else if (type == "Income") {
        acc->deposit(amount);
    } else if (type == "Transfer") {
        // Handled specifically in transferFunds, but if done directly:
        // We will just post it
    } else {
        cout << "  \033[1;31mError: Invalid transaction type " << type << ".\033[0m" << endl;
        return false;
    }
    
    // Generate transaction ID
    string nextID = "TXN" + string(3 - to_string(transactions.size() + 1).length(), '0') + to_string(transactions.size() + 1);
    
    Transaction newTx(nextID, accountID, category, description, amount, type, date);
    addTransaction(newTx);
    
    return true;
}

bool FinanceManager::transferFunds(string fromAccountID, string toAccountID, double amount, string date) {
    Account* fromAcc = findAccount(fromAccountID);
    Account* toAcc = findAccount(toAccountID);
    
    if (!fromAcc) {
        cout << "  \033[1;31mError: Source Account " << fromAccountID << " not found.\033[0m" << endl;
        return false;
    }
    if (!toAcc) {
        cout << "  \033[1;31mError: Destination Account " << toAccountID << " not found.\033[0m" << endl;
        return false;
    }
    if (amount <= 0) {
        cout << "  \033[1;31mError: Transfer amount must be positive.\033[0m" << endl;
        return false;
    }
    
    // Perform transfer
    cout << "  Attempting to transfer NLe" << amount << " from " << fromAcc->getName() << " to " << toAcc->getName() << "..." << endl;
    if (!fromAcc->withdraw(amount)) {
        cout << "  \033[1;31mError: Transfer failed. Source account rejected withdrawal.\033[0m" << endl;
        return false;
    }
    toAcc->deposit(amount);
    
    // Record transactions for both accounts to maintain audit trail
    string txID1 = "TXN" + string(3 - to_string(transactions.size() + 1).length(), '0') + to_string(transactions.size() + 1);
    Transaction outTx(txID1, fromAccountID, "Transfer", "Transfer Out to " + toAcc->getName(), amount, "Transfer", date);
    transactions.push_back(outTx);
    
    string txID2 = "TXN" + string(3 - to_string(transactions.size() + 1).length(), '0') + to_string(transactions.size() + 1);
    Transaction inTx(txID2, toAccountID, "Transfer", "Transfer In from " + fromAcc->getName(), amount, "Transfer", date);
    transactions.push_back(inTx);
    
    cout << "  \033[1;32mSuccess: Transferred NLe" << amount << " successfully.\033[0m" << endl;
    return true;
}

// Listings
void FinanceManager::listAccounts() const {
    cout << "\n========================================================" << endl;
    cout << "   FINANCIAL ACCOUNTS (" << accounts.size() << ")" << endl;
    cout << "========================================================" << endl;
    if (accounts.empty()) {
        cout << "  No accounts registered yet." << endl;
        return;
    }
    for (const auto& acc : accounts) {
        acc.display();
    }
    cout << "--------------------------------------------------------" << endl;
    cout << "  Total Net Worth: \033[1;36mNLe" << fixed << setprecision(2) << getNetWorth() << "\033[0m" << endl;
    cout << "========================================================" << endl;
}

void FinanceManager::listTransactions() const {
    cout << "\n==========================================================================================" << endl;
    cout << "   TRANSACTION HISTORY (" << transactions.size() << ")" << endl;
    cout << "==========================================================================================" << endl;
    if (transactions.empty()) {
        cout << "  No transactions recorded yet." << endl;
        return;
    }
    // List in reverse order (most recent first) to feel like a modern banking feed
    for (auto it = transactions.rbegin(); it != transactions.rend(); ++it) {
        it->display();
    }
    cout << "==========================================================================================" << endl;
}

void FinanceManager::listBudgets() const {
    cout << "\n=======================================================================================" << endl;
    cout << "   BUDGETS & SPENDING LIMITS (" << budgets.size() << ")" << endl;
    cout << "=======================================================================================" << endl;
    if (budgets.empty()) {
        cout << "  No budgets configured yet." << endl;
        return;
    }
    for (const auto& b : budgets) {
        b.display();
    }
    cout << "=======================================================================================" << endl;
}

void FinanceManager::listTransactionsByAccount(string accountID) const {
    cout << "\n==========================================================================================" << endl;
    cout << "   TRANSACTIONS FOR ACCOUNT: " << accountID << endl;
    cout << "==========================================================================================" << endl;
    bool found = false;
    for (auto it = transactions.rbegin(); it != transactions.rend(); ++it) {
        if (it->getAccountID() == accountID) {
            it->display();
            found = true;
        }
    }
    if (!found) {
        cout << "  No transactions found for account " << accountID << "." << endl;
    }
    cout << "==========================================================================================" << endl;
}

void FinanceManager::listTransactionsByCategory(string category) const {
    cout << "\n==========================================================================================" << endl;
    cout << "   TRANSACTIONS FOR CATEGORY: " << category << endl;
    cout << "==========================================================================================" << endl;
    bool found = false;
    for (auto it = transactions.rbegin(); it != transactions.rend(); ++it) {
        // Case insensitive or case-sensitive match
        if (it->getCategory() == category) {
            it->display();
            found = true;
        }
    }
    if (!found) {
        cout << "  No transactions found in category " << category << "." << endl;
    }
    cout << "==========================================================================================" << endl;
}

// Reports & Analytics
void FinanceManager::displayFinancialReport() const {
    cout << "\n==================================================" << endl;
    cout << "   FINANCIAL PERFORMANCE SUMMARY: " << managerName << endl;
    cout << "==================================================" << endl;
    cout << "  Total Income:         \033[1;32mNLe" << fixed << setprecision(2) << totalIncome << "\033[0m" << endl;
    cout << "  Total Expenses:       \033[1;31mNLe" << totalExpenses << "\033[0m" << endl;
    cout << "--------------------------------------------------" << endl;
    double net = getNetSavings();
    if (net >= 0) {
        cout << "  Net Savings:          \033[1;32mNLe" << net << "\033[0m" << endl;
    } else {
        cout << "  Net Deficit:          \033[1;31mNLe" << -net << "\033[0m" << endl;
    }
    cout << "  Savings Rate:         \033[1;36m" << fixed << setprecision(1) << getSavingsRate() << "%\033[0m" << endl;
    cout << "  Overall Net Worth:    \033[1;36mNLe" << getNetWorth() << "\033[0m" << endl;
    cout << "==================================================" << endl;
}

void FinanceManager::displayCategoryBreakdown() const {
    cout << "\n===============================================" << endl;
    cout << "   EXPENSE BREAKDOWN BY CATEGORY" << endl;
    cout << "===============================================" << endl;
    
    map<string, double> catMap;
    double totalExp = 0.0;
    
    for (const auto& tx : transactions) {
        if (tx.getType() == "Expense") {
            catMap[tx.getCategory()] += tx.getAmount();
            totalExp += tx.getAmount();
        }
    }
    
    if (catMap.empty()) {
        cout << "  No expenses recorded yet to analyze." << endl;
        cout << "===============================================" << endl;
        return;
    }
    
    // Sort & print
    for (const auto& pair : catMap) {
        double pct = (pair.second / totalExp) * 100.0;
        int barWidth = 10;
        int filled = static_cast<int>((pct / 100.0) * barWidth);
        
        cout << "  " << left << setw(15) << pair.first 
             << " : NLe" << right << setw(7) << fixed << setprecision(2) << pair.second
             << " | " << setw(5) << fixed << setprecision(1) << pct << "%  [";
             
        for (int i = 0; i < barWidth; ++i) {
            if (i < filled) cout << "█";
            else cout << ".";
        }
        cout << "]" << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "  Total Expenses Analyzed: NLe" << fixed << setprecision(2) << totalExp << endl;
    cout << "===============================================" << endl;
}

void FinanceManager::displayFullStatus() const {
    cout << "\n==========================================================================" << endl;
    cout << "   COMPLETE FINANCIAL STATUS REPORT: " << managerName << endl;
    cout << "==========================================================================" << endl;
    listAccounts();
    listBudgets();
    displayCategoryBreakdown();
    displayFinancialReport();
    cout << "==========================================================================" << endl;
}

void FinanceManager::clearData() {
    accounts.clear();
    transactions.clear();
    budgets.clear();
    totalIncome = 0.0;
    totalExpenses = 0.0;
    cout << "  \033[1;32mSuccess: All financial data has been cleared.\033[0m" << endl;
}
