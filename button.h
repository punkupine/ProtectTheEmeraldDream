#ifndef BUTTON_H
#define BUTTON_H

/**@file button.h
 * @brief holds the declarations for custom Button class
 */

#include<QGraphicsRectItem>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsSceneHoverEvent>
#include<QString>
#include<QObject>

/**@class Button
 * @brief mimics a push button with custom functionality
*/
class Button : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    //constructors
    Button (QString label, QGraphicsItem *parent = nullptr);

    //public member functions
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();

private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
