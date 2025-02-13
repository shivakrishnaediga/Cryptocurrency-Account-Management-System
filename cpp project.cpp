#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
public:
    string type;
    int amount;

    Transaction(const string& t, int a) : type(t), amount(a) {}
};

class Account {
private:
    int balance;
    int dogecoin;
    int bitcoin;
    vector<Transaction> transactions;

public:
    Account() : balance(50000), dogecoin(0), bitcoin(0) {}

    void displayAccountInfo() {
        cout << "Account Information:\n";
        cout << "Balance: $" << balance << endl;
        cout << "Dogecoin Holdings: " << dogecoin << " coins" << endl;
        cout << "Bitcoin Holdings: " << bitcoin << " coins" << endl;
    }

    bool deposit(int amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount." << endl;
            return false;
        }

        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "$" << amount << " deposited successfully." << endl;
        return true;
    }

    bool withdraw(int amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
            return false;
        }

        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        cout << "$" << amount << " withdrawn successfully." << endl;
        return true;
    }

    bool buyCrypto(int amount, int price, const string& cryptoName) {
        int cost = amount * price;
        if (cost > balance) {
            cout << "Insufficient funds to buy " << cryptoName << endl;
            return false;
        }

        if (cryptoName == "Dogecoin") {
            dogecoin += amount;
        } else if (cryptoName == "Bitcoin") {
            bitcoin += amount;
        }

        balance -= cost;
        transactions.push_back(Transaction("Buy " + cryptoName, cost));
        cout << "Bought " << amount << " " << cryptoName << " for $" << cost << endl;
        return true;
    }

    bool sellCrypto(int amount, int price, const string& cryptoName) {
        if ((cryptoName == "Dogecoin" && amount > dogecoin) || (cryptoName == "Bitcoin" && amount > bitcoin)) {
            cout << "Insufficient " << cryptoName << " holdings to sell." << endl;
            return false;
        }

        int earnings = amount * price;
        if (cryptoName == "Dogecoin") {
            dogecoin -= amount;
        } else if (cryptoName == "Bitcoin") {
            bitcoin -= amount;
        }

        balance += earnings;
        transactions.push_back(Transaction("Sell " + cryptoName, earnings));
        cout << "Sold " << amount << " " << cryptoName << " for $" << earnings << endl;
        return true;
    }

    void displayTransactionHistory() {
        cout << "Transaction History:\n";
        for (int i = 0; i < transactions.size(); i++) {
            const Transaction& transaction = transactions[i];
            cout << transaction.type << ": $" << transaction.amount << endl;
        }
    }
};

int main() {
    Account account;

    bool continueRunning = true;

    while (continueRunning) {
        cout << "\nOptions:\n";
        cout << "1. Display Account Information\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Buy Cryptocurrency\n";
        cout << "5. Sell Cryptocurrency\n";
        cout << "6. Display Transaction History\n";
        cout << "7. Exit\n";

        int choice;
        cin >> choice;
                            string cryptoName;

        switch (choice) {

            case 1:
                account.displayAccountInfo();
                break;

            case 2:
                int depositAmount;
                cout << "Enter deposit amount: $";
                cin >> depositAmount;
                account.deposit(depositAmount);
                break;

            case 3:
                int withdrawAmount;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawAmount;
                account.withdraw(withdrawAmount);
                break;

            case 4:
                int buyAmount, buyPrice;
                cout << "Enter the cryptocurrency to buy (Dogecoin/Bitcoin): ";
                cin >> cryptoName;
                cout << "Enter the amount to buy: ";
                cin >> buyAmount;
                cout << "Enter the price per coin: $";
                cin >> buyPrice;
                account.buyCrypto(buyAmount, buyPrice, cryptoName);
                break;

            case 5:
                int sellAmount, sellPrice;

                cout << "Enter the cryptocurrency to sell (Dogecoin/Bitcoin): ";
                cin >> cryptoName;
                cout << "Enter the amount to sell: ";
                cin >> sellAmount;
                cout << "Enter the price per coin: $";
                cin >> sellPrice;
                account.sellCrypto(sellAmount, sellPrice, cryptoName);
                break;

            case 6:
                account.displayTransactionHistory();
                break;

            case 7:
                continueRunning = false;
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
