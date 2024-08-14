#include <SFML/Graphics.hpp>

#include "GameSettings.h"

char field[9];
const sf::Vector2f sizeOfPlace{250, 250};

void handleInput(sf::RenderWindow* window){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window->close();
    }
}

void drawField(sf::RenderWindow* window) {
    float totalWidth = (sizeOfPlace.x + FIELD_PADDING) * FIELD_TOTAL_CELLS - FIELD_PADDING;
    float totalHeight = (sizeOfPlace.y + FIELD_PADDING) * FIELD_TOTAL_CELLS - FIELD_PADDING;
    float startX = (window->getSize().x - totalWidth) / 2;
    float startY = (window->getSize().y - totalHeight) / 2;

    sf::Vector2f nextPos{startX, startY};
    for (int i = 0; i < 9; ++i) {
        nextPos.x = startX + (i % FIELD_TOTAL_CELLS) * (sizeOfPlace.x + FIELD_PADDING);
        nextPos.y = startY + (i / FIELD_TOTAL_CELLS) * (sizeOfPlace.y + FIELD_PADDING);

        sf::RectangleShape fieldShape(sizeOfPlace);
        fieldShape.setPosition(nextPos);

        switch (field[i]) {
        case EMPTY_FIELD_CHAR:
            fieldShape.setOutlineColor(sf::Color::Black);
            fieldShape.setOutlineThickness(5);
            fieldShape.setFillColor(WINDOW_BACKGROUND);
            break;
        default:
            break;
        }
        window->draw(fieldShape);
    }
}

int main()
{   
    for(int i = 0; i < 9; ++i){
        field[i] = EMPTY_FIELD_CHAR;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
     "SFML - TicTacToe", sf::Style::Titlebar);
    
    window.setVerticalSyncEnabled(IS_VSYNC_ENABLED);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        handleInput(&window);

        window.clear(WINDOW_BACKGROUND);

        drawField(&window);
        
        window.display();
    }

    return 0;
}