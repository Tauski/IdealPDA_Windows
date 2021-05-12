#include "notedialog.h"
#include "ui_notedialog.h"

NoteDialog::NoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteDialog)
{
    ui->setupUi(this);
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished,this, &NoteDialog::noteSent);
}

NoteDialog::~NoteDialog()
{
    delete ui;
    delete m_manager;
}

void NoteDialog::noteSent(QNetworkReply *nReply)
{
    QByteArray noteArray = nReply->readAll();

    nReply->deleteLater();
}

void NoteDialog::on_buttonBox_accepted()
{
    //might not get activated as accepted signal is send before.
    QUrl saveNoteUrl(m_saveUrl);
    QUrlQuery params;
    params.addQueryItem("fl_name", "niko");
    params.addQueryItem("incnote",ui->textEdit->toPlainText());
    QNetworkRequest request(saveNoteUrl);
    m_manager->post(request, params.query().toUtf8());
    this->Accepted;
}
