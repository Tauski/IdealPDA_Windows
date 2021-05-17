#include "notelistdialog.h"
#include "ProgramSettings.h"
#include "ui_notelistdialog.h"
#include "notedialog.h"

NoteListDialog::NoteListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteListDialog),
    m_noteVector(),
    m_manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &NoteListDialog::onRequestFinished);
    retrieveNotes();
}

NoteListDialog::~NoteListDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteListDialog::retrieveNotes()
{
    QUrl getAllNotesUrl(m_getAllNotesUrl);
    QUrlQuery params;
    params.addQueryItem("f_name",g_username); // give key determined on PHP side and string to insert
    QNetworkRequest request(getAllNotesUrl);
    m_manager->post(request, params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

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

                foreach (const QJsonValue & value, jsonArray)
                {
                    QJsonObject obj = value.toObject();
                    QString note = (obj["note"].toString());
                    QPushButton *button = new QPushButton(note,this);

                    //If button has dedicated header set it as text for the button
                    if(note.contains("H:"))
                    {
                        QStringList list = note.split(QRegExp("H:"));
                        button->setText(list.at(0));
                    }

                    //Connect signal for created noteButton and add it to layout
                    connect(button,SIGNAL(clicked()),this,SLOT(noteClicked()));
                    m_noteVector.push_back(note);
                    qDebug() << "note: " << note;
                    ui->gb_layout->addWidget(button);
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

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteListDialog::noteClicked()
{

    //this->hide(); //TODO figure out why this doesn't work
    QString noteConstructorString;

    QPushButton *button = (QPushButton *)sender();
    for(int i = 0; i < m_noteVector.size(); i++)
    {
        //If note contains dedicated header string we need to get whole string for noteDialog
        if(m_noteVector.at(i).contains(button->text()))
        {
            noteConstructorString = m_noteVector.at(i);
        }
        else //We can just send the button text
        {
            noteConstructorString = button->text();
        }
    }

    //create new noteDialog with existing note
    NoteDialog newNote(this, noteConstructorString);
    if(newNote.exec() == QDialog::Accepted)
    {
           qDebug() << "noteDialog accepted from list";

           //this->show(); //TODO figure out why this doesn't work
    }
}
