/**@file main.cpp
 * @brief holds the declarations for the Input class
*/

#include "input.h"
#include <QHash>
#include <QString>

static QHash<QString, bool> thisFrame;
static QHash<QString, bool> lastFrame;

/**@brief default constructor for Input object, grabs inputs from keyboard and hides the widget to prevent from interfering with display
*/
Input::Input() {
    QWidget::grabKeyboard();
    QWidget::hide();
}

/**@brief detects specific key press events */
void Input::keyPressEvent(QKeyEvent *event) {
    thisFrame[QKeySequence(event->key()).toString()] = true;
}

/**@brief detects specific key release events */
void Input::keyReleaseEvent(QKeyEvent *event) {
    thisFrame[QKeySequence(event->key()).toString()] = false;
}

/**@brief updates all inputs from the Keyboard coming in */
void Input::update() {
    QHash<QString, bool>::iterator it;
    for (it = thisFrame.begin(); it != thisFrame.end(); ++it) {
        lastFrame[it.key()] = it.value();
    }
}

/**@brief indiciates if a key is being pressed */
bool Input::pressed(int code) {
    return thisFrame[QKeySequence(code).toString()];
}

/**@brief indiciates if a key has just been pressed */
bool Input::just_pressed(int code) {
    return thisFrame[QKeySequence(code).toString()] && !lastFrame[QKeySequence(code).toString()];
}

/**@brief indiciates if a key has just been released */
bool Input::just_released(int code) {
    return false;
}
