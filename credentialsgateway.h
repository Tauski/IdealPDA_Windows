#ifndef CREDENTIALSGATEWAY_H
#define CREDENTIALSGATEWAY_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QByteArray>
#include <QObject>
#include <QVector>
#include <QUrl>

/**
  \brief handles all credential interactions with REST api
*/
class CredentialsGateway : public QObject
{
    Q_OBJECT

public:

    CredentialsGateway(QObject *parent = nullptr);
    ~CredentialsGateway();

    //Reply slot for networkaccessmanager
    void fileDownloaded(QNetworkReply* pReply);

    //checks given credentials from database
    void checkCredentials(QString ccName, QString ccPassword);

    //Registers new user with given parameters
    void registerUser(QString rName, QString rPassword, QString rEmail);

    //Searches given user by email
    void findUserByEmail(QString fuEmail);

    //Status of given credentials false if not found
    bool getCredentialsStatus();

signals:

    //Emited to logindialogs loginDone() slot
    void requestDone();

    //Emited to logindialogs registedDone() slot
    void registerDone();

private:

    const QString m_insertUrl = "http://192.168.1.103:8012/project/Credentials/insert.php";
    const QString m_loginUrl = "http://192.168.1.103:8012/project/Credentials/UserLogin.php";
    const QString m_deleteUserUrl = "WIP";

    QString m_username;

    QNetworkAccessManager *m_manager; //manager object

    bool m_credentialsStatus; //Status of given credentials false by default and if found correct changed to true

};

#endif // CREDENTIALSGATEWAY_H
