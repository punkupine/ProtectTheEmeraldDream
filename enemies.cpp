/**@file enemies.cpp
 * @brief holds the implementation for the Enemy class
*/

#include "enemies.h"
#include "player.h"
#include <QGraphicsScene>
#include <stdlib.h>
#include "game.h"
#include <QTimer>

extern Game* game;

/**@brief default constructor for enemy object
 * sets default location through a random number and assigns a graphic
*/
Enemy::Enemy(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent) {
    //set random position TODO CHANGE THIS TO C++11 IMPLEMENTATION
    int random_number = rand() % 768;
    setPos(1024,random_number);

    //draw the graphics
    setPixmap(QPixmap(":/images/imp.png").scaled(35,40));

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = game->timer;
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    // start the timer
    timer->start();
}

/**@brief calls the move function for the object*/
void Enemy::update() {
    move();
}

/**@brief moves the enemy across the board to the right, decreases player health if it crosses the left side*/
void Enemy::move() {
    //move enemy across scene to the left
    setPos(x()-2,y());

    if (x() < 0) {
        game->decrease_player_health();
        game->level->player_health_text->setPlainText(QString("Player Health: ") + QString::number(game->get_player_health()));
        scene()->removeItem(this);
        delete this;
    }
}
