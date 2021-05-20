#include "notedialog.h"
#include "ui_notedialog.h"
#include "ProgramSettings.h"


NoteDialog::NoteDialog(QWidget *parent, QString savedNote):
    QDialog(parent),
    m_isOldNote(false),
    m_functionSelect(0),
    ui(new Ui::NoteDialog),
    m_savedNote(savedNote),
    m_manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    //if we are not a new noteDialog get saved note and split it for header and body
    if(m_savedNote != "")
    {
        if(m_savedNote.contains("H:"))
        {
            QStringList list = m_savedNote.split(QRegExp("H:"));
            qDebug() << m_savedNote;
            ui->le_noteHeader->setText(list.at(0));
            ui->te_noteBody->setText(list.at(1));
        }
        else
        {
            ui->te_noteBody->setText(m_savedNote);
        }
        m_isOldNote = true;
    }
    else //we are new note so hide delete button
    {
        ui->pb_noteDiagDelete->hide();
    }
    connect(m_manager, &QNetworkAccessManager::finished,this, &NoteDialog::noteSent);
}

NoteDialog::~NoteDialog()
{
    delete ui;
    delete m_manager;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::on_pb_noteDiagSave_clicked()
{
    m_functionSelect = 1;

    QString noteBody = ui->te_noteBody->toPlainText();
    QString header = ui->le_noteHeader->text();

    if(noteBody.isEmpty() || header.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You can't save note with empty header or body");
        msgBox.exec();
    }

    if(m_isOldNote == true)
    {
        updateNote(ui->le_noteHeader->text(),ui->te_noteBody->toPlainText());
    }
    else
    {
        QString compinedHeaderBody = header + "H:" + noteBody;
        //send to rest api
        QUrl saveNoteUrl(m_saveUrl);
        QUrlQuery params;
        params.addQueryItem("fl_name", g_username);
        params.addQueryItem("incnote",compinedHeaderBody);
        QNetworkRequest request(saveNoteUrl);
        m_manager->post(request, params.query().toUtf8());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::on_pb_noteDiagDelete_clicked()
{
    m_functionSelect = 2;

    //might not get activated as accepted signal is send before.
    QUrl saveNoteUrl(m_deleteUrl);
    QUrlQuery params;
    params.addQueryItem("fl_name", g_username);
    params.addQueryItem("oldnote", m_savedNote);

    QNetworkRequest request(saveNoteUrl);
    m_manager->post(request, params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::updateNote(QString newHeader, QString newBody)
{
    m_functionSelect = 3;

    //compine header and body for sending
    QString compinedHeaderBody = newHeader + "H:" + newBody;

    QUrl saveNoteUrl(m_updateUrl);
    QUrlQuery params;
    params.addQueryItem("fl_name", g_username); // give key determined on PHP side and string to insert
    params.addQueryItem("incnote", compinedHeaderBody);
    params.addQueryItem("oldnote", m_savedNote);

    //create request and set manager to send it with rule according to your php file
    QNetworkRequest request(saveNoteUrl);
    m_manager->post(request, params.query().toUtf8());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::noteSent(QNetworkReply *nReply)
{

    QByteArray noteArray = nReply->readAll();
    nReply->deleteLater();

    ///todo: handle all error possibilities using using noteArray that holds echo from php api
    this->accept(); //send accepted signal when regardless of reply type
}

void NoteDialog::on_pg_noteDiagExit_clicked()
{
    this->accept();
}
