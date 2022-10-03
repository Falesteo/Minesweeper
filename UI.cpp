//
// Created by longo on 03/10/2022.
//

#include "UI.h"
#include "Grid.h"

UI::UI(sf::RenderWindow &window, Grid &grid) {
    side = grid.getSide();
    menuHeight = grid.getMenuHeight();
    font = grid.font;

    menuBar.setPosition({0, 0});
    menuBar.setSize({window.getSize().x * 1.f, side * menuHeight * grid.getScale()});
    menuBar.setFillColor(sf::Color(190, 209, 195));

    title.setString("Minesweeper");
    title.setPosition(window.getSize().x / 2, side * menuHeight * grid.getScale() / 2);
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(side * (menuHeight * grid.getScale() - 1));

    resetBtn.setString("Reset");
    resetBtn.setPosition(window.getSize().x / 4, side * menuHeight * grid.getScale() / 2);
    resetBtn.setFillColor(sf::Color::Black);
    resetBtn.setCharacterSize(side * (menuHeight * grid.getScale() - 1.5));
}

void UI::update(sf::RenderWindow &window, Grid &grid) {
    if (resetBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            grid.reset();
}

void UI::draw(sf::RenderWindow &window) {
    window.draw(menuBar);

    title.setFont(font);
    title.setOrigin(title.getLocalBounds().width / 2 + title.getLocalBounds().left,
                    title.getLocalBounds().height / 2 + title.getLocalBounds().top);
    window.draw(title);

    resetBtn.setFont(font);
    resetBtn.setOrigin(resetBtn.getLocalBounds().width / 2 + resetBtn.getLocalBounds().left,
                       resetBtn.getLocalBounds().height / 2 + resetBtn.getLocalBounds().top);
    window.draw(resetBtn);
}