#ifndef PLAYER_H
#define PLAYER_H

/**@file player.h
 * @brief holds the declarations for class Player
*/

#include "wrath.h"
#include "enemies.h"
#include <QGraphicsPixmapItem>
#include <vector>

//forward declaration
class Level;

/**@class Player
 * @brief constructs a player object for the user to control and play the game with
 * inherits from QGraphicsRectItem
 * keeps track of its own attack wrath objects as well as player health, number of enemies killed, and speed
*/
class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    friend class Game;
public:
    //constructor
    Player(QGraphicsItem* parent = nullptr);

    //member functions
    void attack();
    void move();
    void update();
    void remove_enemy(Enemy* enem);
    void increment_score();

    int get_health() const;
    int get_kills() const;

public slots:
    void spawn_enemies();
    void decrease_health();

private:
    Level* level_parent;
    int health; //if player drops to 0, they die
    int enemies_killed; //once player gets to 20 they win (for now)
    float speed = 3.5f;
};

#endif // PLAYER_H
