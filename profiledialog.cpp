#include "profiledialog.h"
#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileDialog),
    m_emailIsChanged(false),
    m_usernameIsChanged(false),
    m_passwordIsChanged(false),
    m_newUsername(),
    m_newEmail(),
    m_manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    ui->pd_bp_saveChanges->hide(); //hide until changes
    ui->pd_label_curUname->setText(g_username);
    ui->pd_label_curEmail->setText(g_userEmail);

    connect(m_manager, &QNetworkAccessManager::finished, this, &ProfileDialog::updateSent);
}

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
    if(ui->pd_le_newEmail->text().isEmpty() && ui->pd_le_newUsername->text().isEmpty() && ui->pd_le_newPass->text().isEmpty())
    {
        //All updatable fields were empty so do nothing
        return;
    }

    QString newUsernameString = ui->pd_le_newUsername->text();
    QString newEmailString = ui->pd_le_newEmail->text();

    //Check if password fields are both empty or has text
    if(ui->pd_le_curPassword->text().isEmpty() && !ui->pd_le_newPass->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You need to give current password if you want to change it. If you don't remember your password you can reset it from login screen");
        msgBox.exec();

        ui->pd_le_curPassword->setText("");
        ui->pd_le_newPass->setText("");
    }

    //Create network request
    QUrl updateUrl(m_updateUrl);
    QUrlQuery params;
    params.addQueryItem("old_name", ui->pd_label_curUname->text());
    params.addQueryItem("new_name", newUsernameString);
    params.addQueryItem("old_password", ui->pd_le_curPassword->text());
    params.addQueryItem("new_password", ui->pd_le_newPass->text());
    params.addQueryItem("old_email", ui->pd_label_curEmail->text());
    params.addQueryItem("new_email", newEmailString);

    m_newUsername = newUsernameString;
    m_newEmail = newEmailString;

    QNetworkRequest request(updateUrl);
    m_manager->post(request, params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newPass_editingFinished()
{
    ui->pd_bp_saveChanges->show();
    m_passwordIsChanged = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newUsername_editingFinished()
{
    ui->pd_bp_saveChanges->show();
    m_usernameIsChanged = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::on_pd_le_newEmail_editingFinished()
{
    ui->pd_bp_saveChanges->show();
    m_emailIsChanged = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ProfileDialog::updateSent(QNetworkReply *uReply)
{
    QByteArray replyArray = uReply->readAll();
    qDebug() << replyArray;

    if(!replyArray.contains("ERROR")) //Error echoes only when something went wrong
    {
        this->accept();

        g_username = m_newUsername.isEmpty() ? g_username : m_newUsername;
        g_userEmail = m_newEmail.isEmpty() ? g_userEmail : m_newEmail;
    }
    else
    {
        QMessageBox profileMsg;
        profileMsg.setIcon(QMessageBox::Warning);
        profileMsg.setText("Error while updating data... please try again \n" + replyArray);
        profileMsg.exec();
    }
}
