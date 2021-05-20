#ifndef CALENDAREVENTDIALOG_H
#define CALENDAREVENTDIALOG_H

#include <QDialog>

namespace Ui {
class CalendarEventDialog;
}

class CalendarEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarEventDialog(QWidget *parent = nullptr);
    ~CalendarEventDialog();

private:
    Ui::CalendarEventDialog *ui;
};

#endif // CALENDAREVENTDIALOG_H
