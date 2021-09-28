#include "logindialog.h"
#include "ui_logindialog.h"
#include "ProgramSettings.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_gateway(this)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(&m_gateway,&NetworkGateway::credentialsOk,this,&LoginDialog::credentialsAccepted);
    connect(&m_gateway,&NetworkGateway::pingOk,this,&LoginDialog::pingRecieved);

    m_gateway.sendPingPost();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

LoginDialog::~LoginDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::credentialsAccepted()
{
    ///Get reply from gateway
    QString typeReply = m_gateway.getCredentialsReply();

    if(typeReply == "register")
    {
        qDebug() << "register done";
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("New user registered, now login using your username and password");
        msgBox.exec();
    }
    else if(typeReply == "login")
    {
        qDebug() << "login done";
        this->accept();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::pingRecieved()
{
    ///Reply
    QString pingReply = m_gateway.getPingReply();

    if(pingReply == "Ok")
    {

    }
    else if (pingReply == "NoCon")
    {

    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::on_pb_diaReg_clicked()
{
    if(ui->le_diaRegUsername->text().isEmpty() || ui->le_diaRegPassword->text().isEmpty() || ui->le_diaRegEmail->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("username, password or email cannot be empty");
        msgBox.exec();

        ui->le_diaRegEmail->setText("");
        ui->le_diaRegUsername->setText("");
        ui->le_diaRegPassword->setText("");
    }
    else
    {
        ///Generate post to register new user
        QVector<QString> postVector;
        postVector.push_back("register");
        postVector.push_back(ui->le_logDiaUsername->text());
        postVector.push_back(ui->le_diaRegEmail->text());
        postVector.push_back(ui->le_logDiaPassword->text());
        m_gateway.sendCredentialsPost(postVector);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::on_pb_login_clicked()
{
    if(ui->le_logDiaUsername->text().isEmpty() || ui->le_logDiaPassword->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("username or password cannot be empty");
        msgBox.exec();

        ui->le_logDiaUsername->setText("");
        ui->le_logDiaPassword->setText("");
    }
    else
    {
        ///Generate post to check given credentials
        QVector<QString> postVector;
        postVector.push_back("check");
        postVector.push_back(ui->le_logDiaUsername->text());
        postVector.push_back(ui->le_logDiaPassword->text());
        m_gateway.sendCredentialsPost(postVector);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::on_pb_newRegister_clicked()
{
    ///change page to register side
    ui->stackedWidget->setCurrentIndex(1);
}
