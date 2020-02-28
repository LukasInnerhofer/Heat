#ifndef HEAT_HPP
#define HEAT_HPP

#include "discrete_function.hpp"

class Heat : public DiscreteFunction
{
    double k_ = 1;

public:
    Heat();
    Heat(const double &k);
    Heat(std::vector<Vector2d> list, const double &k);

    void step(const double &dt);
};

#endif // HEAT_HPP