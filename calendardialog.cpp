#include "calendardialog.h"
#include "ui_calendardialog.h"

CalendarDialog::CalendarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarDialog),
    m_gateway(this,1),
    m_selectedDate()
{
    ui->setupUi(this);
    connect(&m_gateway, &NetworkGateway::calendarOk,this,&CalendarDialog::gotEvents);

    ///setup calendar
    insertCalendarButtons(QDateTime::currentSecsSinceEpoch());

    ///Hide unnecessary things
    ui->cd_pb_addEvents->hide();
    ui->cd_pb_showEvents->hide();
    ui->cd_widget_eventList->hide();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

CalendarDialog::~CalendarDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarDialog::insertCalendarButtons(long long int selectedDateTimeSinceEpoch)
{
    /// set initial current date as systems current date
    QDateTime curDate;
    curDate.setSecsSinceEpoch(selectedDateTimeSinceEpoch);
    m_selectedDate = curDate.date();    

    ///find out first weekday of month and use it to set columns for buttons
    QDate firstDateOfMonth;
    firstDateOfMonth.setDate(curDate.date().year(),curDate.date().month(),1);
    int firstDayOfMonthWeekDay = firstDateOfMonth.dayOfWeek();

    ///Dates start from 1
    for(int i = 1; i < curDate.date().daysInMonth()+1; i++)
    {
        CalendarPushButton *button = new CalendarPushButton(QString::number(i),this);
        ///If our months weekday addition hits last day of the week reset it.
        if(firstDayOfMonthWeekDay == 8)
        {
            firstDayOfMonthWeekDay = 1;
        }
        ///firstWeek
        if(i < 7)
        {
            ui->calendarButtonLayout->addWidget(button,1,firstDayOfMonthWeekDay ,Qt::AlignCenter);
        }
        ///SecondWeek
        if(i < 14 && i > 6 )
        {
            ui->calendarButtonLayout->addWidget(button,2,firstDayOfMonthWeekDay ,Qt::AlignCenter);
        }
        ///thirdWeek
        if(i < 21 && i > 13 )
        {
            ui->calendarButtonLayout->addWidget(button,3,firstDayOfMonthWeekDay ,Qt::AlignCenter);
        }
        ///fourthWeek
        if(i < 28 && i > 20)
        {
            ui->calendarButtonLayout->addWidget(button,4,firstDayOfMonthWeekDay ,Qt::AlignCenter);
        }
        ///fifthWeek
        if(i > 27 )
        {
            ui->calendarButtonLayout->addWidget(button,5,firstDayOfMonthWeekDay ,Qt::AlignCenter);
        }
        ///connect every calendar button to single slot
        connect(button,SIGNAL(clicked()),this,SLOT(calendarButtonClicked()));
        firstDayOfMonthWeekDay++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarDialog::calendarButtonClicked()
{
    ///Enable previously disabled buttons if any
    for(int i = 0; i < ui->calendarButtonLayout->count(); i++)
    {
        QWidget *w = ui->calendarButtonLayout->itemAt(i)->widget();
        {
            if(w->isEnabled() == false)
            {
                w->setEnabled(true);
            }
        }
    }

    ///clear eventlist and hide its widget
    if(ui->cd_vl_eventListLayout->count() != 0)
    {
        QLayoutItem *child;
        while((child = ui->cd_vl_eventListLayout->takeAt(0)) != 0)
        {
            if(child->widget());
            child->widget()->setParent(NULL);
            delete child;
        }
    }
    if(!ui->cd_widget_eventList->isHidden())
    {
        ui->cd_widget_eventList->hide();
    }

    ///get clicked button text and set it disabled
    CalendarPushButton *button = (CalendarPushButton *)sender();
    button->setDisabled(true);

    ///Show event activity buttons
    ui->cd_pb_addEvents->show();
    ///generate selected date and show events
    m_selectedDate.setDate(m_selectedDate.year(),m_selectedDate.month(),button->text().toInt());

    ///populate event list
    eventListPost();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarDialog::eventListPost()
{
    ///generate gateway post
    QVector<QString> calPost;
    calPost.push_back("getAllEvents");
    calPost.push_back(g_username);
    calPost.push_back(m_selectedDate.toString(Qt::ISODate));
    m_gateway.sendCalendarPost(calPost);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarDialog::gotEvents()
{
    ///Retrieve reply from gateway and populate event list if there's events
    QVector<QString> vector = m_gateway.getCalendarReply();
    for(int i = 0; i < vector.size();i++)
    {
        QPushButton *button = new QPushButton(vector.at(i),this);
        connect(button,SIGNAL(clicked()),this,SLOT(eventClicked()));
        ui->cd_vl_eventListLayout->addWidget(button);
    }
    if(ui->cd_vl_eventListLayout->count() != 0)
    {
        ui->cd_widget_eventList->show();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarDialog::on_cd_pb_addEvents_clicked()
{
    ///Open event dialog with m_selectedDate;
    this->hide();
    CalendarEventDialog dialog(nullptr,"");
    dialog.setEventDate(m_selectedDate);
    {
        if(dialog.exec() == QDialog::Accepted)
        {
            qDebug() << "CalendarEventDialog accepted";
            this->show();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CalendarDialog::eventClicked()
{
    ///find out sender
    QPushButton *button = (QPushButton *)sender();

    ///Open new eventDialog with given buttons text as date
    this->hide();
    CalendarEventDialog dialog(nullptr,button->text());
    dialog.setEventDate(m_selectedDate);
    if(dialog.exec() == QDialog::Accepted)
    {
        qDebug() << "CalendarEventDialog accepted";
        this->show();
    }
}
