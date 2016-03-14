/**@file main.cpp
 * @brief holds declaration for custom Input class
*/

#ifndef INPUT_H
#define INPUT_H

#include <QKeyEvent>
#include <QWidget>

/**@class Input
@brief allows for customization of reacting to and citing inputs from keyboard and mouse
*/
class Input : public QWidget {
public:
    Input();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    static bool pressed(int code);
    static bool just_pressed(int code);
    static bool just_released(int code);

    void update();

};

#endif // INPUT_H
