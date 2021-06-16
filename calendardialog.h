#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QDebug>
#include "calendarpushbutton.h"
#include "calendareventdialog.h"
#include "networkgateway.h"

namespace Ui {
class CalendarDialog;
}

/**
    \brief Calendar dialog to create events and keep time/dates
*/
class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    ~CalendarDialog();

public slots:

    ///Slot that listens NetworkGateways calendarOk signal
    void gotEvents();

private slots:

    ///Date on calendar clicked
    void calendarButtonClicked();

    ///Add new event for the selected date
    void on_cd_pb_addEvents_clicked();

    ///Open event dialog with given event
    void eventClicked();

private:

    Ui::CalendarDialog *ui;

    ///Populate month calendar with calendarPushButtons.
    void insertCalendarButtons(long long int selectedDateTimeSinceEpoch);

    ///Generate post for NetworkGateway
    void eventListPost();

    ///Instance of NetworkGateway
    NetworkGateway m_gateway;

    ///Holds currently selected date from calendar
    QDate m_selectedDate;
};

#endif // CALENDARDIALOG_H
