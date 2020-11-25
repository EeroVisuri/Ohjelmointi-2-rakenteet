#ifndef GIRAFFE_HH
#define GIRAFFE_HH
#include "mammal.hh"


class Giraffe: public Mammal
{
public:
    Giraffe();
    Giraffe(const std::string& moving_noise);

    void make_noise(std::ostream& output) const;


private:
    int x_;
    int y_;
    std::string moving_noise;


};

#endif // GIRAFFE_HH
