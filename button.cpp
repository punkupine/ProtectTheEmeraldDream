/**@file button.cpp
 * @brief holds the implementation for custom Button class
 */

#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>

/**@brief constructor for Button
 * draws the button, changes the color, draws the text, and sets position of text
*/
Button::Button(QString label, QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    //draw the button
    setRect(0,0,200,50);

    //change the color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);

    //draw the text
    text = new QGraphicsTextItem(label, this);

    //set position of text within button
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos); //places text in the middle of the button

    //allow response to hover events
    setAcceptHoverEvents(true);
}

/**@brief sets up how button should react to a mousePressEvent, which is to trigger the clicked() signal
*/
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}

/**@brief changes the color to be different than original color when hovering
*/
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    //change color from dark green to green
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
}

/**@brief changes the color back to the original color of the button
*/
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color to dark green
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGreen);
    setBrush(brush);
}

