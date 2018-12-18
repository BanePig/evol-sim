#include "simulation/Simulation.hpp"
#include "./simulation/cell/plantcell/PlantCell.hpp"
#include "./simulation/cell/animalcell/AnimalCell.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include "Utils.hpp"

auto videoMode = sf::VideoMode::getDesktopMode();

Simulation& simulation = *new Simulation({ videoMode.width / 10, videoMode.height / 10 });

sf::RenderWindow& window = *new sf::RenderWindow(videoMode, "EvoSim", sf::Style::Default);

auto active = true;
auto paused = true;

void renderLoop()
{
    active = window.isOpen();
    while(active)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                active = false;
                return;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                    paused = !paused;
            }
        }
        window.clear();
        window.draw(*(sf::Drawable*)(&simulation));
        window.display();
    }
}

void logicLoop()
{
    auto targetFps = 30;
    sf::Clock clock;
    window.setActive(false);
    while(active)
    {
        if(paused)
        {
            clock.restart();
            continue;
        }
        for(auto cell : simulation.getAllCells())
        {
            cell->completeTurn();
        }
        auto timeElapsed = clock.getElapsedTime();
        auto wait = int(1000/targetFps - timeElapsed.asMilliseconds());
        if(wait > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        std::cout << "TPS: " << 1.0 / clock.getElapsedTime().asSeconds() << std::endl;
        clock.restart();
    }
}

int main()
{
    simulation.setScale(10.f);
    //srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    for(int i = 0; i < 20; i++)
    {
        new PlantCell(simulation,
            sf::Vector2f(randInt(0, videoMode.width / 10 - 1), randInt(0, videoMode.height / 10 - 1)),
            sf::Color(randInt(0, 255), randInt(0, 255), randInt(0, 255)),
            randDouble(0.1, 5.0));
    }
    for(int i = 0; i < 10; i++)
    {
        new AnimalCell(simulation,
            sf::Vector2f(randInt(0, videoMode.width / 10 - 1), randInt(0, videoMode.height / 10 - 1)),
            sf::Color(randInt(0, 255), randInt(0, 255), randInt(0, 255)),
            randDouble(0.1, 5.0),
            randDouble(0.1, 5.0),
            randDouble(0.1, 5.0),
            randDouble(0.1, 5.0));
    }
    window.setFramerateLimit(144);

    std::thread renderThread(logicLoop);
    renderLoop();
}

