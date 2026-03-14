#include <iostream>
#include <string>
#include <cstring>

class BankAccount {
    int accountNumber;
    std::string accountHolderName;
    char* accountType;

protected:
    float balance;

public:

    BankAccount(int accNo, std::string accName, float bal, const char* accType)
        : accountNumber(accNo), accountHolderName(accName), balance(bal) {
        accountType = new char[strlen(accType) + 1];
        strcpy(accountType, accType);
    }

    BankAccount(const BankAccount& other)
        : accountNumber(other.accountNumber),
          accountHolderName(other.accountHolderName),
          balance(other.balance) {
        accountType = new char[strlen(other.accountType) + 1];
        strcpy(accountType, other.accountType);
    }

    BankAccount(BankAccount&& other) noexcept
        : accountNumber(other.accountNumber),
          accountHolderName(std::move(other.accountHolderName)),
          accountType(other.accountType),
          balance(other.balance) {
        other.accountType = nullptr;
    }

    BankAccount& operator=(const BankAccount& other) {
        if (this == &other) {
            return *this;
        }

        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;

        delete[] accountType;

        accountType = new char[strlen(other.accountType) + 1];
        strcpy(accountType, other.accountType);

        return *this;
    }

    float displayBalance() const {
        return balance;
    }

    void deposit(float money) {
        this->balance += money;
    }

    virtual void withdraw(float amount) = 0;

    virtual void showAccountDetails() const {
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Account Holder Name: " << accountHolderName << "\n";
        if (accountType)
            std::cout << "Account Type: " << accountType << "\n";
        else
            std::cout << "Account Type: null\n";
        std::cout << "Balance: " << balance << "\n";
    }

    virtual ~BankAccount() {
        delete[] accountType;
        std::cout << "Delete BankAccount\n";
    }
};

class SavingsAccount : public BankAccount {
    float interestRate;

public:
    SavingsAccount(int accNo, std::string accName, float bal, float rate)
        : BankAccount(accNo, accName, bal, "Savings"), interestRate(rate) {}

    SavingsAccount(SavingsAccount&& other) noexcept
        : BankAccount(std::move(other)),
          interestRate(other.interestRate) {}

    void setInterestRate(float rate) {
        interestRate = rate;
    }

    void showAccountDetails() const override {
        BankAccount::showAccountDetails();
        std::cout << "Interest Rate: " << interestRate << "\n";
    }

    void withdraw(float amount) override {
        if (amount <= balance)
            balance -= amount;
        else
            std::cout << "Insufficient balance";
    }

    virtual ~SavingsAccount() {
        std::cout << "delete savings";
    }
};

class CurrentAccount : public BankAccount {
    float overdraftLimit;

public:
    CurrentAccount(int accNo, std::string accName, float bal, float limit)
        : BankAccount(accNo, accName, bal, "Current"), overdraftLimit(limit) {}

    CurrentAccount(CurrentAccount&& other) noexcept
        : BankAccount(std::move(other)),
          overdraftLimit(other.overdraftLimit) {}

    void withdraw(float amount) override {
        if (displayBalance() - amount >= -overdraftLimit) {
            balance -= amount;
        } else {
            std::cout << "Overdraft limit exceeded\n";
        }
    }

    void showAccountDetails() const override {
        BankAccount::showAccountDetails();
        std::cout << "Overdraft Limit: " << overdraftLimit << "\n";
    }

    virtual ~CurrentAccount() {
        std::cout << "delete current";
    }
};

int main() {
// SavingsAccount s1(101, "Easwar", 5000, 4.5);
    // CurrentAccount c1(201, "Easwar", 3000, 2000);

    // s1.deposit(1000);
    // s1.showAccountDetails();

    // c1.withdraw(4500);
    // c1.showAccountDetails();

    // BankAccount *account = new SavingsAccount(1234, "Sai Easwar", 5000.0, 9);
    // account->showAccountDetails(); based on the virtual showAccountDetails base class, this works accordingly, try with virtual and without

    // BankAccount* currAcc = new CurrentAccount(1234, "sai easwar", 6000.0, 200);
    // currAcc->showAccountDetails();
    // delete currAcc;

    SavingsAccount s1(123, "sai easwar", 4000, 5);
    // s1.showAccountDetails();
    // SavingsAccount s2(124, "Goutham", 6000, 8);
    // s2.showAccountDetails();

    // std::cout<<"Before copy assignment operator =\n";

    // s1 = s2;

    s1.showAccountDetails();
    std::cout<<std::endl;
    // SavingsAccount s2 = std::move(s1);
    // s1.showAccountDetails();
    SavingsAccount s2 (124, "goutham", 5000, 7);
    //s2 = std::move(s1);
    s2.showAccountDetails();
}