#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    LoginDialog ld;
    if(ld.exec() == QDialog::Accepted)
    {
       qDebug() << "accepted emitted";
       w.show();
    }
    qDebug()<< "returning a exec";
    return a.exec();
}
