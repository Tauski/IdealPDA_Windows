#ifndef CALENDARPUSHBUTTON_H
#define CALENDARPUSHBUTTON_H

#include <QPushButton>

/**
    \brief Custom pushbutton to use in calendar dialog to create pressable dates
*/
class CalendarPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CalendarPushButton(const QString& text, QWidget* parent = nullptr);

signals:

};

#endif // CALENDARPUSHBUTTON_H
