#include "notelistdialog.h"
#include "ProgramSettings.h"
#include "ui_notelistdialog.h"

NoteListDialog::NoteListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteListDialog),
    m_manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    connect(m_manager, &QNetworkAccessManager::finished, this, &NoteListDialog::onRequestFinished);
    populateList();
}

NoteListDialog::~NoteListDialog()
{
    delete ui;
}


void NoteListDialog::populateList()
{
    QUrl getAllNotesUrl(m_getAllNotesUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",g_username);
    QNetworkRequest request(getAllNotesUrl);
    m_manager->post(request, params.query().toUtf8());
}

void NoteListDialog::onRequestFinished(QNetworkReply *nlReply)
{
    QJsonDocument doc = QJsonDocument::fromJson(nlReply->readAll());
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

                foreach (const QJsonValue & value, jsonArray) {
                    QJsonObject obj = value.toObject();

                    QString note = (obj["note"].toString());

                    qDebug () << "note :" << note;
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



    //qDebug() << nlArray;
    nlReply->deleteLater();
}
