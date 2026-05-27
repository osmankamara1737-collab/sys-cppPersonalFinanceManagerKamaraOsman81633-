#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include "Account.h"
#include "Transaction.h"
#include "Budget.h"
#include "FinanceManager.h"

using namespace std;

// Utility: clear the input stream buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showWelcome() {
    cout << "\n\033[1;36m+-------------------------------------------------------+\n"
         << "|     Welcome to Bockarie's Personal Finance System     |\n"
         << "|       Premium Console Wealth Management Platform       |\n"
         << "+-------------------------------------------------------+\033[0m\n";
}

void showMenu() {
    cout << "\n\033[1;34m=====================================================\n"
         << "        PERSONAL WEALTH & FINANCE DASHBOARD          \n"
         << "=====================================================\033[0m\n"
         << "  [1]  📊 Display Full Financial Status Report\n"
         << "  [2]  💳 List All Financial Accounts & Balances\n"
         << "  [3]  ➕ Register a New Financial Account\n"
         << "  [4]  💸 Record a Transaction (Income or Expense)\n"
         << "  [5]  📝 List Full Transaction History Feed\n"
         << "  [6]  📅 View Budgets & Category Spending Limits\n"
         << "  [7]  🛡️ Set or Update a Category Budget Limit\n"
         << "  [8]  🔄 Transfer Funds Between Accounts\n"
         << "  [9]  📈 View Expense Breakdown & Spending Analytics\n"
         << "  [10] 🔍 Search & Filter Transactions\n"
         << "  [11] 🧹 Reset / Purge All Financial Data\n"
         << "  [12] 🚪 Exit System\n"
         << "\033[1;34m=====================================================\033[0m\n"
         << "Select an option (1-12): ";
}

