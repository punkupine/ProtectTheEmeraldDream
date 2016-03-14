#ifndef GAME_H
#define GAME_H

/**@file game.h
 @brief holds the declarations for game class, which acts as a main window for the game
contains the main view/scene through which user plays game
*/

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "level.h"
#include "button.h"

/**@class Game
 * @brief acts as the view control for the game, setting up new scenes when necessary
*/
class Game : public QGraphicsView {
    Q_OBJECT
    //when something uses custom slots it has to have this macro and also inherit from QObject, which QGraphicsView does
public:
    //constructor
    Game(QWidget* parent = nullptr);

    //public member functions
    void display_game_over(); //if player dies
    void display_end_screen(); //if player wins

    //essentially getters/setters for player member variables
    void decrease_player_health();
    void increment_player_score();
    int get_player_health() const;
    int get_player_kills() const;

    //since so many other classes need to access these variables, we make them public rather than private
    //public member variables
    QGraphicsScene* scene;
    Level* level;
    QTimer* timer;

public slots:
    void displayMainMenu();
    void start();
    void display_instructions();
    void update();

};

#endif // GAME_H
