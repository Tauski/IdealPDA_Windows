#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "credentialsgateway.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:

    void on_pb_diaReg_clicked();
    void on_pb_login_clicked();
    void on_pb_newRegister_clicked();

public slots:

    void loginDone();
    void registerDone();

private:
    Ui::LoginDialog *ui;
    CredentialsGateway m_gateway;
    bool m_credentials = false;
};

#endif // LOGINDIALOG_H
