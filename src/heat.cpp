#include "heat.hpp"

Heat::Heat() : DiscreteFunction(), k_() {}

Heat::Heat(const double &k) : DiscreteFunction(), k_(k) {}

Heat::Heat(std::vector<Vector2d> list, const double &k) : DiscreteFunction(list), k_(k) {}

void Heat::step(const double &dt)
{
    double curvature;
    double dy;

    for(std::vector<Vector2d>::iterator itVectors = vectors_.begin(); itVectors != vectors_.end(); ++itVectors)
    {
        curvature = derivative().derivative().getVectors()[0].y_;

        dy = k_ * curvature;

        itVectors->y_ += dy;
    }
}