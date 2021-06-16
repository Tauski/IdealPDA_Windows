#ifndef CALENDARPUSHBUTTON_H
#define CALENDARPUSHBUTTON_H

#include <QPushButton>

class CalendarPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CalendarPushButton(const QString& text, QWidget* parent = nullptr);

signals:

};

#endif // CALENDARPUSHBUTTON_H
