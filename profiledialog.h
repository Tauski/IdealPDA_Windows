#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QUrlQuery>
#include <QRegExp>

#include "ProgramSettings.h"

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

    ///Detect changes on passwords linedit.
    void on_pd_le_newPass_editingFinished();

    ///Detect changes on usernames linedit.
    void on_pd_le_newUsername_editingFinished();

    ///Detect changes on emails linedit.
    void on_pd_le_newEmail_editingFinished();

    ///Slot for retrieing managers finished signal with reply.
    void updateSent(QNetworkReply *uReply);

private:

    Ui::ProfileDialog *ui;

    ///Url used to change user data from database.
    const QString m_updateUrl = "http://192.168.1.103:8012/project/Credentials/userCredentialsChange.php";

    bool m_emailIsChanged;
    bool m_usernameIsChanged;
    bool m_passwordIsChanged;

    ///Hold new username to update global username variable after reply.
    QString m_newUsername;

    ///Hold new email to update global email variable after reply.
    QString m_newEmail;

    ///Object of NetworkAccessManager
    QNetworkAccessManager * m_manager;
};

#endif // PROFILEDIALOG_H
