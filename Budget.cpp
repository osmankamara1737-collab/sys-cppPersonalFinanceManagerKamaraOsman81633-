#include "Budget.h"
#include <iomanip>

Budget::Budget(string category, double limitAmount)
    : category(category), limitAmount(limitAmount), spentAmount(0.0) {}

string Budget::getCategory() const { return category; }
double Budget::getLimitAmount() const { return limitAmount; }
double Budget::getSpentAmount() const { return spentAmount; }
double Budget::getRemainingBudget() const { return limitAmount - spentAmount; }

double Budget::getPercentageUsed() const {
    if (limitAmount <= 0) return 0.0;
    return (spentAmount / limitAmount) * 100.0;
}

void Budget::addExpense(double amount) {
    if (amount > 0) {
        spentAmount += amount;
    }
}

void Budget::resetSpent() {
    spentAmount = 0.0;
}

void Budget::setLimit(double limit) {
    if (limit >= 0) {
        limitAmount = limit;
    }
}

void Budget::display() const {
    double pct = getPercentageUsed();
    int barWidth = 15;
    int filled = static_cast<int>((pct / 100.0) * barWidth);
    if (filled > barWidth) filled = barWidth;
    if (filled < 0) filled = 0;
    
    cout << "  Category: " << left << setw(15) << category 
         << " | Limit: NLe" << right << setw(7) << fixed << setprecision(0) << limitAmount 
         << " | Spent: NLe" << setw(7) << spentAmount 
         << " | Remaining: NLe" << setw(7) << getRemainingBudget()
         << " | [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filled) cout << "█";
        else cout << ".";
    }
    cout << "] " << right << setw(5) << fixed << setprecision(1) << pct << "%";
    
    if (pct >= 100.0) {
        cout << "  \033[1;31m[EXCEEDED!]\033[0m"; // ANSI Red
    } else if (pct >= 80.0) {
        cout << "  \033[1;33m[WARNING!]\033[0m";  // ANSI Yellow
    } else {
        cout << "  \033[1;32m[SAFE]\033[0m";     // ANSI Green
    }
    cout << endl;
}
