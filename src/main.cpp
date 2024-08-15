#include<iostream>
#include <SFML/Graphics.hpp>

#include "GameSettings.h"

char field[9];
const sf::Vector2f sizeOfPlace{250, 250};
const sf::Vector2f sizeOfSymbol{200, 200};
bool isFirstPlayer = true;
bool isGameOver = false;
int winnerIndex = -1; // 0 - X ; 1 - O ; 2 - X == O ;-1 - None
sf::Font font;
sf::Text winnerText;

void newGame(){
    for(int i = 0; i < 9; ++i){
        field[i] = EMPTY_FIELD_CHAR;
    }
    isGameOver = false;
    winnerIndex = -1;
}

void finish(const int index){
    if(index == -1){
        return;
    }
    winnerIndex = index;
    isGameOver = true;
}

void checkWinner(){
    for(int i = 0; i < FIELD_TOTAL_CELLS; ++i){
        if(field[i * 3] == field[i * 3 + 1] && field[i * 3 + 1] == field[i * 3 + 2]){
            if(field[i * 3] == X_FIELD_CHAR){
                finish(0);
            }
            else if(field[i * 3] == O_FIELD_CHAR){
                finish(1);
            }
        }
    }
    for(int i = 0; i < FIELD_TOTAL_CELLS; i++){
        if(field[i] == field[i + 3] && field[i + 3] == field[i + 6]){
            if(field[i] == X_FIELD_CHAR){
                finish(0);
            }
            else if(field[i] == O_FIELD_CHAR){
                finish(1);
            }
        }
    }
    if(field[0] == field[4] && field[4] == field[8]){
        if(field[0] == X_FIELD_CHAR){
            finish(0);
        }
        else if(field[0] == O_FIELD_CHAR){
            finish(1);
        }
    }
    if(field[2] == field[4] && field[4] == field[6]){
        if(field[2] == X_FIELD_CHAR){
            finish(0);
        }
        else if(field[2] == O_FIELD_CHAR){
            finish(1);
        }
    }
    for(int i = 0; i < 9; ++i){
        if(field[i] == EMPTY_FIELD_CHAR){
            finish(-1);
            return;
        }
    }
    finish(2);
}

void drawSymbol(const char symbol, sf::RenderWindow* window, sf::Vector2f position) {
    position.x += 25.f;
    position.y += 25.f;
    if (symbol == X_FIELD_CHAR) {
        sf::CircleShape triangle(sizeOfSymbol.x / 2, 3);
        triangle.setPosition(position);
        triangle.setOutlineThickness(5);
        triangle.setOutlineColor(sf::Color::Green);
        triangle.setFillColor(sf::Color::Transparent);
        window->draw(triangle);
    } 
    else if (symbol == O_FIELD_CHAR) {
        sf::CircleShape circle(sizeOfSymbol.x / 2);
        circle.setPosition(position);
        circle.setOutlineThickness(5);
        circle.setOutlineColor(sf::Color::Red);
        circle.setFillColor(sf::Color::Transparent);
        window->draw(circle);
    }
}

void play(int fieldIndex) {
    if (field[fieldIndex] == EMPTY_FIELD_CHAR) {
        field[fieldIndex] = isFirstPlayer ? X_FIELD_CHAR : O_FIELD_CHAR;
        isFirstPlayer = !isFirstPlayer;
    }
}

void handleInput(sf::RenderWindow* window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->close();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        newGame();
    }
    if(!isGameOver){
        for (int i = 0; i < 9; ++i) {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i))) {
                play(i);
            }
        }
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
        fieldShape.setOutlineColor(sf::Color::Black);
        fieldShape.setOutlineThickness(5);
        fieldShape.setFillColor(WINDOW_BACKGROUND);

        window->draw(fieldShape);

        if(field[i] != EMPTY_FIELD_CHAR){
            drawSymbol(field[i], window, nextPos);
        }
    }
}

int main()
{   
    #if _WIN32
        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    #elif __APPLE__
        font.loadFromFile("/Library/Fonts/Arial.ttf");
    #else
    #error "This game works only on Windows or MacOS!"
    #endif

    winnerText.setCharacterSize(34);
    winnerText.setFillColor(sf::Color::Black);
    winnerText.setFont(font);

    newGame();

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
     "SFML - TicTacToe");
    
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

        if(!isGameOver){
            drawField(&window);
            checkWinner();
        }        
        else{
            winnerText.setPosition({window.getSize().x / 2, window.getSize().y / 2});
            sf::String text;
            switch (winnerIndex)
            {
            case 0: // X
                text = "X-player wins!\n";
                break;
            
            case 1: // O
                text = "O-player wins!\n";
                break;

            case 2: // Both
                text = "Draw!\n";
                break;
            
            default:
                break;
            }
            text += "Press [esc] to close the game or press [R] to replay!";
            winnerText.setString(text);
            window.draw(winnerText);
        }


        window.display();
    }

    return 0;
}