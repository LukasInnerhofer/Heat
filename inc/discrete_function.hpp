#ifndef DISCRETE_FUNCTION_HPP
#define DISCRETE_FUNCTION_HPP

#include <vector>

#include "vector2.hpp"

class DiscreteFunction
{
protected:
    std::vector<Vector2d> vectors_;

public:
    DiscreteFunction();
    DiscreteFunction(const std::vector<Vector2d> &list);

    std::vector<Vector2d> getVectors() const;

    DiscreteFunction derivative();
    static DiscreteFunction derivative(DiscreteFunction discreteFunction, unsigned int order);
};

#endif // DISCRETE_FUNCTION_HPP