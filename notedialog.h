#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QVector>

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
    void noteSent(QNetworkReply * nReply);

    void on_pg_noteDiagExit_clicked();

private:

    ///if note was opened from list
    bool m_isOldNote;

    ///Identifier for noteSent() method to know wich request was sent
    unsigned int m_functionSelect;

    ///Ui handle
    Ui::NoteDialog *ui;

    ///Specific url for saving user given notes.
    const QString m_saveUrl = "http://192.168.1.103:8012/project/Notepad/userNotesInsert.php";
    const QString m_deleteUrl = "http://192.168.1.103:8012/project/Notepad/userNotesDelete.php";
    const QString m_updateUrl = "http://192.168.1.103:8012/project/Notepad/userNotesUpdate.php";

    ///Saved note that was used in constructor
    const QString m_savedNote;

    ///object of manager
    QNetworkAccessManager* m_manager;
};

#endif // NOTEDIALOG_H
