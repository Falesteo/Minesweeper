//
// Created by longo on 25/09/2022.
//

#ifndef PATHFINDER_CELLRECT_H
#define PATHFINDER_CELLRECT_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>
using namespace std;

class CellRect {
public:
    CellRect(sf::Color color, sf::Color outline);
    ~CellRect() = default;

    void update(bool active, float side, int deltaTime);

    void draw(sf::RenderWindow &window);

    sf::RectangleShape rect;

private:
    sf::Vector2f pos;
    float timer = 0;
    bool active = false;
};



#endif //PATHFINDER_CELLRECT_H
