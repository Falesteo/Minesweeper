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

void CellRect::update(bool active, float side) {
    if (active) {
        if (rect.getSize().x < side) {
            rect.setSize({rect.getSize().x + 1, rect.getSize().y + 1});
            expanding = true;
        } else
            expanding = false;
    } else {
        if (rect.getSize().x > 0) {
            rect.setSize({rect.getSize().x - 1, rect.getSize().y - 1});
            expanding = true;
        } else
            expanding = false;
    }

    // change the origin point
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
}

void CellRect::draw(sf::RenderWindow &window) {
    window.draw(rect);
}
