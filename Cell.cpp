//
// Created by longo on 02/10/2022.
//

#include "Cell.h"
#include "Grid.h"

Cell::Cell(sf::Vector2i indexes, float side, sf::Font font) : indexes(indexes), side(side), font(font) {
    pos = {indexes.x * side, indexes.y * side};

    cellUnknownRect.rect.setPosition({pos.x + side / 2, pos.y + side / 2});
    cellDiscoveredRect.rect.setPosition({pos.x + side / 2, pos.y + side / 2});

    bombSprite.setPosition({pos.x + side / 2, pos.y + side / 2});
    bombSprite.setOrigin({side / 3, side / 3});
    bombSprite.setRadius(side / 3);
    bombSprite.setFillColor(sf::Color::Black);

    if (!flagTexture.loadFromFile("Assets/Images/flag.png")) {
        cout << "flag texture loading failed" << endl;
        system("pause");
    }
    flagSprite.setScale({side * 0.5f / flagTexture.getSize().x, side * 0.5f / flagTexture.getSize().y});
    flagSprite.setPosition({pos.x + side / 2, pos.y + side / 2});
    flagSprite.setOrigin({flagTexture.getSize().x / 2.f, flagTexture.getSize().y / 2.f});

    text.setPosition({pos.x + side / 2, pos.y + side / 2});
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(side * 0.75);
}

void Cell::draw(sf::RenderWindow &window) {
    cellUnknownRect.draw(window);
    if (flag) {
        flagSprite.setTexture(flagTexture);
        window.draw(flagSprite);
    } else if (discovered) {
        cellDiscoveredRect.draw(window);

        if (bomb)
            window.draw(bombSprite);

        text.setString(to_string(adjacentBombs));
        text.setFont(font);
        text.setOrigin(text.getLocalBounds().width / 2 + text.getLocalBounds().left,
                       text.getLocalBounds().height / 2 + text.getLocalBounds().top);
        if (adjacentBombs != 0)
            window.draw(text);
    }
}

void Cell::update(sf::RenderWindow &window, int deltaTime) {
    if (cellUnknownRect.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !flag)
            setDiscovered(true);
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !discovered)
            flag = !flag;
    }

    cellUnknownRect.update(true, side, deltaTime);
    cellDiscoveredRect.update(discovered, side, deltaTime);
}

void Cell::setNeighbours(Grid &grid) {
    for (int x = indexes.x - 1; x <= indexes.x + 1; x++)
        for (int y = indexes.y - 1; y <= indexes.y + 1; y++)
            if (x >= 0 && x < grid.gridSize.x && y >= 0 && y < grid.gridSize.y && !(x == indexes.x && y == indexes.y))
                neighbours.push_back(&grid.cells[x][y]);
}

void Cell::setNumber(Grid &grid) {
    for (auto neighbour: neighbours)
        if (neighbour->bomb)
            adjacentBombs++;
}

void Cell::setDiscovered(bool discovered) {
    if (discovered) {
        this->discovered = discovered;
        if (adjacentBombs == 0) {
            for (auto neighbour: neighbours)
                if (!neighbour->getDiscovered())
                    neighbour->setDiscovered(true);
        }
    }
}
