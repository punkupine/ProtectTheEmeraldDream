/**@file level.cpp
 * @brief holds implementation for class Level
*/

#include "level.h"
#include "game.h"
#include <QMediaPlayer>
#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <QBrush>
#include <QImage>
#include <QString>
#include <QFont>

extern Game* game;

/**@brief constructor for Level object
 * sets the scene to be same size as Game window, intializes a Player and adds it to the scene
*/
Level::Level(QGraphicsScene *parent) {
    //set the scene to be the right size
    this->setSceneRect(0,0,1024,768);
    this->setBackgroundBrush(QBrush(QImage(":/images/forest.png").scaled(1024,768)));

    //add in input
    input = new Input();
    this->addWidget(input);
    input->update();

    //add a player object to the scene
    player = new Player(nullptr);
    this->addItem(player);

    //play background music
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgmusic.mp3"));
    music->setVolume(5);
    music->play();

    //set up score / health signs
    player_health_text = new QGraphicsTextItem();
    player_health_text->setPlainText(QString("Player Health: ") + QString::number(player->get_health()));
    player_health_text->setDefaultTextColor(Qt::white);
    QFont health_text_font ("Lithos Pro", 16);
    player_health_text->setFont(health_text_font);
    this->addItem(player_health_text);

    player_kills_text = new QGraphicsTextItem();
    player_kills_text->setPlainText(QString("Enemies killed: ") + QString::number(player->get_kills()));
    player_kills_text->setDefaultTextColor(Qt::white);
    player_kills_text->setFont(health_text_font);
    player_kills_text->setPos(player_kills_text->x(), player_kills_text->y()+17);
    this->addItem(player_kills_text);

    //restart the timer in case the player is beginning a new game after restarting
    game->timer->start();

    //start spawning enemies
    QTimer * enemy_timer = new QTimer();
    QObject::connect(enemy_timer,SIGNAL(timeout()),player,SLOT(spawn_enemies()));
    enemy_timer->start(2250);

}

/**@brief destructor for Level object, adds in special functionality of ensuring that the level properly shuts down*/
Level::~Level() {
    music->stop();
    game->timer->stop();
}

/**@brief calls update on member variables, also checks to see if player hits Escape at any time to Quit the game*/
void Level::update() {
    if (Input::just_pressed(Qt::Key_Escape)) game->close();
    player->update();
    input->update();
}
