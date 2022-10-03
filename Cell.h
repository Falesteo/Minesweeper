//
// Created by longo on 02/10/2022.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include "CellRect.h"

class Grid;
class Cell {
public:
    Cell(sf::Vector2i pos, float side, sf::Font font);
    ~Cell() = default;

    void setBomb(bool bomb) {
        Cell::bomb = bomb;
        if (bomb)
            adjacentBombs = -1;
    }
    bool hasBomb() { return bomb; }

    void draw(sf::RenderWindow &window);
    void update(sf::RenderWindow &window, int deltaTime);

    void setNumber(Grid &grid);

    void setNeighbours(Grid &grid);

    void setDiscovered(bool discovered);
    bool getDiscovered() { return discovered; }

private:
    sf::Vector2i indexes;
    sf::Vector2f pos;
    float side;

    std::vector<Cell*> neighbours;

    int adjacentBombs = 0;

    CellRect cellUnknownRect = {sf::Color(20, 150, 57), sf::Color(239, 254, 255, 64)};
    CellRect cellDiscoveredRect = {sf::Color(239, 254, 255), sf::Color(20, 150, 57, 64)};

    bool bomb = false;
    sf::CircleShape bombSprite;

    bool flag = false;
    sf::Texture flagTexture;
    sf::Sprite flagSprite;

    bool discovered = false;

    sf::Font font;
    sf::Text text;
};


#endif //MINESWEEPER_CELL_H
