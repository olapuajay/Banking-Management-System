#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <queue>
#include <cstring>

#define MAX_ACCOUNTS 100  // Maximum number of accounts

using namespace std;

class BankingSystem {
private:
    int accountNumbers[MAX_ACCOUNTS];           // Array to store account numbers
    char accountHolderNames[MAX_ACCOUNTS][100]; // Array to store account holder names
    double accountBalances[MAX_ACCOUNTS];       // Array to store account balances
    int accountCount;                           // Keeps track of the number of accounts
    queue<string> transactionHistory;           // Queue to store transaction history

public:
    BankingSystem() {
        accountCount = 0;
    }

    // Function to create a new account
    void createAccount() {
        if (accountCount >= MAX_ACCOUNTS) {
            cout << "Cannot create more accounts. Maximum limit reached." << endl;
            return;
        }

        int accNo;
        double initialDeposit;

        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Account Holder Name: ";
        cin >> accountHolderNames[accountCount];

        cout << "Enter Initial Deposit: ";
        cin >> initialDeposit;

        // Add account details to the arrays
        accountNumbers[accountCount] = accNo;
        accountBalances[accountCount] = initialDeposit;
        accountCount++;

        cout << "Account created successfully!" << endl;
        transactionHistory.push("Created Account: " + string(accountHolderNames[accountCount-1]) + " with initial deposit: " + to_string(initialDeposit));
    }

    // Function to search for an account by account number using linear search
    int findAccount(int accNo) {
        for (int i = 0; i < accountCount; i++) {
            if (accountNumbers[i] == accNo) {
                return i;
            }
        }
        return -1;
    }

    // Function to deposit money into an account
    void deposit() {
        int accNo;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);
        if (index != -1) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accountBalances[index] += amount;
            cout << "Deposit successful! New Balance: " << accountBalances[index] << endl;
            transactionHistory.push("Deposit: " + to_string(amount) + " into Account " + to_string(accNo));
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Function to withdraw money from an account
    void withdraw() {
        int accNo;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);
        if (index != -1) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (accountBalances[index] >= amount) {
                accountBalances[index] -= amount;
                cout << "Withdrawal successful! Remaining Balance: " << accountBalances[index] << endl;
                transactionHistory.push("Withdraw: " + to_string(amount) + " from Account " + to_string(accNo));
            } else {
                cout << "Insufficient balance!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Function to check the balance of an account
    void checkBalance() {
        int accNo;

        cout << "Enter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);
        if (index != -1) {
            cout << "Balance for Account " << accNo << ": " << accountBalances[index] << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Function to transfer money between two accounts
    void transferMoney() {
        int fromAccNo, toAccNo;
        double amount;

        cout << "Enter Sender's Account Number: ";
        cin >> fromAccNo;
        cout << "Enter Receiver's Account Number: ";
        cin >> toAccNo;
        cout << "Enter Amount to Transfer: ";
        cin >> amount;

        int fromIndex = findAccount(fromAccNo);
        int toIndex = findAccount(toAccNo);

        if (fromIndex != -1 && toIndex != -1) {
            if (accountBalances[fromIndex] >= amount) {
                accountBalances[fromIndex] -= amount;
                accountBalances[toIndex] += amount;
                cout << "Transfer successful! " << amount << " transferred from Account " << fromAccNo
                     << " to Account " << toAccNo << endl;
                transactionHistory.push("Transferred " + to_string(amount) + " from Account " + to_string(fromAccNo) +
                                        " to Account " + to_string(toAccNo));
            } else {
                cout << "Insufficient balance in sender's account!" << endl;
            }
        } else {
            cout << "One or both accounts not found!" << endl;
        }
    }

    // Function to sort accounts by balance using Bubble Sort
    void sortAccountsByBalance() {
        for (int i = 0; i < accountCount - 1; i++) {
            for (int j = 0; j < accountCount - i - 1; j++) {
                if (accountBalances[j] < accountBalances[j + 1]) {
                    swap(accountNumbers[j], accountNumbers[j + 1]);
                    swap(accountBalances[j], accountBalances[j + 1]);

                    char temp[100];
                    strcpy(temp, accountHolderNames[j]);
                    strcpy(accountHolderNames[j], accountHolderNames[j + 1]);
                    strcpy(accountHolderNames[j + 1], temp);
                }
            }
        }

        // Display sorted accounts
        cout << "\nAccounts sorted by balance (Descending):\n";
        for (int i = 0; i < accountCount; i++) {
            cout << "Account Number: " << accountNumbers[i] << ", Name: " << accountHolderNames[i]
                 << ", Balance: " << accountBalances[i] << endl;
        }
    }

    // Function to display transaction history
    void displayTransactionHistory() {
        cout << "\nTransaction History:\n";
        while (!transactionHistory.empty()) {
            cout << transactionHistory.front() << endl;
            transactionHistory.pop();
        }
    }
};

int main() {
    BankingSystem bank;
    int choice;

    do {
        cout << "\n--- Banking Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Transfer Money\n";
        cout << "6. Sort Accounts by Balance\n";
        cout << "7. Display Transaction History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.deposit();
                break;
            case 3:
                bank.withdraw();
                break;
            case 4:
                bank.checkBalance();
                break;
            case 5:
                bank.transferMoney();
                break;
            case 6:
                bank.sortAccountsByBalance();
                break;
            case 7:
                bank.displayTransactionHistory();
                break;
            case 0:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}