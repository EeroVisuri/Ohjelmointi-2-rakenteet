#include "cards.hh"

// TODO: Implement the methods here




// A dynamic structure must have a constructor
// that initializes the top item as nullptr.

Cards::Cards(): top_(nullptr) {

}




// Adds a new card with the given id as the topmost element.
void Cards::add(int id) {
    Card_data* new_card = new Card_data;
    new_card->data = (id);
    new_card->next = top_;
    top_ = new_card;
}


// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the first element.
void Cards::print_from_top_to_bottom(std::ostream &s) {
    if (top_ == nullptr) {
        return;
    }
    Card_data* nextcard = top_;
    int count = 1;
    while (nextcard != nullptr) {
        int out_value = nextcard->data;
        s << count << ": " << out_value << std::endl;
        nextcard = nextcard->next;
        count = count+1;

    }

}
// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int &id) {
    if (top_ == nullptr) {
        return false;
    }
    if (top_->next == nullptr) {
        id = top_->data;
        delete top_;
        top_ = nullptr;
        return true;
    }

    Card_data* temp = top_;
    id = top_->data;
    top_ = top_->next;
    delete temp;
    return true;

}

// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top() {
    if (top_ == nullptr) {
        return false;
    }
    if (top_->next == nullptr) {
        return true;
    }

    Card_data* last = top_;
    Card_data* second_to_last = NULL;
    while (last->next != nullptr) {
        second_to_last = last;
        last = last->next;
    }
    second_to_last->next = nullptr;
    last->next = top_;
    top_ = last;


    return true;
}
// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.

bool Cards::top_to_bottom() {
    if (top_ == nullptr) {
        return false;
    }
    if (top_->next == nullptr) {
        return true;
    }
    Card_data* first = top_;
    Card_data* last = top_;
    while (last->next != nullptr) {
        last = last->next;
    }
    top_ = first->next;
    first->next = nullptr;
    last->next = first;

    return true;
}


// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the last element.
void Cards::print_from_bottom_to_top(std::ostream &s) {
    //ongoing...
    Card_data* last = top_;
    int count = 0;
    int cardnumber = 1;
    if (last->next != nullptr) {
        count++;
        last = last->next;
    }
    while (count != 0) {
        s << cardnumber << last->data;
        count--;

    }


}
//DESTRUCTOR
Cards::~Cards()
{

};

