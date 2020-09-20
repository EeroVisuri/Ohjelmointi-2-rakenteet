#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false)  ;



    // More methods

    //sets the credit for account
    void setCredit(bool has_credit);

    //Setting the account owners name.
    void setName(std::string owner);

    //Getting the account owners name.
    void getName() const;

    //Method for printing out account names, IBANS and how much money is on them
    void print() const;

    //sets credit limit to an account, returns true on success, false otherwise.
    bool set_credit_limit(int new_credit_limit);

    //saves money to an account
    void save_money(int add_to_balance);

    //takes money from an account, up to maximum negative of credit limit.
    bool take_money(int remove_from_balance);

    //transfers money from current account to another account
    void transfer_to(Account& customer, int value);


    //gets you the balance of the account
    void getBalance() const;
    //sets the balance of account
    void setBalance(int value);



    void getIban() const;



private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    //balance of an account
    int balance;

    //account credit limit
    int credit_limit;

    //account credit
    bool has_credit;

    //account IBAN
    std::string iban_;
    //account owner
    std::string owner;








};

#endif // ACCOUNT_HH
