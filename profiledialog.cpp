#include "profiledialog.h"
#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileDialog),
    m_newUsername(),
    m_newEmail(),
    m_gateway(this)
{
    ui->setupUi(this);

    ///Set current value labels
    ui->pd_bp_saveChanges->hide(); //hide until changes
    ui->pd_label_curUname->setText(g_username);
    ui->pd_label_curEmail->setText(g_userEmail);
    ui->pd_label_curlocation->setText(g_userLocation);

    connect(&m_gateway, &NetworkGateway::credentialsUpdated, this, &ProfileDialog::updateConfirmed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

ProfileDialog::~ProfileDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool ProfileDialog::emailValid(QString email)
{
    QRegExp regex("^[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?$");
    if(regex.exactMatch(email))
    {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_bp_saveChanges_clicked()
{
    if(ui->pd_le_newEmail->text().isEmpty() && ui->pd_le_newUsername->text().isEmpty() && ui->pd_le_newPass->text().isEmpty() && ui->pd_le_newlocation->text().isEmpty())
    {
        ///All updatable fields were empty so do nothing
        return;
    }

    ///Can be empty, handled in API
    QString newUsernameString = ui->pd_le_newUsername->text();
    QString newEmailString = ui->pd_le_newEmail->text();
    QString newLocationString = ui->pd_le_newlocation->text();

    ///Check if password fields are both empty or has text
    if(ui->pd_le_curPassword->text().isEmpty() && !ui->pd_le_newPass->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You need to give current password if you want to change it. If you don't remember your password you can reset it from login screen");
        msgBox.exec();

        ui->pd_le_curPassword->setText("");
        ui->pd_le_newPass->setText("");
    }

    ///Create network request
    QVector<QString> params;
    params.push_back("change");
    params.push_back(ui->pd_label_curUname->text());
    params.push_back(newUsernameString);
    params.push_back(ui->pd_le_curPassword->text());
    params.push_back(ui->pd_le_newPass->text());
    params.push_back(ui->pd_label_curEmail->text());
    params.push_back(newEmailString);
    params.push_back(ui->pd_label_curlocation->text());
    params.push_back(newLocationString);
    m_gateway.sendCredentialsPost(params);

    ///Insert possible new values.
    m_newUsername = newUsernameString;
    m_newEmail = newEmailString;
    m_newLocation = newLocationString;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newPass_editingFinished()
{
    ui->pd_bp_saveChanges->show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newUsername_editingFinished()
{
    ui->pd_bp_saveChanges->show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newEmail_editingFinished()
{
    ui->pd_bp_saveChanges->show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newlocation_textChanged(const QString &arg1)
{
    ui->pd_bp_saveChanges->show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::updateConfirmed()
{
    QString replyString = m_gateway.getCredentialsReply();

    ///New values confirmed update globals
    if(!replyString.contains("ERROR")) //Error echoes only when something went wrong
    {
        this->accept();

        g_username = m_newUsername.isEmpty() ? g_username : m_newUsername;
        g_userEmail = m_newEmail.isEmpty() ? g_userEmail : m_newEmail;
        g_userLocation = m_newLocation.isEmpty() ? g_userLocation : m_newLocation;
    }
    else
    {
        QMessageBox profileMsg;
        profileMsg.setIcon(QMessageBox::Warning);
        profileMsg.setText("Error while updating data... please try again \n" + replyString);
        profileMsg.exec();
    }
}



