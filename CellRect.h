//
// Created by longo on 25/09/2022.
//

#ifndef PATHFINDER_CELLRECT_H
#define PATHFINDER_CELLRECT_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>
#include <list>
using namespace std;

class CellRect {
public:
    CellRect(sf::Color color, sf::Color outline);
    ~CellRect() = default;

    void update(bool active, float side);

    void draw(sf::RenderWindow &window);

    sf::RectangleShape rect;

    bool isExpanding() { return expanding; }

private:
    sf::Vector2f pos;

    bool active = false;
    bool expanding = false;
};



#endif //PATHFINDER_CELLRECT_H
