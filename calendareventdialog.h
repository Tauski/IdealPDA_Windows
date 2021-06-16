#ifndef CALENDAREVENTDIALOG_H
#define CALENDAREVENTDIALOG_H

#include <QDialog>

#include "ProgramSettings.h"
#include "networkgateway.h"

namespace Ui {
class CalendarEventDialog;
}


/**
    \brief Used to create new event with required data, or opened with existing data when
    previously created event was clicked in event list in CalendaDialog
*/
class CalendarEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarEventDialog(QWidget *parent = nullptr, QString eventTitle = NULL);
    ~CalendarEventDialog();

    ///Gets selected date from calendar dialog
    void setEventDate(QDate date);

public slots:

    ///New event sent to database successfully
    void eventSent();

    ///Set dialog text fields with data from database
    void eventGot();

    ///Old event deleted from database successfully
    void eventDeleted();

    ///Old event updated in database
    void eventUpdated();

private slots:

    ///Save clicked so generate gateway post and send it to api
    void on_ced_pb_saveEvent_clicked();

    ///Update clicked so generate updated post and send it to api
    void on_ced_pb_updateEvent_clicked();

    ///Delete clicked so Generate delete post and send it to api
    void on_ced_pb_deleteEvent_clicked();

private:

    ///Generates post to gateway to find event by title
    void getEventByTitle(const QString title);

    Ui::CalendarEventDialog *ui;

    ///Instance of networkGateway
    NetworkGateway m_gateway;

    ///Title of existing event to use when finding its data
    const QString m_eventTitle;

    ///Holds old title to update it for database
    QString m_oldTitle;

    ///Selected date
    QDate m_date;
};

#endif // CALENDAREVENTDIALOG_H