int main() {
    // Enable ANSI escapes on Windows console if possible (most modern consoles support this natively)
    showWelcome();

    // Initialize the Finance Manager System
    FinanceManager manager("Pinto's Premium Wealth Portfolio");

    // Preload some financial accounts
    Account a1("ACC001", "Primary Checking", "Checking", 2500.00);
    Account a2("ACC002", "High-Yield Savings", "Savings", 10000.00);
    Account a3("ACC003", "Cashback Credit Card", "Credit Card", 150.00); // 150.00 current debt

    manager.addAccount(a1);
    manager.addAccount(a2);
    manager.addAccount(a3);

    // Preload budgets
    manager.setBudget("Food", 400.0);
    manager.setBudget("Entertainment", 150.0);
    manager.setBudget("Utilities", 300.0);

    // Preload some transactions to populate history and balances
    manager.recordTransaction("ACC001", "Salary", "Bi-weekly Paycheck", 3000.00, "Income", "2026-05-15");
    manager.recordTransaction("ACC001", "Food", "Supermarket Groceries", 120.00, "Expense", "2026-05-18");
    manager.recordTransaction("ACC003", "Entertainment", "Netflix & Spotify", 45.00, "Expense", "2026-05-20");
    manager.recordTransaction("ACC001", "Utilities", "Electricity Bill", 180.00, "Expense", "2026-05-22");

    int choice = 0;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cout << "  \033[1;31mError: Invalid option. Please enter a valid number.\033[0m\n";
            clearInput();
            continue;
        }

        if (choice == 12) {
            cout << "\n\033[1;32mThank you for managing your wealth with Bockarie's Finance Manager. Stay wealthy! Goodbye!\033[0m\n";
            break;
        }

        switch (choice) {
            case 1:
                manager.displayFullStatus();
                break;

            case 2:
                manager.listAccounts();
                break;

            case 3: {
                string id, name, type;
                double initialBalance;
                cout << "\n--- Register New Financial Account ---\n";
                cout << "  Enter Unique Account ID (e.g. ACC004): ";
                cin >> id;
                cout << "  Enter Account Name (e.g. Vacation Fund): ";
                clearInput();
                getline(cin, name);
                
                int typeChoice = 0;
                cout << "  Select Account Type:\n";
                cout << "    [1] Checking\n";
                cout << "    [2] Savings\n";
                cout << "    [3] Credit Card\n";
                cout << "  Choice (1-3): ";
                while (!(cin >> typeChoice) || typeChoice < 1 || typeChoice > 3) {
                    cout << "    Invalid. Select 1, 2, or 3: ";
                    clearInput();
                }
                
                if (typeChoice == 1) type = "Checking";
                else if (typeChoice == 2) type = "Savings";
                else type = "Credit Card";

                cout << "  Enter Starting Balance / Initial Debt (NLe): ";
                while (!(cin >> initialBalance) || initialBalance < 0) {
                    cout << "    Invalid input. Enter a non-negative balance: ";
                    clearInput();
                }

                Account newAcc(id, name, type, initialBalance);
                manager.addAccount(newAcc);
                break;
            }

            case 4: {
                string accID, category, description, type, date;
                double amount;
                
                cout << "\n--- Record a New Transaction ---\n";
                cout << "  Enter Account ID: ";
                cin >> accID;
                
                Account* test = manager.findAccount(accID);
                if (!test) {
                    cout << "  \033[1;31mError: Account ID not found. Return to menu.\033[0m\n";
                    break;
                }

                int typeChoice = 0;
                cout << "  Select Transaction Type:\n";
                cout << "    [1] Expense (Withdrawal / Charge)\n";
                cout << "    [2] Income (Deposit / Paycheck)\n";
                cout << "  Choice (1-2): ";
                while (!(cin >> typeChoice) || typeChoice < 1 || typeChoice > 2) {
                    cout << "    Invalid. Select 1 or 2: ";
                    clearInput();
                }
                type = (typeChoice == 1) ? "Expense" : "Income";

                cout << "  Enter Category (e.g. Food, Salary, Rent, Entertainment): ";
                clearInput();
                getline(cin, category);
                
                cout << "  Enter Brief Description: ";
                getline(cin, description);
                
                cout << "  Enter Transaction Amount (NLe): ";
                while (!(cin >> amount) || amount <= 0) {
                    cout << "    Invalid amount. Enter a positive number: ";
                    clearInput();
                }

                cout << "  Enter Date (YYYY-MM-DD, or press enter / enter '.' for today's default '2026-05-26'): ";
                clearInput();
                getline(cin, date);
                if (date.empty() || date == ".") {
                    date = "2026-05-26";
                }

                manager.recordTransaction(accID, category, description, amount, type, date);
                break;
            }

            case 5:
                manager.listTransactions();
                break;

            case 6:
                manager.listBudgets();
                break;

            case 7: {
                string category;
                double limit;
                cout << "\n--- Configure Category Budget Limit ---\n";
                cout << "  Enter Expense Category Name (e.g. Food): ";
                clearInput();
                getline(cin, category);
                cout << "  Enter Budget Monthly Limit (NLe): ";
                while (!(cin >> limit) || limit < 0) {
                    cout << "    Invalid input. Enter a positive limit: ";
                    clearInput();
                }
                manager.setBudget(category, limit);
                break;
            }

            case 8: {
                string fromID, toID, date;
                double amount;
                cout << "\n--- Transfer Funds Between Accounts ---\n";
                cout << "  Enter Source Account ID (Transfer Out): ";
                cin >> fromID;
                cout << "  Enter Destination Account ID (Transfer In): ";
                cin >> toID;
                
                if (fromID == toID) {
                    cout << "  \033[1;31mError: Source and destination accounts must be different.\033[0m\n";
                    break;
                }

                cout << "  Enter Transfer Amount (NLe): ";
                while (!(cin >> amount) || amount <= 0) {
                    cout << "    Invalid amount. Enter a positive number: ";
                    clearInput();
                }

                cout << "  Enter Transfer Date (YYYY-MM-DD, or press enter for default): ";
                clearInput();
                getline(cin, date);
                if (date.empty() || date == ".") {
                    date = "2026-05-26";
                }

                manager.transferFunds(fromID, toID, amount, date);
                break;
            }

            case 9:
                manager.displayCategoryBreakdown();
                break;

            case 10: {
                int searchChoice = 0;
                cout << "\n--- Search & Filter Transactions ---\n";
                cout << "  [1] Filter by Account ID\n";
                cout << "  [2] Filter by Category\n";
                cout << "  Select search method (1-2): ";
                while (!(cin >> searchChoice) || searchChoice < 1 || searchChoice > 2) {
                    cout << "    Invalid choice. Enter 1 or 2: ";
                    clearInput();
                }

                if (searchChoice == 1) {
                    string accID;
                    cout << "  Enter Account ID to filter by: ";
                    cin >> accID;
                    manager.listTransactionsByAccount(accID);
                } else {
                    string category;
                    cout << "  Enter Category to filter by: ";
                    clearInput();
                    getline(cin, category);
                    manager.listTransactionsByCategory(category);
                }
                break;
            }

            case 11: {
                char confirm;
                cout << "  \033[1;31;5mWARNING: Are you absolutely sure you want to purge all data? This cannot be undone! (y/N): \033[0m";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    manager.clearData();
                } else {
                    cout << "  Purge cancelled.\n";
                }
                break;
            }

            default:
                cout << "  \033[1;31mError: Invalid option. Choose from 1 to 12.\033[0m\n";
        }
    }

    return 0;
}
