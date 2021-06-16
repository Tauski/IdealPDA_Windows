#include "networkgateway.h"

NetworkGateway::NetworkGateway(QObject *parent, int type)
    : QObject(parent),
      m_manager(new QNetworkAccessManager(this)),
      m_type(type)
{
    if(m_type == 0) ///Credentials
    {
        connect(m_manager,&QNetworkAccessManager::finished,this,&NetworkGateway::credentialsReply);
    }
    else if(m_type == 1) ///Calendar
    {
        connect(m_manager,&QNetworkAccessManager::finished,this,&NetworkGateway::calendarReply);
    }
    else if(m_type == 2) ///Notes
    {
        connect(m_manager,&QNetworkAccessManager::finished,this,&NetworkGateway::noteReply);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::sendCredentialsPost(QVector<QString> post)
{
    qDebug() << "post type :" << post.at(0);

    if(post.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("ERROR: while using credentials post command");
        msgBox.exec();
    }

    QUrlQuery params;
    for(int i = 0; i < post.size(); i++)
    {
        if(post.at(0) == "check")
        {
            setUrl(m_loginUrl);
            params.addQueryItem("f_name", post.at(1));
            params.addQueryItem("password", post.at(2));

            ///hold name to update g_useranem
            m_username = post.at(1);
        }
        else if(post.at(0) == "register")
        {
            setUrl(m_insertUrl);
            params.addQueryItem("f_name", post.at(1));
            params.addQueryItem("email", post.at(2));
            params.addQueryItem("password", post.at(3));
        }
        else if(post.at(0) == "getEmail")
        {
            setUrl(m_getEmailUrl);
            params.addQueryItem("f_name", post.at(1));
        }
        else if(post.at(0) == "getLocation")
        {
            setUrl(m_getLocationUrl);
            params.addQueryItem("f_name", post.at(1));
        }
        else if(post.at(0) == "change")
        {
            setUrl(m_updateUrl);
            params.addQueryItem("old_name", post.at(1));
            params.addQueryItem("new_name", post.at(2));
            params.addQueryItem("old_password", post.at(3));
            params.addQueryItem("new_password", post.at(4));
            params.addQueryItem("old_email", post.at(5));
            params.addQueryItem("new_email", post.at(6));
            params.addQueryItem("old_location", post.at(7));
            params.addQueryItem("new_location", post.at(8));
        }
    }
    QUrl credentialsUrl(m_activeUrl);
    QNetworkRequest request(credentialsUrl);
    m_manager->post(request,params.query().toUtf8());
}


///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::credentialsReply(QNetworkReply *creReply)
{
    QByteArray array = creReply->readAll();
    QString reply = array;
    qDebug() << "Credentials : " << reply;

    if(reply.contains("credentialsID"))
    {
        ///username was good so set request for email and location
        g_username = m_username;
        QVector<QString> email;
        email.push_back("getEmail");
        email.push_back(g_username);
        sendCredentialsPost(email);
    }
    else if(reply.contains("registerID"))
    {
        m_credentialsReply = "register";
        emit credentialsOk();
    }
    else if(reply.contains("emailID"))
    {
        g_userEmail = reply.remove(" emailID");
        QVector<QString> location;
        location.push_back("getLocation");
        location.push_back(g_username);
        sendCredentialsPost(location);
    }
    else if(reply.contains("locationID"))
    {
        g_userLocation = reply.remove(" locationID");
        m_credentialsReply = "login";
        emit credentialsOk();
    }
    else if(reply.contains("updated"))
    {
        m_credentialsReply = "updated";
        emit credentialsUpdated();
    }
    else if(reply.contains("ERROR:"))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("ERROR: while retrieving reply. " + reply);
        msgBox.exec();
    }

    creReply->deleteLater();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::sendCalendarPost(QVector<QString> post)
{
    if(post.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("ERROR: while using calendar post command");
        msgBox.exec();
    }

    QUrlQuery params;
    for(int i = 0; i < post.size(); i++)
    {
        if(post.at(0) == "getAllEvents")
        {
            setUrl(m_getEventsUrl);
            params.addQueryItem("f_name", post.at(1));
            params.addQueryItem("date", post.at(2));
        }
        else if(post.at(0) == "addEvent")
        {
            setUrl(m_addEventUrl);
            params.addQueryItem("fl_name", post.at(1));
            params.addQueryItem("event", post.at(2));
            params.addQueryItem("edate", post.at(3));
            params.addQueryItem("etime", post.at(4));
            params.addQueryItem("elocation", post.at(5));
            params.addQueryItem("edescription", post.at(6));
        }
        else if(post.at(0) == "getEventByTitle")
        {
            setUrl(m_getEventByTitleUrl);
            params.addQueryItem("f_name", post.at(1));
            params.addQueryItem("event", post.at(2));
        }
        else if(post.at(0) == "deleteEvent")
        {
            setUrl(m_deleteEventUrl);
            params.addQueryItem("fl_name", post.at(1));
            params.addQueryItem("oldevent", post.at(2));
        }
        else if(post.at(0) == "updateEvent")
        {            
            setUrl(m_updateEventUrl);
            params.addQueryItem("fl_name", post.at(1));
            params.addQueryItem("event", post.at(2));
            params.addQueryItem("oldevent", post.at(3));
            params.addQueryItem("elocation", post.at(4));
            params.addQueryItem("edescription", post.at(5));
            params.addQueryItem("edate", post.at(6));
            params.addQueryItem("etime", post.at(7));
        }
    }
    QUrl credentialsUrl(m_activeUrl);
    QNetworkRequest request(credentialsUrl);
    m_manager->post(request,params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::calendarReply(QNetworkReply *calReply)
{
    QByteArray array = calReply->readAll();
    QString reply = array;
    QVector<QString> eventArray;
    qDebug() << "Calendar : " << reply;
    if(reply.contains("allEventID"))
    {
        QJsonDocument doc = QJsonDocument::fromJson(array);

        ///Check if empty
        if(!doc.isNull())
        {
            ///IF its object
            if(doc.isObject())
            {
                QJsonObject obj = doc.object();
                qDebug () << "json obj : " << obj;

                ///if object is empty
                if(!obj.isEmpty())
                {
                    QJsonArray jsonArray = obj["data"].toArray();

                    foreach(const QJsonValue & value, jsonArray)
                    {
                        QJsonObject obj = value.toObject();
                        QString event = (obj["event"].toString());
                        if(event != "")
                        {
                            eventArray.push_back(event);
                        }
                    }
                }
                else
                {
                    qDebug () << "Json object is empty :";
                }
            }
            else
            {
                qDebug() << "Json doc is not object";
            }
        }
        else
        {
            qDebug() << "json is empty";
        }
        m_calendarReply = eventArray;
        emit calendarOk();
    }
    else if(reply.contains("Saved"))
    {
        m_eventReply = "Event Saved!";
        emit calendarOk();
    }
    else if(reply.contains("eventID"))
    {
        QVector<QString> eventArray;
        QJsonDocument doc = QJsonDocument::fromJson(array);

        ///Check if empty
        if(!doc.isNull())
        {
            ///IF its object
            if(doc.isObject())
            {
                QJsonObject obj = doc.object();
                qDebug () << "json obj : " << obj;

                ///if object is empty
                if(!obj.isEmpty())
                {
                    QJsonArray jsonArray = obj["data"].toArray();

                    foreach(const QJsonValue & value, jsonArray)
                    {
                        QJsonObject obj = value.toObject();
                        QString event = (obj["event"].toString());
                        QString dateofevent = (obj["dateofevent"].toString());
                        QString timeofevent = (obj["timeofevent"].toString());
                        QString location = (obj["location"].toString());
                        QString description = (obj["description"].toString());

                        if(event != "")
                        {
                            eventArray.push_back(event);
                            eventArray.push_back(dateofevent);
                            eventArray.push_back(timeofevent);
                            eventArray.push_back(location);
                            eventArray.push_back(description);
                        }
                    }
                }
                else
                {
                    qDebug () << "Json object is empty :";
                }
            }
            else
            {
                qDebug() << "Json doc is not object";
            }
        }
        else
        {
            qDebug() << "json is empty";
        }

        m_calendarReply = eventArray;
        emit calendarOk();
    }
    else if(reply.contains("Deleted"))
    {
        m_eventReply = "Event Deleted";
        emit calendarOk();
    }
    else if(reply.contains("Updated"))
    {
        m_eventReply = reply;
        emit calendarUpdated();
    }
    else if(reply.contains("ERROR:"))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("ERROR: while retrieving reply. " + reply);
        msgBox.exec();
    }

    calReply->deleteLater();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::sendNotePost(QVector<QString> nPost)
{

    if(nPost.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("ERROR: while using calendar post command");
        msgBox.exec();
    }

    QUrlQuery params;
    for(int i = 0; i < nPost.size(); i++)
    {
        if(nPost.at(0) == "getAllNotes")
        {
            setUrl(m_getAllNotesUrl);
            params.addQueryItem("f_name", nPost.at(1));
        }
        else if(nPost.at(0) == "saveNote")
        {
            setUrl(m_saveNoteUrl);
            params.addQueryItem("fl_name", nPost.at(1));
            params.addQueryItem("incnote", nPost.at(2));
        }
        else if(nPost.at(0) == "deleteNote")
        {
            setUrl(m_deleteNoteUrl);
            params.addQueryItem("fl_name", nPost.at(1));
            params.addQueryItem("oldnote", nPost.at(2));
        }
        else if(nPost.at(0) == "updateNote")
        {
            setUrl(m_updateNoteUrl);
            params.addQueryItem("fl_name", nPost.at(1));
            params.addQueryItem("incnote", nPost.at(2));
            params.addQueryItem("oldnote", nPost.at(3));
        }
    }
    QUrl credentialsUrl(m_activeUrl);
    QNetworkRequest request(credentialsUrl);
    m_manager->post(request,params.query().toUtf8());
}


///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::noteReply(QNetworkReply *nReply)
{    

    QByteArray replyArray = nReply->readAll();
    QString reply = replyArray;

    qDebug() << "note Reply : " << reply;

    if(reply.contains("Note saved"))
    {
        m_noteReply = "Saved";

        emit notesOk();
    }
    else if(reply.contains("notesID"))
    {
        QJsonDocument doc = QJsonDocument::fromJson(replyArray);

        qDebug() << "whole document : " << doc;

        if(!doc.isNull())
        {
            if(doc.isObject())
            {
                QJsonObject obj = doc.object();
                qDebug () << "json obj : " << obj;

                if(!obj.isEmpty())
                {
                    QJsonArray jsonArray = obj["data"].toArray();

                    foreach (const QJsonValue & value, jsonArray)
                    {
                        QJsonObject obj = value.toObject();
                        QString note = (obj["note"].toString());
                        QString header;
                        //If button has dedicated header set it as text for the button
                        if(note.contains("H:"))
                        {
                            QStringList list = note.split(QRegExp("H:"));
                            header = list.at(0);
                        }
                        //create vector that holds notes and headers
                        if(!header.isEmpty())
                        {
                            QPair<QString,QString> pairHeader;
                            pairHeader.first = header; //this contains header
                            pairHeader.second = note.split(QRegExp("H:")).at(1); //bring only body of the note
                            m_noteListReply.push_back(pairHeader);
                        }
                        qDebug() << "note: " << note;
                    }
                }
                else
                {
                    qDebug () << "Json object is  empty :";
                }
            }
            else
            {
                qDebug () << "Json Document is not Object :";
            }
        }
        emit notesListOk();
    }
    else if(reply.contains("Updated"))
    {
        m_credentialsReply = "Updated";
        emit notesOk();
    }
    else if(reply.contains("Deleted"))
    {
        m_noteReply = "Deleted";
        emit notesOk();
    }
    else if(reply.contains("ERROR:"))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("ERROR: while retrieving reply. " + reply);
        msgBox.exec();
    }

    nReply->deleteLater();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkGateway::setUrl(const QString url)
{
    m_activeUrl = url;
}
