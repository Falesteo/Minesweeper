#include <SFML/Graphics.hpp>

#include <ctime>
#include <iostream>

#include "Grid.h"
#include "UI.h"

int main() {
    // initialize the randomic number generator
    srand(time(nullptr));

    // load window in fullscreen mode
    sf::RenderWindow window(sf::VideoMode(), "Minesweeper", sf::Style::Fullscreen);

    // creation of the event
    sf::Event event;

    sf::Clock clock;
    int deltaTime;

    // create the grid
    Grid grid({window.getSize().x, window.getSize().y});
    UI ui(window, grid);

    // Game loop
    while (window.isOpen()) {
        deltaTime = clock.restart().asMilliseconds();

        while (window.pollEvent(event)) {
            // closing the window and ending the game
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
            }
        }

        // Clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color(239, 254, 255));

        // project update and draw
        ui.update(window, grid);
        grid.update(window, deltaTime);

        ui.draw(window);
        grid.draw(window);

        // Bring to screen and display the new frame just drawn
        window.display();
    }

    // End of the Game
    return 0;
}