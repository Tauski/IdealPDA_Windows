#include "credentialsgateway.h"
#include "ProgramSettings.h"


CredentialsGateway::CredentialsGateway(QObject *parent)
    : QObject(parent)
    , m_credentialsStatus(false)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &CredentialsGateway::fileDownloaded);
}

CredentialsGateway::~CredentialsGateway()
{
    delete m_manager;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::checkCredentials(QString ccName, QString ccPassword)
{
    QUrl registerUrl(m_loginUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",ccName);
    params.addQueryItem("password",ccPassword);
    QNetworkRequest request(registerUrl);
    m_manager->post(request,params.query().toUtf8());

    //modifying global username from programSettings
    g_username = ccName;

    getEmail(g_username);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::registerUser(QString rName, QString rPassword, QString rEmail)
{
    QUrl registerUrl(m_insertUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",rName);
    params.addQueryItem("email",rEmail);
    params.addQueryItem("password",rPassword);
    QNetworkRequest request(registerUrl);
    m_manager->post(request,params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::findUserByEmail(QString fuEmail)
{
    qDebug() << fuEmail;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool CredentialsGateway::getCredentialsStatus()
{
    return m_credentialsStatus;
}

void CredentialsGateway::getEmail(QString name)
{
    QUrl getEmailUrl(m_getEmailUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",name);
    QNetworkRequest request(getEmailUrl);
    m_manager->post(request,params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::fileDownloaded(QNetworkReply* pReply)
{
    QByteArray replyArray = pReply->readAll();
    QString replyString = replyArray;

    //if reply string contains @ sign it should be email address
    if(replyString.contains("@"))
    {
        g_userEmail = replyString;
    }
    else if(replyString == "Data Matched")
    {
        m_credentialsStatus = true;
        emit requestDone();
    }   
    else if(replyString == "user created successfully")
    {
        emit registerDone();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Couldn't connect to database");
        msgBox.exec();
    }

    pReply->deleteLater();
}
