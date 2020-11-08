#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here



// Constructor that initializes the attribute cycle_.
// (The other attibutes are initialized in the private part below.)
Queue::Queue(unsigned int cycle) {
    cycle_ = cycle;
}


//destructor
Queue::~Queue() {

}

// Inserts a vehicle, the register number of which is reg, to the queue.

void Queue::enqueue(string reg) {
    if (!is_green_) {
        Vehicle* new_vehicle = new Vehicle;
        new_vehicle->reg_num = reg;
        //first car scenario
        if (first_ == nullptr && last_ == nullptr) {
            first_ = new_vehicle;
            last_ = new_vehicle;
            new_vehicle->next = nullptr;
            return;
        }
        else  {
            last_->next = new_vehicle;
            last_ = new_vehicle;
            new_vehicle->next = nullptr;
            return;
        }
    }
    std::cout << "GREEN: The vehicle " << reg << " need not stop to wait"<< std::endl;;
}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light() {
    is_green_= !is_green_;
    if (is_green_) {
        std::cout << "GREEN: ";
        Vehicle* current_vehicle = first_;
        if (current_vehicle == nullptr) {
            std::cout << "No vehicles waiting in traffic lights" << std::endl;
            return;
        }
        std::cout << "Vehicles(s) ";
        for (unsigned int i = 0; i < cycle_; ++i) {
            std::cout << current_vehicle->reg_num << " ";
            if (current_vehicle->next!= nullptr) {
                dequeue();
                current_vehicle = current_vehicle->next;
            }
            else if (current_vehicle->next == nullptr) {
                dequeue();
                std::cout << "can go on"<< std::endl;
                is_green_ = false;
                return;
            }
            else {
                std::cout << "can go on"<< std::endl;
                is_green_ = false;
                return;
            }
        }
        std::cout << "can go on"<< std::endl;
        is_green_ = false;
        return;
    }
    else {
        print();
    }
}


// Resets the attribute cycle_.
void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
void Queue::print()
{
    if (is_green_) {
        std::cout << "GREEN: ";
    }
    else {
        std::cout << "RED: ";
    }
    if (first_ == nullptr) {
        std::cout << "No vehicles waiting in traffic lights."<< std::endl;;
        return;
    }
    Vehicle* current_vehicle = first_;
    std::cout << "Vehicle(s) ";
    while (current_vehicle != nullptr) {
        std::cout << current_vehicle->reg_num << " ";
        if (current_vehicle->next != nullptr) {
            current_vehicle = current_vehicle->next;
        }
        else {
            std::cout << "waiting in traffic lights" << std::endl;
            return;
        }
    }
    ;
}
//removes a vehicle from the queue
void Queue::dequeue() {
    Vehicle* temp = first_;
    //in case we empty the queue by letting last car go
    if (first_->next == nullptr) {
        first_ = nullptr;
        last_ = nullptr;
        delete temp;
        return;
    }

    first_ = first_->next;
    delete temp;

}


