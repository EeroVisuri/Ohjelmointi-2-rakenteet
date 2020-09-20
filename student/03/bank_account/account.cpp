#include "account.hh"
#include <iostream>
#include <string>
using namespace std;


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;



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
    balance = newBalance;
}

void Account::print() const {
    cout << owner << " : ";
    getIban();
    cout << " : ";
    getBalance();
    cout << "euros" << endl;
}

void Account::set_credit_limit(int new_credit_limit) {
    credit_limit = new_credit_limit;
}

void Account::save_money(int add_to_balance) {
    balance = balance+add_to_balance;
}

void Account::take_money(int remove_from_balance) {
    if (balance-remove_from_balance > credit_limit) {
        balance = balance-remove_from_balance;
    }

}

void Account::transfer_to(Account account, int value) {
    this->take_money(value);
    account.save_money(value);
}




