#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>
#include <QDebug>
#include <QObject>

#include "credentialsgateway.h"
#include "notedialog.h"
#include "calendardialog.h"
#include "notelistdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
    \brief Mainwindow class that will hold some kind of storage for
    all different PDA functionality dialogs.
    for now only different buttons for different dialogs.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    ///Handling Note buttons press
    void on_pb2_clicked();

    ///Handling Calendar buttons press
    void on_pb1_clicked();

    void on_pb5_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
