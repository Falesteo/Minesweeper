//
// Created by longo on 02/10/2022.
//

#include "Grid.h"
#include <iostream>

Grid::Grid(sf::Vector2u windowSize) {
    if (!font.loadFromFile("Assets/Font/Quicksand/Quicksand-Regular.ttf")) {
        cout << "font non caricato" << endl;
        system("pause");
    }

    if (!flagTexture.loadFromFile("Assets/Images/flag.png")) {
        cout << "flag texture loading failed" << endl;
        system("pause");
    }

    if (!bombTexture.loadFromFile("Assets/Images/mine.png")) {
        cout << "mine texture loading failed" << endl;
        system("pause");
    }

    // get window dimensions
    scale = 2;
    menuHeight = 1;
    getGridMeasures(windowSize);

    // and initialize cells matrix accordingly
    initializeGrid();

    setNeighbours();

    // add obstacles to the grid
    bombChance = 0.1;
    addBombs();

    setNumbers();
}

void Grid::getGridMeasures(sf::Vector2u windowSize) {
    float aspectRatio = float(windowSize.x) / float(windowSize.y);

    // calculate the game unit based on the screen resolution
    if (is_equal(aspectRatio, 16.0 / 9.0) ||
        is_equal(aspectRatio, 16.0 / 10.0) ||
        is_equal(aspectRatio, 4.0 / 3.0))
        gridSize = {16 * scale, int((9 - menuHeight) * scale)};
    else if (is_equal(aspectRatio, 5.0 / 4.0))
        gridSize = {15 * scale, int((12 - menuHeight) * scale)};
    else if (is_equal(aspectRatio, 21.0 / 9.0))
        gridSize = {21 * scale, int((9 - menuHeight) * scale)};

    side = floor(windowSize.x / gridSize.x);
}

void Grid::initializeGrid() {
    cells = {};
    for (int i = 0; i < gridSize.x; i++) {
        cells.emplace_back();
        for (int j = 0; j < gridSize.y; j++) {
            Cell cell({i, j}, *this);
            cells[i].push_back(cell);
        }
    }
}

void Grid::setNeighbours() {
    for (int i = 0; i < gridSize.x; i++)
        for (int j = 0; j < gridSize.y; j++)
            cells[i][j].setNeighbours(*this);
}

void Grid::addBombs() {
    for (int i = 0; i < gridSize.x; i++)
        for (int j = 0; j < gridSize.y; j++)
            if (rand() / (RAND_MAX + 1.0f) < bombChance)
                cells[i][j].setBomb(true);
}

void Grid::setNumbers() {
    for (int i = 0; i < gridSize.x; i++)
        for (int j = 0; j < gridSize.y; j++)
            cells[i][j].setNumber(*this);
}

void Grid::update(sf::RenderWindow &window, int deltaTime) {
    // check if some cells are still expanding
    if (size(oldExpandingCells) > 0) {
        if (timer > 0.05f) {
            newExpandingCells = {};
            for (auto cell: oldExpandingCells)
                cell->expand(*this);

            oldExpandingCells = newExpandingCells;
            timer = 0;
        }
    } else if (detonated != nullptr) {
        for (int i = 0; i < size(cells); i++)
            for (int j = 0; j < size(cells[i]); j++)
                if (cells[i][j].hasBomb() && !cells[i][j].hasFlag() && dist(cells[i][j].getPosition(), detonated->getPosition()) < timer * 400)
                    cells[i][j].setDiscovered(true);
    } else
        getMouseInput(window);

    for (int i = 0; i < gridSize.x; i++)
        for (int j = 0; j < gridSize.y; j++)
            cells[i][j].update(window);

    timer += deltaTime / 1000.f;
}

void Grid::getMouseInput(sf::RenderWindow &window) {
    for (int i = 0; i < gridSize.x; i++)
        for (int j = 0; j < gridSize.y; j++)
            cells[i][j].getMouseInput(window, *this);
}

void Grid::draw(sf::RenderWindow &window) {
    for (int i = 0; i < gridSize.x; i++)
        for (int j = 0; j < gridSize.y; j++)
            cells[i][j].draw(window);
}

void Grid::reset() {
    initializeGrid();
    setNeighbours();
    addBombs();
    setNumbers();

    detonated = nullptr;
}
