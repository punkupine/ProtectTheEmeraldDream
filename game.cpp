/**@file game.cpp
 @brief holds implementation for class Game functions
*/

#include "game.h"
#include "enemies.h"
#include <QGraphicsTextItem>
#include <QObject>
#include <QMediaPlayer>
#include <QTimer>
#include <QFont>
#include <QUrl>
#include <QBrush>
#include <QGraphicsScene>

/**@brief constructs the main screen and view */
Game::Game(QWidget *parent) {
    //set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    //now we can set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);
}

/**@brief creates a new display to indicate that the player has lost and needs to restart */
void Game::display_game_over() {
    qDebug() << "game over.";

    level->input->releaseKeyboard();
    level->clear();
    delete level;
    level = nullptr;

    //clear the screen from the level
    scene = new QGraphicsScene();
    setScene(scene);

    //next create the Game Over text
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem(QString("You Perished. Game Over."));
    //set font and size
    QFont game_over_font ("28 Days Later", 25);
    gameOverText->setFont(game_over_font);
    //position the text
    int gameOverXPos = this->width()/2 - gameOverText->boundingRect().width()/2;
    int gameOverYPos = 150;
    gameOverText->setPos(gameOverXPos, gameOverYPos);
    //add it to the scene
    scene->addItem(gameOverText);


    //create back to main menu button
    Button* returnToMenu = new Button(QString("Return to Menu"));
    //position button
    int returnXPos = this->width()/2 - returnToMenu->boundingRect().width()/2;
    int returnYPos = 425;
    returnToMenu->setPos(returnXPos, returnYPos);
    //connect this button to quit the game
    QObject::connect(returnToMenu, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(returnToMenu);
}

/**@brief displays a new screen to indicate that the player has won the game */
void Game::display_end_screen() {
    level->input->releaseKeyboard();
    level->clear();
    delete level;
    level = nullptr;

    //clear the screen from the level
    scene = new QGraphicsScene();
    setScene(scene);

    //next create the end screen text
    QGraphicsTextItem* endText = new QGraphicsTextItem(QString("You defeated all the demons! Congratulations Champion!"));
    //set font and size
    QFont endFont ("Adventure", 25);
    endText->setFont(endFont);
    //position the text
    int endXPos = this->width()/2 - endText->boundingRect().width()/2;
    int endYPos = 150;
    endText->setPos(endXPos, endYPos);
    //add it to the scene
    scene->addItem(endText);


    //create back to main menu button
    Button* returnToMenu = new Button(QString("Return to Menu"));
    //position button
    int returnXPos = this->width()/2 - returnToMenu->boundingRect().width()/2;
    int returnYPos = 425;
    returnToMenu->setPos(returnXPos, returnYPos);
    //connect this button to quit the game
    QObject::connect(returnToMenu, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(returnToMenu);
}

/**@brief acts as a setter for the player health */
void Game::decrease_player_health() {
    level->player->decrease_health();
}

/**@brief acts as a setter for the number of enemies killed / score of the player */
void Game::increment_player_score() {
    level->player->increment_score();
}

/**@brief acts as a getter for the player's health*/
int Game::get_player_health() const {
    return level->player->get_health();
}

/**@brief acts as a getter for the player's number of kills*/
int Game::get_player_kills() const {
    return level->player->get_kills();
}

/**@brief begins a new game by starting the first level */
void Game::start() {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //set timer's time to 20ms
    timer->start(20);

    level = new Level();
    //need to remove current background to allow level to set background
    this->setBackgroundBrush(Qt::NoBrush);
    setScene(level);
}

/**@brief shows a set of instructions for the user to understand gameplay */
void Game::display_instructions() {
    //start by clearing the scene from the Main Menu
    scene->clear();

    //next we create the instructions portion
    QGraphicsTextItem* instructionsText =
            new QGraphicsTextItem (QString("You are about to embark on an epic quest champion! In order to protect the\n"
                                           "Emerald Dream, you must cleanse the land of demons. Use WASD or the arrow\n"
                                           "keys to move around and Spacebar to fire your wrath attack. At any time you\n"
                                           "can hit escape if the battle becomes too intense. Beware of the demons, if they\n"
                                           "cross the threshold this will lower your health. If your health reaches 0, you\n"
                                           "lose the game. If you kill 10 of the demons, you win! You have all you need\n"
                                           "now fulfill your druidic duties! May Elune be with you!"));
    //set the font and size
    QFont instructFont ("Lithos Pro", 17);
    instructionsText->setFont(instructFont);
    //position the text
    int instructXPos = this->width()/2 - instructionsText->boundingRect().width()/2;
    int instructYPos = 150;
    instructionsText->setPos(instructXPos, instructYPos);
    //add it to the scene
    scene->addItem(instructionsText);

    //create the Back to Main Menu Button
    Button* returnToMenu = new Button(QString("Return to Menu"));
    //position button
    int returnXPos = this->width()/2 - returnToMenu->boundingRect().width()/2;
    int returnYPos = 425;
    returnToMenu->setPos(returnXPos, returnYPos);
    //connect this button to quit the game
    QObject::connect(returnToMenu, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
    scene->addItem(returnToMenu);

}

/**@brief calls update on level, which calls update on its private member variables */
void Game::update() {
    if (level != nullptr) level->update();
}

/**@brief sets up the Main Menu before gameplay begins */
void Game::displayMainMenu() {
    //clear scene in case someone comes from the instructions
    scene->clear();

    //need to remove current background to allow level to set background
    this->setBackgroundBrush(Qt::NoBrush);
    //load in background photo
    this->setBackgroundBrush(QBrush(QImage(":/images/emeraldDream.jpg").scaled(1024,768)));

    //start by creating Title Text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Protect the Emerald Dream"));
    QFont titleFont ("Adventure", 50); //sets title font and size
    titleText->setFont(titleFont);
    //now we position the text
    int titleXPos = this->width()/2 - titleText->boundingRect().width()/2;
    int titleYPos = 150;
    titleText->setPos(titleXPos, titleYPos);
    //now we add it to the scene
    scene->addItem(titleText);

    //next we create the Play Button
    Button* playButton = new Button(QString("Play"));
    //now we position the button
    int buttonXPos = this->width()/2 - playButton->boundingRect().width()/2;
    int buttonYPos = 275;
    playButton->setPos(buttonXPos, buttonYPos);
    //connect this button to start the game
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    //now we add it to the scene
    scene->addItem(playButton);

    //create the Instructions Button
    Button* instructionsButton = new Button(QString("Instructions"));
    //position button
    int instructXPos = this->width()/2 - instructionsButton->boundingRect().width()/2;
    int instructYPos = 350;
    instructionsButton->setPos(instructXPos, instructYPos);
    //connect this button to show instructions
    QObject::connect(instructionsButton, SIGNAL(clicked()), this, SLOT(display_instructions()));
    scene->addItem(instructionsButton);

    //create the Quit Button
    Button* quitButton = new Button(QString("Quit"));
    //position button
    int quitXPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int quitYPos = 425;
    quitButton->setPos(quitXPos, quitYPos);
    //connect this button to quit the game
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}
