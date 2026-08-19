/*
    Project     : Banking System
    Internship  : CodeAlpha - C++ Programming
    Description : A console-based banking system demonstrating OOP concepts
                   using Customer, Account and Transaction classes.
                   Supports account creation, deposits, withdrawals,
                   fund transfers and transaction history.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

// ---------------------------------------------------------------------
// Transaction class: represents a single record of money movement.
// ---------------------------------------------------------------------
class Transaction {
private:
    string type;      // "Deposit", "Withdrawal", "Transfer-Out", "Transfer-In"
    double amount;
    string timestamp;

public:
    Transaction(string t, double amt) : type(t), amount(amt) {
        time_t now = time(nullptr);
        char buf[26];
        // ctime_s / ctime are not perfectly portable, so we format manually
        strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
        timestamp = string(buf);
    }

    void display() const {
        cout << left << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << setw(22) << timestamp << "\n";
    }
};

// ---------------------------------------------------------------------
// Account class: represents a single bank account belonging to a customer.
// ---------------------------------------------------------------------
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNo, double initialDeposit) : accountNumber(accNo), balance(initialDeposit) {
        if (initialDeposit > 0) {
            history.push_back(Transaction("Deposit", initialDeposit));
        }
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
    }

    // Returns true if the withdrawal succeeded, false if balance was insufficient.
    bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdrawal", amount));
        return true;
    }

    // These are used ONLY during a transfer, so the transaction is logged
    // once as "Transfer-Out"/"Transfer-In" instead of also being logged as
    // a separate generic Withdrawal/Deposit (which would double-count it).
    bool withdrawForTransfer(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Transfer-Out", amount));
        return true;
    }

    void depositForTransfer(double amount) {
        balance += amount;
        history.push_back(Transaction("Transfer-In", amount));
    }

    void showTransactionHistory() const {
        if (history.empty()) {
            cout << "No transactions yet for this account.\n";
            return;
        }
        cout << left << setw(15) << "Type" << setw(12) << "Amount" << setw(22) << "Date/Time" << "\n";
        cout << string(49, '-') << "\n";
        for (const auto &t : history) {
            t.display();
        }
    }
};

// ---------------------------------------------------------------------
// Customer class: represents a bank customer who can own one account.
// (Kept to one account per customer to stay simple/beginner-friendly;
//  see "Future Enhancements" in the README for multi-account support.)
// ---------------------------------------------------------------------
class Customer {
private:
    string name;
    int customerId;
    Account account;

public:
    Customer(string customerName, int custId, int accNo, double initialDeposit)
        : name(customerName), customerId(custId), account(accNo, initialDeposit) {}

    string getName() const { return name; }
    int getCustomerId() const { return customerId; }
    Account& getAccount() { return account; }
    const Account& getAccount() const { return account; } // const-safe overload for read-only access

    void showAccountInfo() const {
        cout << "\nCustomer Name : " << name << "\n";
        cout << "Customer ID   : " << customerId << "\n";
        cout << "Account No.   : " << account.getAccountNumber() << "\n";
        cout << fixed << setprecision(2);
        cout << "Balance       : " << account.getBalance() << "\n";
    }
};

// ---------------------------------------------------------------------
// Bank class: manages the collection of all customers and provides the
// main banking operations (create account, deposit, withdraw, transfer).
// ---------------------------------------------------------------------
class Bank {
private:
    vector<Customer> customers;
    int nextAccountNumber = 1001;
    int nextCustomerId = 1;

    // Finds a customer by account number. Returns nullptr if not found.
    Customer* findByAccountNumber(int accNo) {
        for (auto &c : customers) {
            if (c.getAccount().getAccountNumber() == accNo) {
                return &c;
            }
        }
        return nullptr;
    }

public:
    void createCustomer(const string &name, double initialDeposit) {
        Customer newCustomer(name, nextCustomerId, nextAccountNumber, initialDeposit);
        customers.push_back(newCustomer);
        cout << "\nAccount created successfully!\n";
        cout << "Customer ID: " << nextCustomerId << " | Account Number: " << nextAccountNumber << "\n";
        nextCustomerId++;
        nextAccountNumber++;
    }

    void deposit(int accNo, double amount) {
        Customer *c = findByAccountNumber(accNo);
        if (!c) {
            cout << "Error: Account number not found.\n";
            return;
        }
        c->getAccount().deposit(amount);
        cout << "Deposit successful. New balance: " << fixed << setprecision(2)
             << c->getAccount().getBalance() << "\n";
    }

    void withdraw(int accNo, double amount) {
        Customer *c = findByAccountNumber(accNo);
        if (!c) {
            cout << "Error: Account number not found.\n";
            return;
        }
        if (c->getAccount().withdraw(amount)) {
            cout << "Withdrawal successful. New balance: " << fixed << setprecision(2)
                 << c->getAccount().getBalance() << "\n";
        } else {
            cout << "Error: Insufficient balance.\n";
        }
    }

    void transfer(int fromAccNo, int toAccNo, double amount) {
        Customer *from = findByAccountNumber(fromAccNo);
        Customer *to = findByAccountNumber(toAccNo);

        if (!from || !to) {
            cout << "Error: One or both account numbers not found.\n";
            return;
        }
        if (fromAccNo == toAccNo) {
            cout << "Error: Cannot transfer to the same account.\n";
            return;
        }
        if (!from->getAccount().withdrawForTransfer(amount)) {
            cout << "Error: Insufficient balance for transfer.\n";
            return;
        }
        to->getAccount().depositForTransfer(amount);

        cout << "Transfer successful!\n";
        cout << fixed << setprecision(2);
        cout << "New balance of Account " << fromAccNo << ": " << from->getAccount().getBalance() << "\n";
    }

    void showAccountInfo(int accNo) {
        Customer *c = findByAccountNumber(accNo);
        if (!c) {
            cout << "Error: Account number not found.\n";
            return;
        }
        c->showAccountInfo();
    }

    void showTransactionHistory(int accNo) {
        Customer *c = findByAccountNumber(accNo);
        if (!c) {
            cout << "Error: Account number not found.\n";
            return;
        }
        cout << "\nTransaction History for Account " << accNo << ":\n";
        c->getAccount().showTransactionHistory();
    }

    void listAllCustomers() const {
        if (customers.empty()) {
            cout << "No customers registered yet.\n";
            return;
        }
        cout << "\n" << left << setw(15) << "Customer ID" << setw(20) << "Name"
             << setw(15) << "Account No." << setw(12) << "Balance" << "\n";
        cout << string(62, '-') << "\n";
        for (const auto &c : customers) {
            cout << left << setw(15) << c.getCustomerId() << setw(20) << c.getName()
                 << setw(15) << c.getAccount().getAccountNumber()
                 << fixed << setprecision(2) << c.getAccount().getBalance() << "\n";
        }
    }
};

// ---------------------------------------------------------------------
// Input helper functions (kept outside classes to keep them reusable)
// ---------------------------------------------------------------------
void clearInputError() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid whole number.\n";
            clearInputError();
        } else {
            clearInputError();
            return value;
        }
    }
}

double readNonNegativeDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cout << "Invalid input. Please enter a non-negative number.\n";
            clearInputError();
        } else {
            clearInputError();
            return value;
        }
    }
}

string readName(const string &prompt) {
    string name;
    cout << prompt;
    getline(cin, name);
    while (name.empty()) {
        cout << "Name cannot be empty. Please enter a name: ";
        getline(cin, name);
    }
    return name;
}

void showMenu() {
    cout << "\n========== BANKING SYSTEM MENU ==========\n";
    cout << "1. Create New Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Transfer Funds\n";
    cout << "5. View Account Info\n";
    cout << "6. View Transaction History\n";
    cout << "7. List All Customers\n";
    cout << "8. Exit\n";
    cout << "==========================================\n";
}

int main() {
    Bank bank;
    int choice;

    cout << "=========================================\n";
    cout << "     BANKING SYSTEM (CodeAlpha)           \n";
    cout << "=========================================\n";

    do {
        showMenu();
        choice = readInt("Enter your choice (1-8): ");

        switch (choice) {
            case 1: {
                string name = readName("Enter customer name: ");
                double deposit = readNonNegativeDouble("Enter initial deposit amount: ");
                bank.createCustomer(name, deposit);
                break;
            }
            case 2: {
                int accNo = readInt("Enter account number: ");
                double amount = readNonNegativeDouble("Enter deposit amount: ");
                bank.deposit(accNo, amount);
                break;
            }
            case 3: {
                int accNo = readInt("Enter account number: ");
                double amount = readNonNegativeDouble("Enter withdrawal amount: ");
                bank.withdraw(accNo, amount);
                break;
            }
            case 4: {
                int fromAcc = readInt("Enter sender account number: ");
                int toAcc = readInt("Enter receiver account number: ");
                double amount = readNonNegativeDouble("Enter amount to transfer: ");
                bank.transfer(fromAcc, toAcc, amount);
                break;
            }
            case 5: {
                int accNo = readInt("Enter account number: ");
                bank.showAccountInfo(accNo);
                break;
            }
            case 6: {
                int accNo = readInt("Enter account number: ");
                bank.showTransactionHistory(accNo);
                break;
            }
            case 7: {
                bank.listAllCustomers();
                break;
            }
            case 8: {
                cout << "Thank you for using the Banking System. Goodbye!\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please select a number between 1 and 8.\n";
            }
        }

    } while (choice != 8);

    return 0;
}
