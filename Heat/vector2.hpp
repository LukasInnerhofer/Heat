#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <vector>

template<typename T>
struct Vector2
{
    T x_, y_;

    Vector2() : x_(), y_() {}
    Vector2(const std::vector<T> &list) : Vector2()
    {
        if(list.size() >= 2)
        {
            x_ = list[0];
            y_ = list[1];
        }
    }
    Vector2(const std::initializer_list<T> &list) : Vector2(std::vector<T>(list)) { }
};

typedef Vector2<double> Vector2d;

#endif // VECTOR2_HPP