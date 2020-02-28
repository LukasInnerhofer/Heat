#include "heat.hpp"

Heat::Heat() : DiscreteFunction(), k_() {}

Heat::Heat(const double &k) : DiscreteFunction(), k_(k) {}

Heat::Heat(std::vector<Vector2d> list, const double &k) : DiscreteFunction(list), k_(k) {}

void Heat::step(const double &dt)
{
    double curvature;
    double dy;

    if (isolated_)
    {
        if (vectors_.size() >= 3)
        {
            // Enforce boundary conditions for isolated start and end points:
            // ux(0)=0, ux(L)=0
            vectors_[0].y_ = vectors_[1].y_;
            vectors_[vectors_.size() - 1].y_ = vectors_[vectors_.size() - 2].y_;
        }
    }

    for (std::vector<Vector2d>::iterator itVectors = vectors_.begin();
        itVectors != vectors_.end();
        ++itVectors)
    {
        curvature = derivative().derivative().getVectors()[(itVectors - vectors_.begin())].y_;

        dy = k_ * curvature * dt;

        itVectors->y_ += dy;
    }
}