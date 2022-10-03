//
// Created by longo on 25/09/2022.
//

#include "CellRect.h"

CellRect::CellRect(sf::Color color, sf::Color outline) {
    rect.setSize({0, 0});
    rect.setFillColor(color);
    rect.setOutlineColor(outline);
    rect.setOutlineThickness(1);
}

void CellRect::update(bool active, float side, int deltaTime) {
    if (active != this->active) {
        this->active = active;
        timer = 0;
    } else {
        if (timer > 1)
            timer = 1;
        else if (timer < 0)
            timer = 0;
    }

    if (this->active)
        rect.setSize({side * timer, side * timer});
    else
        rect.setSize({side * (1 - timer), side * (1 - timer)});

    // change the origin point
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);

    timer += 5 * deltaTime / pow(10, 3);
}

void CellRect::draw(sf::RenderWindow &window) {
    window.draw(rect);
}
