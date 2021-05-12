#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>

namespace Ui {
class CalendarDialog;
}

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    ~CalendarDialog();

private:
    Ui::CalendarDialog *ui;

};

#endif // CALENDARDIALOG_H
