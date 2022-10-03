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

    std::vector<std::vector<Cell>> cells;

    void update(sf::RenderWindow &window, int deltaTime);
    void draw(sf::RenderWindow &window);

    sf::Vector2i gridSize;

private:
    int scale;
    int side;

    void getGridMeasures(sf::Vector2u windowSize, int scale);

    void initializeGrid();

    void setNeighbours();

    float bombChance;
    void addBombs();

    void setNumbers();

    bool is_equal(float a, float b) { return fabs(a - b) <= 0.01; }

    sf::Font font;
};


#endif //MINESWEEPER_GRID_H