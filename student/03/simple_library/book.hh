#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"
using namespace std;

class Book
{

    // Default constructor.
    //
    Book();


public:

    // Constructor.
    Book(string author, string bookName);

    // Destructor
    ~Book();

    //methods

    //prints out name and author "author : bookname" , if not loaned, prints "- available",
    //if loaned prints - loaned: xx.xx.xxxx endl; -to be returned: xx.xx.xxxx
    void print();

    //loans the book if it's available, takes Dates as parameter pointer, due date 28 days later
    void loan(Date today);

    //renews the loan from old due date
    void renew();

    //gives the loaned book back
    void give_back();


private:

    //attributes of a book

    bool is_loaned;
    string author;
    string bookName;
    Date due_date;
    Date day_of_loan;




};
#endif // BOOK_HH
