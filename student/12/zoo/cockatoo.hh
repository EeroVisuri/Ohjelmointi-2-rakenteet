#ifndef COCKATOO_HH
#define COCKATOO_HH
#include "bird.hh"
#include "iostream"
#include "string"

class Cockatoo: public Bird
{
public:
    Cockatoo();
    void sing(std::ostream& output);

};

#endif // COCKATOO_HH
