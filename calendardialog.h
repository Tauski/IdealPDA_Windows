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

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    ~CalendarDialog();

public slots:

    ///Slot that listens Networkmanagers calendarOk signal
    void gotEvents();

private slots:

    ///CalendarPushButton clicked,
    void calendarButtonClicked();

    ///Add new event for the given date
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

    ///String to use when getting all notes
    const QString m_getEventsUrl = "http://192.168.1.103:8012/project/Calendar/userEventsGetNew.php";
};

#endif // CALENDARDIALOG_H
