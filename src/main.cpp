#include <SFML/Graphics.hpp>

#include "GameSettings.h"

char field[9];

void handleInput(sf::RenderWindow* window){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window->close();
    }
}

void drawField(){

}

int main()
{
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

        window.clear(sf::Color::White);

        drawField();
        
        window.display();
    }

    return 0;
}