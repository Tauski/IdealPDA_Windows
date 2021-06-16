#include "notelistdialog.h"
#include "ProgramSettings.h"
#include "ui_notelistdialog.h"

NoteListDialog::NoteListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteListDialog),
    m_noteVector(),
    m_gateway(this,2)
{
    ui->setupUi(this);
    connect(&m_gateway, &NetworkGateway::notesListOk, this, &NoteListDialog::onRequestFinished);

    retrieveNotes();
}

NoteListDialog::~NoteListDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteListDialog::retrieveNotes()
{
    QVector<QString> params;
    params.push_back("getAllNotes");
    params.push_back(g_username);
    m_gateway.sendNotePost(params);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteListDialog::onRequestFinished()
{
    ///if no work try change this to fwd
    m_noteVector = m_gateway.getNoteListReply();

    for(int i = 0; i < m_noteVector.size(); i++)
    {
        QPushButton *button = new QPushButton(m_noteVector.at(i).first,this);
        connect(button, SIGNAL(clicked()),this,SLOT(noteClicked()));

        ui->gb_layout->addWidget(button);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteListDialog::noteClicked()
{

    //this->hide(); //TODO figure out why this doesn't work
    QString noteConstructorString;

    QPushButton *button = (QPushButton *)sender();

    qDebug() << button->text() << " was note header";
    for(int i = 0; i < m_noteVector.size(); i++)
    {
        //If note contains dedicated header string we need to get whole string for noteDialog
        if(m_noteVector.at(i).first != "")
        {
            noteConstructorString = m_noteVector.at(i).first + "H:" + m_noteVector.at(i).second;
        }
        else //We can just send the button text
        {
            noteConstructorString = button->text();
        }
    }

    //create new noteDialog with existing note
    qDebug() << "note constructor string = " << noteConstructorString;

    NoteDialog newNote(this, noteConstructorString);
    if(newNote.exec() == QDialog::Accepted)
    {
           qDebug() << "noteDialog accepted from list";
           this->accept();
           //this->show(); //TODO figure out why this doesn't work
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void NoteListDialog::updateList()
{
    ///TODO:
}
