#ifndef HEAT_HPP
#define HEAT_HPP

#include "discrete_function.hpp"

#include <cmath>

class Heat : public DiscreteFunction
{
    double k_ = 1;          /**< Conductivity */
    bool isolated_ = true;  /**< Are start and end points thermally isolated?*/

public:
    Heat();
    Heat(const double &k);
    Heat(std::vector<Vector2d> list, const double &k);

    void step(const double &dt);
};

#endif // HEAT_HPP