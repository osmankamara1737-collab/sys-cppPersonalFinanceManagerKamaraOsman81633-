#ifndef BUDGET_H
#define BUDGET_H

#include <iostream>
#include <string>

using namespace std;

class Budget {
public:
    Budget(string category, double limitAmount);
    
    string getCategory() const;
    double getLimitAmount() const;
    double getSpentAmount() const;
    double getRemainingBudget() const;
    double getPercentageUsed() const;
    
    void addExpense(double amount);
    void resetSpent();
    void setLimit(double limit);
    void display() const;

private:
    string category;
    double limitAmount;
    double spentAmount;
};

#endif // BUDGET_H
