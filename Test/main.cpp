#include "heat.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "SFML/Graphics.hpp"

static constexpr size_t nVectors = 120;

int main()
{
    std::vector<Vector2d> function;

    for(int i = 0; i < nVectors; ++i)
    {
        function.push_back({ i / static_cast<double>(nVectors), std::cos(i * 6 * 3.1415 / nVectors) });
    }

    Heat heat = Heat(function, 0.001);

    std::thread timerThread;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    sf::RenderWindow window;
    window.create(sf::VideoMode(640, 480), "Heat");
    sf::Event event;
    sf::RectangleShape pixel({ 1,1 });
    pixel.setFillColor({ 255,255,255 });
    size_t logCounter = 0;

    while(window.isOpen())
    {
        startTime = std::chrono::steady_clock::now();
        timerThread = std::thread([]() { std::this_thread::sleep_for(std::chrono::milliseconds(13)); });

        timerThread.join();

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        heat.step(0.016);

        window.clear();

        for (Vector2d vector : heat.getVectors())
        {
            pixel.setPosition({ static_cast<float>(window.getSize().x * vector.x_), static_cast<float>((window.getSize().y / 2) * (vector.y_ + 1)) });
            window.draw(pixel);
        }

        window.display();

        if (logCounter++ == 60)
        {
            logCounter = 0;
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() << std::endl;
        }
    }

    return 0;
}