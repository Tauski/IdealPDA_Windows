#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include "ProgramSettings.h"
#include "networkgateway.h"

namespace Ui {
class ProfileDialog;
}

/**
    \brief Dialog with fields to change credential data and
    program preferences(TODO)
*/
class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = nullptr);
    ~ProfileDialog();

    ///Go through regex check for regular email type, catches most type cases
    bool emailValid(QString email);

private slots:

    ///Save changes on profile dialog.
    void on_pd_bp_saveChanges_clicked();

    ///Detect changes on passwords lineEdit.
    void on_pd_le_newPass_editingFinished();

    ///Detect changes on usernames lineEdit.
    void on_pd_le_newUsername_editingFinished();

    ///Detect changes on emails lineEdit.
    void on_pd_le_newEmail_editingFinished();

    ///SLot for m_gateways credentialsUpdated signal.
    void updateConfirmed();

    ///Detect changes on location lineEdit
    void on_pd_le_newlocation_textChanged(const QString &arg1);

private:

    Ui::ProfileDialog *ui;

    ///Url used to change user data from database.
    const QString m_updateUrl = "http://192.168.1.103:8012/project/Credentials/userCredentialsChange.php";

    ///Hold new username to update global username variable after reply.
    QString m_newUsername;

    ///Hold new email to update global email variable after reply.
    QString m_newEmail;

    ///Holds new location to update global location variable if reply is correct
    QString m_newLocation;

    ///Object of NetworkAccessManager
    NetworkGateway m_gateway;
};

#endif // PROFILEDIALOG_H
