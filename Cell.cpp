//
// Created by longo on 02/10/2022.
//

#include "Cell.h"
#include "Grid.h"

Cell::Cell(sf::Vector2i indexes, Grid &grid) : indexes(indexes) {
    side = grid.getSide();
    font = grid.font;
    pos = {indexes.x * side, (indexes.y + grid.getMenuHeight() * grid.getScale()) * side};

    cellUnknownRect.rect.setPosition({pos.x + side / 2, pos.y + side / 2});
    cellDiscoveredRect.rect.setPosition({pos.x + side / 2, pos.y + side / 2});
    cellFlagRect.rect.setPosition({pos.x + side / 2, pos.y + side / 2});
    cellBombRect.rect.setPosition({pos.x + side / 2, pos.y + side / 2});

    bombTexture = grid.getBombTexture();
    bombSprite.setScale({side * 0.75f / bombTexture.getSize().x, side * 0.75f / bombTexture.getSize().y});
    bombSprite.setPosition({pos.x + side / 2, pos.y + side / 2});
    bombSprite.setOrigin({bombTexture.getSize().x / 2.f, bombTexture.getSize().y / 2.f});

    flagTexture = grid.getFlagTexture();
    flagSprite.setScale({side * 0.75f / flagTexture.getSize().x, side * 0.75f / flagTexture.getSize().y});
    flagSprite.setPosition({pos.x + side / 2, pos.y + side / 2});
    flagSprite.setOrigin({flagTexture.getSize().x / 2.f, flagTexture.getSize().y / 2.f});

    text.setPosition({pos.x + side / 2, pos.y + side / 2});
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(side * 0.75);
}

void Cell::draw(sf::RenderWindow &window) {
    cellUnknownRect.draw(window);
    cellDiscoveredRect.draw(window);

    cellFlagRect.draw(window);
    if (flag && !cellFlagRect.isExpanding()) {
        flagSprite.setTexture(flagTexture);
        window.draw(flagSprite);
    }
    if (discovered) {
        if (!cellDiscoveredRect.isExpanding()) {
            if (bomb) {
                cellBombRect.draw(window);
                bombSprite.setTexture(bombTexture);
                window.draw(bombSprite);
            } else {
                text.setString(to_string(adjacentBombs));
                text.setFont(font);
                text.setOrigin(text.getLocalBounds().width / 2 + text.getLocalBounds().left,
                               text.getLocalBounds().height / 2 + text.getLocalBounds().top);
                if (adjacentBombs > 0)
                    window.draw(text);
            }
        }
    }
}

void Cell::update(sf::RenderWindow &window) {
    cellUnknownRect.update(true, side);
    cellDiscoveredRect.update(discovered, side);
    cellBombRect.update(discovered, side);
    cellFlagRect.update(flag, side);
}

void Cell::getMouseInput(sf::RenderWindow &window, Grid &grid) {
    if (cellUnknownRect.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !flag) {
            if (!bomb) {
                setDiscovered(true);
                grid.oldExpandingCells.push_back(this);
            } else
                grid.detonated = this;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !discovered) {
            if (!addFlag) {
                addFlag = true;
                flag = !flag;
            }
        } else
            addFlag = false;
    }
}

void Cell::setNeighbours(Grid &grid) {
    for (int x = indexes.x - 1; x <= indexes.x + 1; x++)
        for (int y = indexes.y - 1; y <= indexes.y + 1; y++)
            if (x >= 0 && x < grid.gridSize.x && y >= 0 && y < grid.gridSize.y && !(x == indexes.x && y == indexes.y))
                neighbours.push_back(&grid.cells[x][y]);
}

void Cell::setNumber(Grid &grid) {
    if (!bomb) {
        for (auto neighbour: neighbours)
            if (neighbour->bomb)
                adjacentBombs++;
    } else
        adjacentBombs = -1;

    switch (adjacentBombs) {
        case 1:
            text.setFillColor(sf::Color(10, 201, 201));
            break;
        case 2:
            text.setFillColor(sf::Color(134, 201, 10));
            break;
        case 3:
            text.setFillColor(sf::Color(201, 10, 176));
            break;
        case 4:
            text.setFillColor(sf::Color(10, 74, 201));
            break;
        case 5:
            text.setFillColor(sf::Color(201, 195, 10));
            break;
        case 6:
            text.setFillColor(sf::Color(201, 10, 109));
            break;
        case 7:
            text.setFillColor(sf::Color(201, 67, 10));
            break;
        case 8:
            text.setFillColor(sf::Color(10, 201, 166));
            break;
    }
}

void Cell::expand(Grid &grid) {
    if (adjacentBombs == 0) {
        for (auto neighbour: neighbours) {
            if (!neighbour->getDiscovered()) {
                neighbour->setDiscovered(true);
                neighbour->flag = false;
                grid.newExpandingCells.push_back(neighbour);
            }
        }
    }
}

