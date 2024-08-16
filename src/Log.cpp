#include "Log.h"

#include<iostream>


#include "GameSettings.h"

#define UNIX_GREEN_CONSOLE_COLOR "\033[32m"
#define UNIX_WHITE_CONSOLE_COLOR "\033[0m" 

void logTheCourse(int index, char player){
    std::cout << UNIX_GREEN_CONSOLE_COLOR
     << player 
     << "-player puts a " 
     << (player == X_FIELD_CHAR ? "cross" : "circle") 
     << " in cell " 
     << index + 1 
     << "!" 
     << UNIX_WHITE_CONSOLE_COLOR
     << "\n";
}

void logNewGame(){
    std::cout << UNIX_GREEN_CONSOLE_COLOR
     << "-----New game started-----" 
     << UNIX_WHITE_CONSOLE_COLOR 
     << "\n";
}