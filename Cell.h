//
// Created by longo on 02/10/2022.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include "CellRect.h"

class Grid;
class Cell {
public:
    Cell(sf::Vector2i indexes, Grid &grid);
    ~Cell() = default;

    bool hasBomb() const { return bomb; }
    void setBomb(bool bomb) { Cell::bomb = bomb; }

    bool hasFlag() const { return flag; }
    void setFlag(bool flag) { Cell::flag = flag; }

    bool isExpanding() { return cellDiscoveredRect.isExpanding(); }
    void expand(Grid &grid);

    bool getDiscovered() const { return discovered; }
    void setDiscovered(bool discovered) { Cell::discovered = discovered; }

    sf::Vector2f getPosition() const { return pos; }
    void setPosition(sf::Vector2f pos) { Cell::pos = pos; }

    void draw(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);

    void setNumber(Grid &grid);

    void setNeighbours(Grid &grid);

    void getMouseInput(sf::RenderWindow &window, Grid &grid);



private:
    sf::Vector2i indexes;
    sf::Vector2f pos;
    float side;

    std::vector<Cell*> neighbours;

    int adjacentBombs = 0;

    // light mode
    CellRect cellUnknownRect = {sf::Color(147, 184, 156), sf::Color(239, 254, 255, 64)};
    CellRect cellDiscoveredRect = {sf::Color(239, 254, 255), sf::Color(147, 184, 156, 64)};
    // dark mode
    // CellRect cellUnknownRect = {sf::Color(196, 255, 213), sf::Color(0, 23, 7, 64)};
    // CellRect cellDiscoveredRect = {sf::Color(0, 23, 7), sf::Color(196, 255, 213, 64)};

    bool bomb = false;
    sf::Texture bombTexture;
    sf::Sprite bombSprite;
    CellRect cellBombRect = {sf::Color(190, 209, 195), sf::Color(239, 254, 255, 64)};

    bool flag = false;
    bool addFlag = false;
    sf::Texture flagTexture;
    sf::Sprite flagSprite;
    CellRect cellFlagRect = {sf::Color(190, 209, 195), sf::Color(239, 254, 255, 64)};

    bool discovered = false;

    sf::Font font;
    sf::Text text;
};


#endif //MINESWEEPER_CELL_H
