#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "networkgateway.h"

namespace Ui {
class LoginDialog;
}

/**
    \brief Handles sending data connected to credentials.
    Like new users registration and users login
*/
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:

    ///Page 1 Register buttons clicked method handling
    void on_pb_diaReg_clicked();

    ///Page 1 Login buttons clicked
    void on_pb_login_clicked();

    ///Page 2 Register buttons clicked method handling
    void on_pb_newRegister_clicked();

public slots:

    ///Retrieves emitted signal from networkGateway when reply is done
    void credentialsAccepted();

    void pingRecieved();

private:

    Ui::LoginDialog *ui;

    ///instance of credentials gateway
    NetworkGateway m_gateway;
};

#endif // LOGINDIALOG_H
