/**@file wrath.cpp
@brief holds implementation for wrath class
*/

#include "wrath.h"
#include "enemies.h"
#include "game.h"
#include <QList>
#include <QGraphicsScene>

extern Game* game;

/**@brief default constructor for wrath object, mainly just draws the graphic */
Wrath::Wrath(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent) {
    //draw graphics
    setPixmap(QPixmap(":/images/wrath.png").scaled(25,25));

    //set timer for moving
    QTimer* wrath_timer = game->timer;
    QObject::connect(wrath_timer,SIGNAL(timeout()),this,SLOT(update()));
    wrath_timer->start();
}

/**@brief calls the move function */
void Wrath::update() {
    move();
}

/**@brief moves the attack object to the right of the screen against oncoming enemies
 * also checks to see if it collides with an enemy and will remove both from the scene
*/
void Wrath::move() {
    //first check if the attack is colliding with an enemy
    //if it is colliding, we destroy both the attack and the enemy
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (auto x : colliding_items) {
        if (typeid(*(x)) == typeid(Enemy)) {
            //increment score
            game->increment_player_score();
            game->level->player_kills_text->setPlainText(QString("Enemies killed: ") + QString::number(game->get_player_kills()));

            //remove both
            scene()->removeItem(x);
            scene()->removeItem(this);

            delete x;
            delete this;
            return;
        }
    }

    //move bullet to the right
    setPos(x()+5,y());

    //check to see if object is off screen
    if (x() > 1024) {
        scene()->removeItem(this);
        delete this;
    }
}
