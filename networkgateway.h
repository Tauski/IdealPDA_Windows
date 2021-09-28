#ifndef NETWORKGATEWAY_H
#define NETWORKGATEWAY_H

#include <QObject>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QUrlQuery>
#include <QVector>

#include "ProgramSettings.h"
/**
    \brief Modified to be only class to hold NetworkManager.
    Creates request for all database activities through REST api.
    retrieves replies and updates software data accordingly
*/
class NetworkGateway : public QObject
{
    Q_OBJECT

public:

    explicit NetworkGateway(QObject *parent = nullptr, int type = 0);
    ~NetworkGateway();

    ///Simple ping handling to see if connection is up
    void sendPingPost();
    QString getPingReply(){return m_pingReply;}

    ///Credentials post creation and reply handling
    void sendCredentialsPost(QVector<QString> crPost);
    QString getCredentialsReply(){return m_credentialsReply;}

    ///Calendar post creation and reply handling
    void sendCalendarPost(QVector<QString> cPost);
    QVector<QString> getCalendarReply(){return m_calendarReply;}
    QString getEventReply() {return m_eventReply;};

    ///Notes post creation and reply handling
    void sendNotePost(QVector<QString> nPost);
    QString getNoteReply() {return m_noteReply;};
    QVector<QPair<QString,QString>> getNoteListReply() {return m_noteListReply;}



public slots:

    ///QNetworkManagers replies slots
    void pingReply(QNetworkReply *pingReply);
    void credentialsReply(QNetworkReply *creReply);
    void calendarReply(QNetworkReply *calReply);
    void noteReply(QNetworkReply * nReply);

signals:

    ///Ping
    void pingOk();

    ///Credentials
    void credentialsOk();
    void credentialsUpdated();

    ///Calendar
    void calendarOk();
    void calendarUpdated();

    ///Notes
    void notesOk();
    void notesListOk();

private:

    ///Credentials
    ///insert data to credentials (mostly register usage).
    const QString m_insertUrl = "http://192.168.1.103:8012/project/Credentials/insert.php";

    ///check credentials during login.
    const QString m_loginUrl = "http://192.168.1.103:8012/project/Credentials/UserLogin.php";

    ///retrieve users email address from database.
    const QString m_getEmailUrl = "http://192.168.1.103:8012/project/Credentials/userGetEmail.php";

    ///retrieve users default location from database.
    const QString m_getLocationUrl = "http://192.168.1.103:8012/project/Credentials/userGetLocation.php";

    ///insert data to credentials (mostly register usage).
    const QString m_deleteUrl = "http://192.168.1.103:8012/project/Credentials/userDelete.php";

    ///updatigng users credentials
    const QString m_updateUrl = "http://192.168.1.103:8012/project/Credentials/userCredentialsChange.php";

    ///Calendar
    ///get all events
    const QString m_getEventsUrl = "http://192.168.1.103:8012/project/Calendar/userEventsGetNew.php";

    ///Add event to database
    const QString m_addEventUrl = "http://192.168.1.103:8012/project/Calendar/userEventsInsert.php";

    ///Get single event by title
    const QString m_getEventByTitleUrl = "http://192.168.1.103:8012/project/Calendar/userEventsGetByTitle.php";

    ///delete event
    const QString m_deleteEventUrl = "http://192.168.1.103:8012/project/Calendar/userEventsDelete.php";

    ///update event
    const QString m_updateEventUrl = "http://192.168.1.103:8012/project/Calendar/userEventsUpdate.php";

    ///Notes
    ///Url used to get all notes from database
    const QString m_getAllNotesUrl = "http://192.168.1.103:8012/project/Notepad/userNotesGet.php";

    ///Saves note in database
    const QString m_saveNoteUrl = "http://192.168.1.103:8012/project/Notepad/userNotesInsert.php";

    ///Deletes note from database
    const QString m_deleteNoteUrl = "http://192.168.1.103:8012/project/Notepad/userNotesDelete.php";

    ///Updates note in database
    const QString m_updateNoteUrl = "http://192.168.1.103:8012/project/Notepad/userNotesUpdate.php";

    ///Common members and methods
    void setUrl(const QString url);
    QNetworkAccessManager *m_manager;
    const int m_type;
    QString m_activeUrl;

    ///ping members
    QString m_pingReply;

    ///credentials members
    QString m_username;
    QString m_credentialsReply;

    ///Calendar members
    QVector<QString> m_calendarReply;
    QString m_eventReply;

    ///Note members
    QString m_noteReply;
    QVector<QPair<QString,QString>> m_noteListReply;
};

#endif // NETWORKGATEWAY_H
