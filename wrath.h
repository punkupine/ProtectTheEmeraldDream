#ifndef WRATH_H
#define WRATH_H

/**@file wrath.h
@brief holds the declarations for wrath class
*/

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>

/**@class Wrath
@brief handles functions of the attack object of the player
*/
class Wrath : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Wrath(QGraphicsItem* parent = nullptr);

    void move();

public slots:
    void update();
};

#endif // WRATH_H
