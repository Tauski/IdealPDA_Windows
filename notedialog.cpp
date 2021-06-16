#include "notedialog.h"
#include "ui_notedialog.h"
#include "ProgramSettings.h"


NoteDialog::NoteDialog(QWidget *parent, QString savedNote):
    QDialog(parent),
    m_isOldNote(false),
    m_functionSelect(0),
    ui(new Ui::NoteDialog),
    m_savedNote(savedNote),
    m_gateway(this,2)
{
    ui->setupUi(this);

    ///if we are not a new note get saved note and split it for header and body
    if(m_savedNote != "")
    {
        if(m_savedNote.contains("H:"))
        {
            QStringList list = m_savedNote.split(QRegExp("H:"));
            qDebug() << "saved note from notedialog: " << list.at(0) << list.at(1);
            ui->le_noteHeader->setText(list.at(0));
            ui->te_noteBody->setText(list.at(1));
        }
        else
        {
            ui->te_noteBody->setText(m_savedNote);
        }
        m_isOldNote = true;
    }
    else
    {
        ui->pb_noteDiagDelete->hide();
    }
    connect(&m_gateway, &NetworkGateway::notesOk,this, &NoteDialog::noteSent);
}

NoteDialog::~NoteDialog()
{
    delete ui;
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
        QVector<QString> params;
        params.push_back("saveNote");
        params.push_back(g_username);
        params.push_back(compinedHeaderBody);
        m_gateway.sendNotePost(params);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::on_pb_noteDiagDelete_clicked()
{
    m_functionSelect = 2;

    QVector<QString> params;
    params.push_back("deleteNote");
    params.push_back(g_username);
    params.push_back(m_savedNote);
    m_gateway.sendNotePost(params);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::updateNote(QString newHeader, QString newBody)
{
    m_functionSelect = 3;

    ///compine header and body for sending
    QString compinedHeaderBody = newHeader + "H:" + newBody;

    QVector<QString> params;
    params.push_back("updateNote");
    params.push_back(g_username);
    params.push_back(compinedHeaderBody);
    params.push_back(m_savedNote);
    m_gateway.sendNotePost(params);

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::noteSent()
{
    QString reply = m_gateway.getNoteReply();
    this->accept();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteDialog::on_pg_noteDiagExit_clicked()
{
    this->accept();
}
