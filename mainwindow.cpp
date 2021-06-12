#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb7_clicked
/// Opens Weather dialog
void MainWindow::on_mw_pb_weather_clicked()
{
    this->hide();
    WeatherDialog weaDialog;
    if(weaDialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Weather Dialog accepted";
        this->show();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_mw_pb_email_clicked
/// Opens Email dialog
void MainWindow::on_mw_pb_email_clicked()
{
    ///TODO
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb9_clicked
/// Opens Profile settings dialog
void MainWindow::on_mw_pb_profile_clicked()
{
    this->hide();
    ProfileDialog proDialog;
    if(proDialog.exec() == QDialog::Accepted)
    {
        qDebug() << "profileDialog accepted";
        this->show();
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb5_clicked
/// Opens all notes dialog
void MainWindow::on_mw_pb_notelist_clicked()
{
    this->hide();
    NoteListDialog notelist;
    if(notelist.exec() == QDialog::Accepted)
    {
        qDebug() << "notelistDialog accepted";
        this->show();
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb2_clicked
/// Opens New Note Dialog
void MainWindow::on_mw_pb_notes_clicked()
{
    this->hide();
    NoteDialog note(this,"");
    if(note.exec() == QDialog::Accepted)
    {
        qDebug() << "noteDialog accepted";
        this->show();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb1_clicked
/// Opens Calendar dialog
void MainWindow::on_mw_pb_calendar_clicked()
{
    this->hide();
    CalendarDialog cal;
    if(cal.exec() == QDialog::Accepted)
    {
        qDebug() << "calendarDialog accepted";
        this->show();
    }
}

void MainWindow::on_mw_pb_weather_pressed()
{
    qDebug() << "this was pressed";
}
