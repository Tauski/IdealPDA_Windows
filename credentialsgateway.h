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
  BRIEF:
  handles all credential interactions with REST api


*/
class CredentialsGateway : public QObject
{
    Q_OBJECT

public:
    CredentialsGateway(QObject *parent = nullptr);
    ~CredentialsGateway();

    void fileDownloaded(QNetworkReply* pReply);
    void checkCredentials(QString ccName, QString ccPassword);
    void registerUser(QString rName, QString rPassword, QString rEmail);
    void findUser(QString fuName);
    void findUserByEmail(QString fuEmail);
    bool getCredentialsStatus();

signals:

    void requestDone();
    void registerDone();

private:

    const QString m_insertUrl = "http://192.168.1.103:8012/project/Credentials/insert.php";
    const QString m_loginUrl = "http://192.168.1.103:8012/project/Credentials/UserLogin.php";
    const QString m_deleteUserUrl = "WIP";

    QNetworkAccessManager *m_manager;

    bool m_credentialsStatus;

};

#endif // CREDENTIALSGATEWAY_H
