#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QByteArray>
#include <QRegExp>

#include "ProgramSettings.h"

namespace Ui {
class ProfileDialog;
}

/**
    \brief Window with fields to change credential data and
    program preferences(WIP)
*/
class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = nullptr);
    ~ProfileDialog();

    bool emailValid(QString email);

private slots:

    ///Save changes on profile dialog
    void on_pd_bp_saveChanges_clicked();

    ///Detect changes on passwords linedit
    void on_pd_le_newPass_editingFinished();

    ///Detect changes on usernames linedit
    void on_pd_le_newUsername_editingFinished();

    ///Detect changes on emails linedit
    void on_pd_le_newEmail_editingFinished();

    ///Slot for retrieing managers finished signal with reply
    void updateSent(QNetworkReply *uReply);

private:
    Ui::ProfileDialog *ui;

    ///Url used to change user data from database
    const QString m_updateUrl = "http://192.168.1.103:8012/project/Credentials/userCredentialsChange.php";

    bool m_emailIsChanged;
    bool m_usernameIsChanged;
    bool m_passwordIsChanged;

    ///Object of NetworkAccessManager
    QNetworkAccessManager * m_manager;
};

#endif // PROFILEDIALOG_H