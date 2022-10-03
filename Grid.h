//
// Created by longo on 02/10/2022.
//

#ifndef MINESWEEPER_GRID_H
#define MINESWEEPER_GRID_H

#include "Cell.h"

class Grid {
public:
    Grid(sf::Vector2u windowSize);
    ~Grid() = default;

    float getSide() const { return side; }
    void setSide(float side) { Grid::side = side; }

    int getScale() const { return scale; }
    void setScale(int scale) { Grid::scale = scale; }

    float getMenuHeight() const { return menuHeight; }
    void setMenuHeight(int menuHeight) { Grid::menuHeight = menuHeight; }

    sf::Texture getFlagTexture() { return flagTexture; }
    sf::Texture getBombTexture() { return bombTexture; }

    std::vector<std::vector<Cell>> cells;

    void update(sf::RenderWindow &window, int deltaTime);
    void draw(sf::RenderWindow &window);

    void reset();

    sf::Vector2i gridSize;

    std::list<Cell*> oldExpandingCells = {};
    std::list<Cell*> newExpandingCells = {};
    Cell* detonated = nullptr;

    sf::Font font;

private:
    int scale, side;
    float menuHeight;

    void getGridMeasures(sf::Vector2u windowSize);

    void initializeGrid();

    void setNeighbours();

    sf::Texture flagTexture;

    float bombChance;
    sf::Texture bombTexture;
    void addBombs();

    void setNumbers();

    bool expanding = false;
    void getMouseInput(sf::RenderWindow &window);

    bool is_equal(float a, float b) { return fabs(a - b) <= 0.01; }
    float dist(sf::Vector2f a, sf::Vector2f b) { return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)); }

    float timer = 0;
};


#endif //MINESWEEPER_GRID_H
