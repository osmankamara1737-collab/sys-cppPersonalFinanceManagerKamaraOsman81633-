# 💵 Personal  Finance Manager

A premium console-based **C++ Personal Finance Manager** built using clean Object-Oriented Programming (OOP) principles. It manages financial accounts (Checking, Savings, Credit Cards), logs transaction logs (Income, Expenses, Transfers), displays budgets with visual progress bars, and generates robust portfolio reports and analytics.

---

## 📋 Table of Contents

- [Overview](#-overview)
- [✨ Features](#-features)
- [📁 Project Structure](#-project-structure)
- [🧩 Classes & Entities](#-classes--entities)
  - [`Account`](#account)
  - [`Transaction`](#transaction)
  - [`Budget`](#budget)
  - [`FinanceManager`](#financemanager)
- [🚀 Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Compile](#compile)
  - [▶️ How to Run](#️-how-to-run)
- [📌 Menu Options](#-menu-options)
- [🗂️ Sample Data (Pre-loaded on Startup)](#️-sample-data-pre-loaded-on-startup)
  - [Accounts](#accounts)
  - [Budgets](#budgets)
  - [Transactions](#transactions)
- [👤 Author](#-author)

---

## Overview

This system is built with robust **Object-Oriented Programming (OOP)** in C++ including **encapsulation**, **abstraction**, and **modular design**. It provides a fully interactive terminal-based portfolio manager, applying ANSI escape colors to highlight positive balances, caution-level budgets, credit card liabilities, and transaction feeds.

---

## ✨ Features

- ✅ **Account Management**: Create and track Checking, Savings, and Credit Card accounts, applying strict withdrawal rules (e.g. Savings cannot go negative, Credit Cards enforce limits).
- ✅ **Double-Entry Transactions**: Records income and expenses, automatically updating associated account balances and category-specific budgets.
- ✅ **Fund Transfers**: Transfer funds seamlessly between accounts with clean validation checks and transaction logging.
- ✅ **Dynamic Budgets**: Create budget category limits with visually stunning real-time ASCII progress bars showing usage and status badges (`[SAFE]`, `[WARNING]`, `[EXCEEDED]`).
- ✅ **Expense Breakdown & Analytics**: Generate category breakdown summaries showing spending percentages and visual graphs.
- ✅ **Full Transaction Search & Filters**: Filter through transaction feeds by Account ID or Category.
- ✅ **Modern Terminal UI**: Utilizes ANSI terminal coloring and elegant menu formatting for premium usability.
- ✅ **Robust Input Validation**: Strict validation for negative numbers, invalid strings, and numeric errors.

---

## 📁 Project Structure

```
c:\Users\Pinto\Downloads\students attendance management system/
│
├── main.cpp                     # Application entry point & interactive dashboard
│
├── Account.h / Account.cpp       # Account class (ID, Name, Type, Balance, Deposits/Withdrawals)
├── Transaction.h / Transaction.cpp # Transaction class (ID, AccountID, Category, Amount, Type, Date)
├── Budget.h / Budget.cpp         # Budget class (Category, Limit, Spent, Progress Bars)
│
├── FinanceManager.h             # Core portfolio controller & aggregator (header)
├── FinanceManager.cpp           # Core portfolio controller & aggregator (implementation)
│
└── FinanceManager.exe           # Compiled executable (Windows)
```

---

## 🧩 Classes & Entities

### `Account`
Represents a user's financial account.

| Field | Type | Description |
|---|---|---|
| `accountID` | `string` | Unique identifier (e.g., ACC001) |
| `name` | `string` | User-defined label (e.g., High-Yield Savings) |
| `type` | `string` | Checking, Savings, or Credit Card |
| `balance` | `double` | Current balance (represents debt if Credit Card) |
| `initialBalance` | `double` | Starting balance on registration |

---

### `Transaction`
Represents an individual financial record.

| Field | Type | Description |
|---|---|---|
| `transactionID` | `string` | Unique ID auto-generated (e.g., TXN001) |
| `accountID` | `string` | Target account ID |
| `category` | `string` | Category (e.g., Salary, Food, Utilities) |
| `description` | `string` | Brief notes (e.g., Groceries) |
| `amount` | `double` | Numeric dollar/currency value |
| `type` | `string` | Income, Expense, or Transfer |
| `date` | `string` | YYYY-MM-DD format |

---

### `Budget`
Represents monthly budgets and trackers.

| Field | Type | Description |
|---|---|---|
| `category` | `string` | Expense category budget is set for |
| `limitAmount` | `double` | Maximum allowed spending limit |
| `spentAmount` | `double` | Current cumulative expenditure |

---

### `FinanceManager`
The central system orchestrator managing accounts, transactions, and budgets.

| Method | Description |
|---|---|
| `addAccount()` | Add a new checking, savings, or credit card |
| `recordTransaction()` | Execute a transaction, updating accounts and budgets |
| `transferFunds()` | Perform fund transfer between two accounts |
| `setBudget()` | Set or adjust category budget limits |
| `listAccounts()` | Show balances and calculate current Net Worth |
| `listTransactions()` | Output full reverse-chronological ledger feed |
| `listBudgets()` | Output all budgets with visual progress bars |
| `displayCategoryBreakdown()`| Summarize expense category allocation and graphs |
| `displayFinancialReport()` | Performance report: savings rate, net wealth |

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting **C++17** or later (e.g., `g++` via MinGW)
- Terminal/PowerShell supporting standard console features

### Compile

Compile the manager using standard compiler arguments:
```bash
g++ -o FinanceManager.exe main.cpp Account.cpp Transaction.cpp Budget.cpp FinanceManager.cpp -std=c++17 -Wall -Wextra
```

### ▶️ How to Run

```bash
.\FinanceManager.exe
```

---

## 📌 Menu Options

```
=====================================================
        PERSONAL WEALTH & FINANCE DASHBOARD          
=====================================================
  [1]  📊 Display Full Financial Status Report
  [2]  💳 List All Financial Accounts & Balances
  [3]  ➕ Register a New Financial Account
  [4]  💸 Record a Transaction (Income or Expense)
  [5]  📝 List Full Transaction History Feed
  [6]  📅 View Budgets & Category Spending Limits
  [7]  🛡️ Set or Update a Category Budget Limit
  [8]  🔄 Transfer Funds Between Accounts
  [9]  📈 View Expense Breakdown & Spending Analytics
  [10] 🔍 Search & Filter Transactions
  [11] 🧹 Reset / Purge All Financial Data
  [12] 🚪 Exit System
=====================================================
```

---

## 🗂️ Sample Data (Pre-loaded on Startup)

### Accounts
| ID | Name | Type | Starting Balance / Debt |
|---|---|---|---|
| ACC001 | Primary Checking | Checking | NLe 2,500.00 |
| ACC002 | High-Yield Savings | Savings | NLe 10,000.00 |
| ACC003 | Cashback Credit Card | Credit Card | NLe 150.00 (Debt) |

### Budgets
| Category | Monthly Limit | Starting Spent |
|---|---|---|
| Food | NLe 400.00 | NLe 120.00 |
| Entertainment | NLe 150.00 | NLe 45.00 |
| Utilities | NLe 300.00 | NLe 180.00 |

### Transactions
- **TXN001**: Income of **NLe 3,000.00** into Primary Checking (Salary Paycheck)
- **TXN002**: Expense of **NLe 120.00** from Primary Checking (Groceries)
- **TXN003**: Expense of **NLe 45.00** from Credit Card (Netflix & Spotify)
- **TXN004**: Expense of **NLe 180.00** from Primary Checking (Electricity Bill)

---

## 👤 Author

**Osman Kamara**
C++ Console Application Developer

---

> Built with ❤️ using C++ OOP principles: Encapsulation · Abstraction · Modular Design
