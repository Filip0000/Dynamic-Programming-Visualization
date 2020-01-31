#include <iostream>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "figures.h"
#include "factorial.h"
#include "fibonacci.h"
#include "knapsack.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Figures::size, Figures::size), "It's good!");
    window.setFramerateLimit(60);

    std::string type; //"factorial", "fibonacci", "knapsack"
    type = "knapsack";

    sf::Texture background_image;
    background_image.loadFromFile(Figures::background);
    background_image.setSmooth(true);

    sf::Sprite background;
    background.setTexture(background_image, true);
    background.setPosition(.0f, .0f);
    background.setScale((double) Figures::size / background_image.getSize().x,
                        (double) Figures::size / background_image.getSize().y);

    window.draw(background);
    window.display();
    window.draw(background);
    window.display();

    if(type == "factorial")
        Factorial::solve(background, window);
    else if(type == "fibonacci")
        Fibonacci::solve(background, window);
    else if(type == "knapsack")
        Knapsack::solve(background, window);
    return 0;
}
