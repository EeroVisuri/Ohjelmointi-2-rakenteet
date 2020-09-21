#include "date.hh"
#include <iostream>
#include <ostream>
#include <string>
#include "book.hh"
using namespace std;


//This class models a library book

//Constructor
Book::Book()
{
   this->author = "A. Anonym";
    this->bookName = "A book";
   this->is_loaned = false;
}

//Constructor with parameters
Book::Book(std::string author, std::string bookName)
{
    this->author = author;
    this->bookName = bookName;
    this->is_loaned = false;
}

//prints out author, bookname and availability
void Book::print()
{
    //Always print author and book name
    cout << this->author << " : " << this->bookName <<endl;
    //print due date if loaned
    if (is_loaned) {
        cout << "- loaned ";
        std::cout << &this->day_of_loan << endl;
        cout << "- to be returned ";
        cout << &this->due_date <<endl;
    }

    //otherwise it's available
    else {
        cout << "- available";
    }
}
//loans a book
void Book::loan(Date today)
{
    if (this->is_loaned==true) {
        cout << "Already loaned: cannot be loaned" << endl;
    }
    this->is_loaned = true;
    Date loandate = today;
    loandate.advance(28);
    this->due_date = loandate;
}
//renews a loan
void Book::renew()
{

    Date renewed_date = this->day_of_loan;
    renewed_date.advance(28);
    this->due_date = renewed_date;
}
//gives back a book
void Book::give_back()
{

}




