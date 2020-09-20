#include "account.hh"
#include <iostream>
#include <string>
using namespace std;


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

Account::Account(const string &owner, bool has_credit)
{
    this->owner = owner;
    this->has_credit = has_credit;
    this->generate_iban();
    this->setBalance(0);

}


void Account::generate_iban() {
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::getIban() const {
   cout <<  iban_;
}



void Account::getBalance() const
{
    cout << balance;
}

void Account::setBalance(int newBalance)
{
    this->balance = newBalance;
}



void Account::setCredit(bool has_credit)
{
    this->has_credit = has_credit;
}

void Account::setName(string owner)
{
    this->owner = owner;
}

void Account::getName() const
{
    cout << this->owner;
}

void Account::print() const {
    cout << this->owner;
    cout << " : ";
    this->getIban();
    cout << " : ";
    this->getBalance();
    cout << "euros" << endl;
}

bool Account::set_credit_limit(int new_credit_limit) {
    if (this->has_credit) {
        this->credit_limit = new_credit_limit;
        return true;
    }
    else {
        cout << "Cannot set credit limit: the account has no credit card"<<endl;
        return false;
    }

}

void Account::save_money(int add_to_balance) {
    this->balance = this->balance+add_to_balance;
}

bool Account::take_money(int remove_from_balance) {
    if (this->has_credit==false && this->balance-remove_from_balance < 0) {
        cout << "Cannot take money: balance underflow"<< endl;
        return false;
    }
    else if (this->has_credit==true && this->balance+this->credit_limit < remove_from_balance) {
        cout << "Cannot take money: credit limit overflow" << endl << "Transfer from ";
                this->getIban();
                cout << " failed"<<endl;
                return false;
    }
    else if (this->balance-remove_from_balance < this->balance+this->credit_limit) {
        this->balance = (this->balance - remove_from_balance);
        cout << remove_from_balance << " euros taken: new balance of ";
        this->getIban();
        cout << " is ";
        this->getBalance();
        cout << " euros"<<endl;
        return true;
    }

    else {
        cout << "Something weird went wrong this should not happen.";
        return false;
    }
}

void Account::transfer_to(Account&customer, int value) {
    if (this->take_money(value)==false) {
        cout << "Transfer from ";
        this->getIban();
        cout << " failed"<<endl;
        return;
    }
    else {
        customer.balance = customer.balance+value;
        return;
    }
}




