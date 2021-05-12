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
    connect(&m_gateway,SIGNAL(requestDone()),this,SLOT(loginDone()));
    connect(&m_gateway,SIGNAL(registerDone()),this, SLOT(registerDone()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::loginDone()
{
    qDebug() << "login done";

    this->accept();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::registerDone()
{
    qDebug() << "register done";
    ui->stackedWidget->setCurrentIndex(0);
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("New user registered");
    msgBox.exec();
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
        m_gateway.registerUser(ui->le_diaRegUsername->text(),ui->le_diaRegPassword->text(),ui->le_diaRegEmail->text());
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
    }else{
        m_gateway.checkCredentials(ui->le_logDiaUsername->text(),ui->le_logDiaPassword->text());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void LoginDialog::on_pb_newRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
