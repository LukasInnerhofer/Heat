#include "heat.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <Windows.h>

int main()
{
    std::vector<Vector2d> function;

    for(int i = 0; i < 100; ++i)
    {
        function.push_back({ 1.0 / i, std::cos(2 * 3.1415 / 100) });
    }

    Heat heat = Heat(function, 1);

    while(1)
    {
        Sleep(900);

        heat.step(1);

        for(Vector2d v : heat.getVectors())
        {
            std::cout << v.y_ << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}