#include "credentialsgateway.h"

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

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::fileDownloaded(QNetworkReply* pReply)
{
    QByteArray replyArray = pReply->readAll();
    qDebug()<< replyArray;
    QString replyString = replyArray;

    if(replyString == "Data Matched")
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
        msgBox.setText("Error while inserting or retrieving data from database");
        msgBox.exec();
    }

    /*else if(replyString == "user deleted successfully")
    {
        emit deleteDone();
    }*/

    pReply->deleteLater();
}
