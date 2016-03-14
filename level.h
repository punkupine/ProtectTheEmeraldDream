#ifndef LEVEL_H
#define LEVEL_H

/**@file level.h
 * @brief holds the declarations for class Level
*/

#include "player.h"
#include "input.h"
#include <QGraphicsScene>
#include <string>
#include <QMediaPlayer>
#include <QGraphicsTextItem>

class Player;
class Input;

/**@class Level
 * @brief controls the scenes, player, and enemies during actual gameplay
*/
class Level: public QGraphicsScene {
    friend class Game;
public:
    //constructor
    Level (QGraphicsScene* parent = nullptr);

    ~Level();

    QMediaPlayer* music;
    QGraphicsTextItem* player_health_text;
    QGraphicsTextItem* player_kills_text;

    void update();

private:
    Player* player;
    Input* input;
};


#endif // LEVEL_H
