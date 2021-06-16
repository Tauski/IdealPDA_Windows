#include "calendareventdialog.h"
#include "ui_calendareventdialog.h"

CalendarEventDialog::CalendarEventDialog(QWidget *parent,QString eventTitle) :
    QDialog(parent),
    ui(new Ui::CalendarEventDialog),
    m_gateway(this,1),
    m_eventTitle(eventTitle)
{
    ui->setupUi(this);
    if(m_eventTitle == "")
    {
        connect(&m_gateway, &NetworkGateway::calendarOk,this,&CalendarEventDialog::eventSent);
    }
    else
    {
        ///disable/enable necessary stuff
        ui->ced_pb_saveEvent->setDisabled(true);
        ui->ced_pb_updateEvent->setEnabled(true);
        ui->ced_pb_deleteEvent->setEnabled(true);

        ///Connections for getting event and updating event
        connect(&m_gateway, &NetworkGateway::calendarOk, this, &CalendarEventDialog::eventGot);
        connect(&m_gateway, &NetworkGateway::calendarUpdated,this,&CalendarEventDialog::eventUpdated);

        ///Build event dialog if was opened from eventList
        getEventByTitle(m_eventTitle);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

CalendarEventDialog::~CalendarEventDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::setEventDate(QDate date)
{
    m_date = date;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::eventSent()
{
    qDebug() << "event sent";
    this->accept();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::eventGot()
{
    ///Set text fields according to reply data
    QVector<QString> eventData = m_gateway.getCalendarReply();
    ui->ced_le_title->setText(eventData.at(0));
    ui->ced_dateTime_start->setTime(QTime::fromString(eventData.at(2)));
    ui->ced_le_location->setText(eventData.at(3));
    ui->ced_te_body->setText(eventData.at(4));

    ///Hold old title incase update is needed
    m_oldTitle = eventData.at(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::eventUpdated()
{
    ///get reply and generate msgbox
    QString reply = m_gateway.getEventReply();
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(reply);
    msgBox.exec();

    this->accept();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::eventDeleted()
{    
    QString replyString = m_gateway.getEventReply();
    if(replyString == "Event Deleted")
    {
        this->accept();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(replyString);
        msgBox.exec();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::on_ced_pb_saveEvent_clicked()
{
    QString eventTitle = ui->ced_le_title->text();
    QString eventBody = ui->ced_te_body->toPlainText();
    QString eventLocation = ui->ced_le_location->text();

    ///Only need start time
    QString eventDate = m_date.toString(Qt::ISODate);
    QString eventTime = ui->ced_dateTime_start->time().toString("hh:mm:ss");

    ///Only title is required
    if(eventTitle.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You can't save event without title");
        msgBox.exec();
    }
    else
    {
        ///generate gateway post to save event into database
        QVector<QString> params;
        params.push_back("addEvent");
        params.push_back(g_username);
        params.push_back(eventTitle);
        params.push_back(eventDate);
        params.push_back(eventTime);
        params.push_back(eventLocation);
        params.push_back(eventBody);
        m_gateway.sendCalendarPost(params);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::getEventByTitle(const QString title)
{
    ///generate gateway post to get event by title
    QVector<QString>params;
    params.push_back("getEventByTitle");
    params.push_back(g_username);
    params.push_back(title);
    m_gateway.sendCalendarPost(params);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::on_ced_pb_updateEvent_clicked()
{
    ///generate gateway post to update event
    QVector<QString>params;
    params.push_back("updateEvent");
    params.push_back(g_username);
    params.push_back(ui->ced_le_title->text());
    params.push_back(m_oldTitle);
    params.push_back(ui->ced_le_location->text());
    params.push_back(ui->ced_te_body->toPlainText());
    params.push_back(m_date.toString(Qt::ISODate));
    params.push_back(ui->ced_dateTime_start->time().toString("hh:mm:ss"));
    m_gateway.sendCalendarPost(params);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarEventDialog::on_ced_pb_deleteEvent_clicked()
{
    ///Disconnect event finder to allow event delete
    disconnect(&m_gateway, &NetworkGateway::calendarOk,this,&CalendarEventDialog::eventGot);
    connect(&m_gateway, &NetworkGateway::calendarOk, this, &CalendarEventDialog::eventDeleted);

    ///generate gateway post
    QVector<QString>params;
    params.push_back("deleteEvent");
    params.push_back(g_username);
    params.push_back(m_eventTitle);
    m_gateway.sendCalendarPost(params);
}
