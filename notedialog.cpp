#include "notedialog.h"
#include "ui_notedialog.h"
#include "ProgramSettings.h"

NoteDialog::NoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteDialog),
    m_manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(m_manager, &QNetworkAccessManager::finished,this, &NoteDialog::noteSent);
}

NoteDialog::~NoteDialog()
{
    delete ui;
    delete m_manager;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::noteSent(QNetworkReply *nReply)
{
    QByteArray noteArray = nReply->readAll();

    nReply->deleteLater();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::on_pb_noteDiagSave_clicked()
{
    QString header = ui->le_noteHeader->text();
    QString noteBody = ui->te_noteBody->toPlainText() + " : ";
    QString compinedHeaderBody = header + noteBody;
    //might not get activated as accepted signal is send before.
    QUrl saveNoteUrl(m_saveUrl);
    QUrlQuery params;
    params.addQueryItem("fl_name", g_username);
    params.addQueryItem("incnote",compinedHeaderBody);
    QNetworkRequest request(saveNoteUrl);
    m_manager->post(request, params.query().toUtf8());
    //this->Accepted;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::on_pb_noteDiagDelete_clicked()
{
    //might not get activated as accepted signal is send before.
    QUrl saveNoteUrl(m_deleteUrl);
    QUrlQuery params;
    params.addQueryItem("fl_name", g_username);
    params.addQueryItem("oldnote","");

    QNetworkRequest request(saveNoteUrl);
    m_manager->post(request, params.query().toUtf8());
    //this->Accepted;
}
