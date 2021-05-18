#ifndef CREDENTIALSGATEWAY_H
#define CREDENTIALSGATEWAY_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QUrlQuery>

/**
  \brief handles all credential interactions with database through rest api
*/
class CredentialsGateway : public QObject
{
    Q_OBJECT

public:

    CredentialsGateway(QObject *parent = nullptr);
    ~CredentialsGateway();

    ///Reply slot for networkaccessmanager
    void fileDownloaded(QNetworkReply* pReply);

    ///checks given credentials from database
    void checkCredentials(QString ccName, QString ccPassword);

    ///Registers new user with given parameters
    void registerUser(QString rName, QString rPassword, QString rEmail);

    ///Searches given user by email
    void findUserByEmail(QString fuEmail);

    ///Status of given credentials false if not found
    bool getCredentialsStatus();

    ///Retrieves users email address from database.
    void getEmail(QString name);

signals:

    ///Emited to logindialogs loginDone() slot
    void requestDone();

    ///Emited to logindialogs registedDone() slot
    void registerDone();

private:

    ///Url to use when inserting data to credentials (mostly register usage).
    const QString m_insertUrl = "http://192.168.1.103:8012/project/Credentials/insert.php";

    ///Url to use when checking credentials during login.
    const QString m_loginUrl = "http://192.168.1.103:8012/project/Credentials/UserLogin.php";

    ///Url to use when retrieving users email address from database.
    const QString m_getEmailUrl = "http://192.168.1.103:8012/project/Credentials/userGetEmail.php";

    ///Url to use when deleting user from database WIP.
    //const QString m_deleteUserUrl;

    ///Object of networkaccessmanager
    QNetworkAccessManager *m_manager; //manager object

    ///Flag if credentials are usable
    bool m_credentialsStatus;

};

#endif // CREDENTIALSGATEWAY_H
