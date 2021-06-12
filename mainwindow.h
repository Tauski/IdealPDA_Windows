#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>

#include "credentialsgateway.h"
#include "notedialog.h"
#include "calendardialog.h"
#include "notelistdialog.h"
#include "profiledialog.h"
#include "weatherdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
    \brief Mainwindow class that will hold some kind of storage for
    all different functionality dialogs.
    for now only different buttons for different dialogs.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    ///Opens weather dialog
    void on_mw_pb_weather_clicked();

    ///Opens email dialog
    void on_mw_pb_email_clicked();

    ///Opens profile dialog
    void on_mw_pb_profile_clicked();

    ///Opens notelist dialog
    void on_mw_pb_notelist_clicked();

    ///Opens new note dialog
    void on_mw_pb_notes_clicked();

    ///Opens calendar dialog
    void on_mw_pb_calendar_clicked();

    void on_mw_pb_weather_pressed();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
