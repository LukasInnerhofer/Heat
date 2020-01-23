#include "discrete_function.hpp"

DiscreteFunction::DiscreteFunction()
{
    this->vectors_ = std::vector<Vector2d>();
}

DiscreteFunction::DiscreteFunction(const std::vector<Vector2d> &list)
{
    this->vectors_ = std::vector<Vector2d>(list);
}

std::vector<Vector2d> DiscreteFunction::getVectors() const
{
    return vectors_;
}

DiscreteFunction DiscreteFunction::derivative()
{
    DiscreteFunction derivedFunction = DiscreteFunction(this->vectors_);
    
    std::vector<Vector2d>::iterator itFunction = this->vectors_.begin();
    std::vector<Vector2d>::iterator itDerivedFunction = derivedFunction.vectors_.begin();

    Vector2d v0, v1;

    for(; 
        itFunction != this->vectors_.end(), itDerivedFunction != derivedFunction.vectors_.end();
        ++itFunction, ++itDerivedFunction)
    {
        if(itFunction == this->vectors_.begin())
        {
            // Forward difference
            v0 = *itFunction;
            v1 = *(itFunction + 1);
        }
        else if(itFunction + 1 == this->vectors_.end())
        {
            // Backward difference
            v0 = *(itFunction - 1);
            v1 = *itFunction;
        }
        else
        {
            // Center difference
            v0 = *(itFunction - 1);
            v1 = *(itFunction + 1);
        }

        (*itDerivedFunction).y_ = (v1.y_ - v0.y_) / (v1.x_ - v0.x_);
    }

    return derivedFunction;
}