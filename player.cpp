/**@file player.cpp
 * @brief holds implementation for class Player
*/

#include "player.h"
#include "input.h"
#include <QGraphicsScene>
#include "game.h"

extern Game* game;

/**@brief constructor for Player object
 * draws the player and sets it as the focus to be able to respond to keyPressEvents and other inputs
*/
Player::Player(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    //draw the player graphics
    setPixmap(QPixmap(":/images/night_elf.png").scaled(50,100));

    health = 3;
    enemies_killed = 0;

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

/**@brief creates a new attack wrath object */
void Player::attack() {
    //player attack
    //create the wrath attack object
    Wrath* wrath = new Wrath();
    wrath->setPos(x(),y()); //sets the position of the attack to be where the player is
    scene()->addItem(wrath);
}

/**@brief moves player according to inputs on keyboard
 * will move diagonally in a smooth motion as it reacts to which keys are being pressed
 * keeps track of movement through updating x and y coordinates based on input and then normalizes based on desired speed
 */
void Player::move() {
    //player movement

    //keeps track of how far the player will move
    float dx = 0.0f;
    float dy = 0.0f;

    //adds or subtracts speed from x and y axes depending on keys being pressed
    if (Input::pressed(Qt::Key_W) || Input::pressed(Qt::Key_Up) ) {
        dy -= speed;
    }
    if (Input::pressed(Qt::Key_A) || Input::pressed(Qt::Key_Left) ) {
        dx -= speed;
    }
    if (Input::pressed(Qt::Key_S) || Input::pressed(Qt::Key_Down) ) {
        dy += speed;
    }
    if (Input::pressed(Qt::Key_D) || Input::pressed(Qt::Key_Right) ) {
        dx += speed;
    }

    //normalizes diagonal movement
    if (dx != 0.0f && dy != 0.0f) {
        dx*=0.7071f;
        dy*=0.7071f;
    }
    setPos(x()+dx,y()+dy);
}

/**@brief updates player actions
 * if space is pressed, player will call attack function
 * also checks to see if game should be over
 */
void Player::update() {
    move();

    if (Input::just_pressed(Qt::Key_Space)) {
        attack();
    }

    //check to see if player is dead
    if (health <= 0) {
        game->display_game_over();
        return;
    }

    //check to see if player has won
    if (enemies_killed >= 10) {
        game->display_end_screen();
        return;
    }
}

/**@brief updates player score based on an enemy kill */
void Player::increment_score() {
    ++enemies_killed;
}

int Player::get_health() const {
    return health;
}

int Player::get_kills() const {
    return enemies_killed;
}

/**@brief decreases player health based on an enemy making it to the other side of the screen */
void Player::decrease_health() {
    health-=1;
}

/**@brief creates new enemy object and adds it to the scene */
void Player::spawn_enemies() {
    Enemy* enemy = new Enemy();
    scene()->addItem(enemy);
}
