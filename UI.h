//
// Created by longo on 03/10/2022.
//

#ifndef MINESWEEPER_UI_H
#define MINESWEEPER_UI_H

#include "SFML/Graphics.hpp"

class Grid;
class UI {
public:
    UI(sf::RenderWindow &window, Grid &grid);
    ~UI() = default;

    void update(sf::RenderWindow &window, Grid &grid);
    void draw(sf::RenderWindow &window);

private:
    float side, menuHeight;

    sf::RectangleShape menuBar;
    sf::Text title;

    sf::Text resetBtn;

    sf::Font font;
};


#endif //MINESWEEPER_UI_H
