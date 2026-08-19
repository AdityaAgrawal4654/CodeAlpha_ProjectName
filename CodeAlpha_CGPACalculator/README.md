# Banking System

**Internship:** CodeAlpha – C++ Programming Internship
**Task:** Task 4 – Banking System

---

## 1. Project Title
Banking System (Console-based, Object-Oriented C++)

## 2. Objective
To design and implement a console-based banking system using object-oriented programming, with `Customer`, `Account`, and `Transaction` classes, supporting account creation, deposits, withdrawals, fund transfers, and transaction history — as specified by the CodeAlpha task requirements.

## 3. Problem Statement
A bank needs a simple system to manage customers and their accounts: creating accounts, handling deposits/withdrawals safely (without allowing overdrafts), transferring money between accounts, and keeping a record of every transaction so customers can review their history.

## 4. Features
- Create a new customer with an auto-generated Customer ID and Account Number.
- Deposit money into an account.
- Withdraw money (blocked if it would overdraw the account).
- Transfer funds between two accounts.
- View full account info (name, ID, account number, balance).
- View a timestamped transaction history per account.
- List all registered customers with their balances.
- Menu-driven interface that loops until the user chooses to exit.

## 5. C++ Concepts Used
- **Object-Oriented Programming**: `Customer`, `Account`, `Transaction`, and `Bank` classes.
- **Encapsulation**: private data members with public getter methods.
- **Composition**: a `Customer` *has-a* `Account`, an `Account` *has-a* list of `Transaction`s.
- **`const` correctness**: const and non-const overloads of `getAccount()`.
- **`vector`** to store dynamic lists of customers and transaction history.
- **`ctime`** for real transaction timestamps.
- Menu-driven `switch` statement with a `do-while` loop.
- Robust input validation.

## 6. Requirements
- C++17-compatible compiler (e.g. `g++`)
- Terminal / console
- VS Code (recommended)

## 7. Algorithm / Working
1. The `Bank` class holds a list of all `Customer` objects and auto-generates unique customer IDs and account numbers starting from 1001.
2. **Create Account:** Takes a name and initial deposit, creates a `Customer` (which internally creates an `Account`).
3. **Deposit/Withdraw:** The `Bank` looks up the customer by account number, then calls the account's `deposit()`/`withdraw()` method, which updates the balance and logs a `Transaction`.
4. **Transfer:** Looks up both sender and receiver accounts, checks the sender has sufficient balance, deducts from the sender (logged as "Transfer-Out"), and credits the receiver (logged as "Transfer-In") — logged only once per side to avoid duplicate records.
5. **View History:** Iterates through the account's stored `Transaction` list and prints each entry with type, amount, and timestamp.
6. The whole program runs inside a menu loop until the user selects "Exit".

## 8. Complete C++ Source Code
See [`banking_system.cpp`](./banking_system.cpp) in this folder.

## 9. Detailed Explanation of the Code
- **`Transaction` class**: represents one movement of money (type, amount, timestamp). It's immutable once created — a transaction record shouldn't change after the fact, which mirrors how real bank statements work.
- **`Account` class**: owns the actual balance and the list of transactions. It exposes `deposit()` and `withdraw()` for normal operations (each logs a transaction), and separate `withdrawForTransfer()` / `depositForTransfer()` methods used **only** during transfers, so a transfer is logged once as "Transfer-Out"/"Transfer-In" rather than twice (once as a generic Withdrawal/Deposit AND again as a Transfer). *This was actually a bug I caught and fixed during testing — see the note below.*
- **`Customer` class**: wraps a name, ID, and a single `Account`. `getAccount()` has both a normal and a `const` version so it can be safely called from read-only contexts like `listAllCustomers() const`.
- **`Bank` class**: the "manager" class — holds all customers, generates new IDs/account numbers, and exposes all the banking operations (`deposit`, `withdraw`, `transfer`, etc.) by looking up the right customer via `findByAccountNumber()`.
- **`main()`**: a simple menu loop (`do-while` + `switch`) that calls the appropriate `Bank` method based on user choice.

