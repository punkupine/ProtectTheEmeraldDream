/**@file main.cpp
 * @author Catherine Collins 704169614 3-11-16
 * @brief creates a Game view object and runs the game
*/

#include "game.h"
#include <QApplication>

//since other classes will need to access this, we make the Game view a global variable
Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    game->displayMainMenu();

    return a.exec();
}
