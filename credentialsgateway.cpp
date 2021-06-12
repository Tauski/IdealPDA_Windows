#include "credentialsgateway.h"
#include "ProgramSettings.h"


CredentialsGateway::CredentialsGateway(QObject *parent)
    : QObject(parent),
    m_credentialsStatus(false),
    m_username("")
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &CredentialsGateway::fileDownloaded);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

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
    m_username = ccName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::registerUserDatabase(QString rName, QString rPassword, QString rEmail)
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
    qDebug() << "TODO";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool CredentialsGateway::getCredentialsStatus()
{
    return m_credentialsStatus;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::getEmailDatabase(QString name)
{
    QUrl getEmailUrl(m_getEmailUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",name);
    QNetworkRequest request(getEmailUrl);
    m_manager->post(request,params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::getLocationDatabase(QString username)
{
    QUrl getLocationUrl(m_getLocationUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",username);
    QNetworkRequest request(getLocationUrl);
    m_manager->post(request,params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CredentialsGateway::fileDownloaded(QNetworkReply* pReply)
{

    QByteArray replyArray = pReply->readAll();
    QString replyString = replyArray;

    qDebug() << replyString;

    ///if reply string contains ID, it's good
    if(replyString == "credentialsID")
    {
        ///setup globals with approved credentials
        g_username = m_username;
        getEmailDatabase(g_username);
        getLocationDatabase(g_username);
        m_credentialsStatus = true;
        emit requestDone();
    }
    else if(replyString == "registerID")
    {
        ///register approved emit signal for logindialog
        emit registerDone();
    }
    else if(replyString.contains("emailID"))
    {
        ///add users email to global variables
        g_userEmail = replyString.remove(" emailID");
    }
    else if(replyString.contains("locationID"))
    {
        ///add users location to global variables
        g_userLocation = replyString.remove(" locationID");
    }
    /// Open messagebox when error in replystring
    else if(replyString.contains("ERROR:"))
    {

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(replyString);
        msgBox.exec();
    }

    pReply->deleteLater();
}