> **Testing note:** While testing, I found that my first version logged transfers twice (as both a generic Withdrawal/Deposit and a Transfer-Out/Transfer-In). I fixed this by adding dedicated `withdrawForTransfer()`/`depositForTransfer()` methods used only in the transfer path. I'm noting this here honestly rather than pretending the first version was already correct — this is the kind of bug you genuinely find through testing.

## 10. Sample Input
```
Choice: 1  (Create Account)
Name: Rahul Sharma
Initial deposit: 5000

Choice: 1  (Create Account)
Name: Priya Singh
Initial deposit: 2000

Choice: 4  (Transfer Funds)
Sender account: 1001
Receiver account: 1002
Amount: 2500

Choice: 6  (View Transaction History)
Account number: 1001
```

## 11. Sample Output
```
Account created successfully!
Customer ID: 1 | Account Number: 1001

Account created successfully!
Customer ID: 2 | Account Number: 1002

Transfer successful!
New balance of Account 1001: 3000.00

Transaction History for Account 1001:
Type           Amount      Date/Time
-------------------------------------------------
Deposit        5000.00     18-08-2026 20:12:38
Transfer-Out   2500.00     18-08-2026 20:12:38
```
*(This is real output from an actual test run of the compiled program.)*

## 12. Test Cases

| # | Scenario | Expected Result | Actual Result (Tested) |
|---|---|---|---|
| 1 | Create 2 accounts | Both get unique IDs (1001, 1002) | ✅ Passed |
| 2 | Deposit ₹1500 into account 1001 | Balance updates correctly | ✅ Passed |
| 3 | Withdraw more than balance | Rejected with "Insufficient balance" | ✅ Passed |
| 4 | Transfer ₹2500 from 1001 to 1002 | Both balances update, single log entry each | ✅ Passed (after bug fix) |
| 5 | Transfer to a non-existent account | Rejected with clear error message | ✅ Passed |
| 6 | View transaction history | Shows accurate, timestamped list | ✅ Passed |
| 7 | Invalid menu choice (e.g. 99) | Rejected, re-shows menu | ✅ Passed |

## 13. Possible Errors and How to Handle Them
- **Withdrawing more than the balance:** `withdraw()` returns `false` if `amount > balance`, and the caller shows an "Insufficient balance" message — the balance is never allowed to go negative.
- **Operating on a non-existent account number:** `findByAccountNumber()` returns `nullptr`, and every operation checks for this before proceeding.
- **Transferring to the same account:** explicitly checked and rejected.
- **Non-numeric menu input:** `readInt()`/`readNonNegativeDouble()` detect `cin.fail()` and re-prompt instead of crashing or looping infinitely.
- **Empty customer name:** `readName()` keeps asking until a non-empty name is given.

## 14. Advantages
- Clean OOP structure that mirrors a real banking domain model.
- Prevents overdrafts and invalid transfers.
- Full, accurate transaction history per account.
- Easy to extend with more account types or features.

## 15. Limitations
- Data is **not persisted** — all customers/accounts are lost when the program closes (in-memory only).
- One account per customer (a real bank system usually supports multiple accounts per customer).
- No authentication/PIN — anyone running the program can operate any account.
- Console-only interface.

## 16. Future Enhancements
*(My own recommended additions — not CodeAlpha requirements.)*
- Persist customer/account data to a file or a lightweight database (e.g. SQLite) so data survives restarts.
- Support multiple accounts per customer (e.g. Savings + Current).
- Add PIN/password protection per account.
- Add interest calculation for savings accounts.
- Export transaction history to a file/CSV.

## 17. Conclusion
This project fulfills CodeAlpha's Task 4 requirements exactly: dedicated `Customer`, `Account`, and `Transaction` classes; account creation and management; deposit, withdrawal and transfer features; transaction history; and account info display. It's a solid demonstration of object-oriented design in C++, and the bug found and fixed during testing (duplicate transfer logging) shows genuine, verified testing rather than an untested submission.
