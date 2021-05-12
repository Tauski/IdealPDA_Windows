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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb2_clicked();

    void on_pb1_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
