#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include "networkgateway.h"

namespace Ui {
class NoteDialog;
}

/**
    \brief Shows existing note if given flag to do so.
    Defaults to empty textEdit.
    Sends completed note to database.
*/
class NoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteDialog(QWidget *parent = nullptr, QString savedNote = "");
    ~NoteDialog();

private slots:

    ///Create request for saving selected note
    void on_pb_noteDiagSave_clicked();

    ///Create request for deleting selected note
    void on_pb_noteDiagDelete_clicked();

    ///update existing note (the one that was inserted in constructor)
    void updateNote(QString newHeader, QString newBody);

    ///Slot for managers reply
    void noteSent();

    ///Slot for exit button clicked, Closes the dialog with accepted signal so Notelist or mainwindow can continue.
    void on_pg_noteDiagExit_clicked();

private:

    ///if note was opened from list
    bool m_isOldNote;

    ///Identifier for noteSent() method to know wich request was sent
    unsigned int m_functionSelect;

    ///Ui handle
    Ui::NoteDialog *ui;

    ///Saved note that was used in the constructor
    const QString m_savedNote;

    NetworkGateway m_gateway;
};

#endif // NOTEDIALOG_H
