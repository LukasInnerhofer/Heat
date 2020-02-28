#include "heat.hpp"

#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include "SFML/Graphics.hpp"

static constexpr size_t nVectors = 500;
static constexpr double conductivity = 0.0001;
static constexpr size_t frameRate = 60;
static constexpr size_t logPeriod = 1000;

int main()
{
    std::vector<Vector2d> function;

    for(int i = 0; i < nVectors; ++i)
    {
        function.push_back({ i / static_cast<double>(nVectors), std::sin(8 * 3.14 * i / static_cast<double>(nVectors)) });
    }

    Heat heat = Heat(function, conductivity);

    std::thread timerThread;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::atomic<double> frameTime = 1.0 / frameRate;
    std::thread logThread = std::thread([](std::atomic<double>& frameTime) {
        for (;;)
        {
            std::thread timerThread = std::thread([]() {std::this_thread::sleep_for(std::chrono::milliseconds(logPeriod)); });
            std::cout << frameTime << "\n";
            timerThread.join();
        }
        
        }, std::ref(frameTime));

    sf::RenderWindow window;
    window.create(sf::VideoMode(1600, 900), "Heat");
    sf::Event event;
    sf::RectangleShape pixel({ 1,1 });
    pixel.setFillColor({ 255,255,255 });

    while(window.isOpen())
    {
        startTime = std::chrono::steady_clock::now();
        timerThread = std::thread([]() { std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frameRate)); });

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        heat.step(frameTime);

        window.clear();

        for (Vector2d vector : heat.getVectors())
        {
            pixel.setPosition({ static_cast<float>(window.getSize().x * vector.x_), static_cast<float>((window.getSize().y / 2) * (1 - vector.y_)) });
            window.draw(pixel);
        }

        window.display();

        timerThread.join();

        frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() / 1000.0;
    }

    logThread.detach();

    return 0;
}