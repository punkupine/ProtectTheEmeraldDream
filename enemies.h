#ifndef ENEMIES_H
#define ENEMIES_H

/**@file enemies.h
@brief holds the declarations for the Enemy class which handles all enemies
*/


#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>

/**@class Enemy
@brief handles movement and actions of the enemy objects
*/
class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = nullptr);

    void move();

public slots:
    void update();

private:

};

#endif // ENEMIES_H
