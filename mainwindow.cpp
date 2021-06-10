#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb2_clicked
/// Opens New Note Dialog
void MainWindow::on_pb2_clicked()
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
void MainWindow::on_pb1_clicked()
{
    this->hide();
    CalendarDialog cal;
    if(cal.exec() == QDialog::Accepted)
    {
        qDebug() << "calendarDialog accepted";
        this->show();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::on_pb5_clicked
/// Opens all notes dialog
void MainWindow::on_pb5_clicked()
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
/// \brief MainWindow::on_pb9_clicked
/// Opens Profile settings dialog
void MainWindow::on_pb9_clicked()
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
/// \brief MainWindow::on_pb7_clicked
/// Opens Weather dialog
///

void MainWindow::on_pb7_clicked()
{
    this->hide();
    WeatherDialog weaDialog;
    if(weaDialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Weather Dialog accepted";
        this->show();
    }
}
