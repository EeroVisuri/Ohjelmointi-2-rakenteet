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
    cout << this->author << " : " << this->bookName <<"\n";
    //print due date if loaned
    if (this->is_loaned == true) {
        cout << "- loaned: ";
        this->day_of_loan.print();
        cout << "- to be returned: ";
        this->due_date.print();
        return;
    }

    //otherwise it's available
    else if (this->is_loaned == false) {
        cout << "- available" << endl;
        return;
    }
}
//loans a book
void Book::loan(Date& today)
{
    if (this->is_loaned==true) {
        cout << "Already loaned: cannot be loaned" << endl;
        return;
    }
    else {
        this->is_loaned = true;
        Date loandate = today;
        this->day_of_loan = loandate;
        loandate.advance(28);
        this->due_date = loandate;
    }

}
//renews a loan
void Book::renew()
{
    Date renewed_date = this->due_date;
    renewed_date.advance(28);
    this->due_date = renewed_date;
}
//gives back a book
void Book::give_back()
{
    this->is_loaned = false;

}




