#ifndef NOTELISTDIALOG_H
#define NOTELISTDIALOG_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMessageBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>

#include "notedialog.h"

namespace Ui {
class NoteListDialog;
}

/**
    \brief Dynamically scalable list that holds buttons for each note in the
    database. By pressing on note button we open new noteDialog with given note

    \todo: perhaps integrate this on notedialog class, for clarity
*/
class NoteListDialog : public QDialog
{
    Q_OBJECT

public:

    explicit NoteListDialog(QWidget *parent = nullptr);
    ~NoteListDialog();

private slots:

    ///Sends request to get all notes from database
    void retrieveNotes();

    ///Itarate through all notes and add QPushButtons for each note
    void onRequestFinished(QNetworkReply *nlReply);

    ///Open new noteDialog with saved notes data
    void noteClicked();

private:

    ///Updates list after closing note dialog
    void updateList();

    ///NoteListDialog UI object
    Ui::NoteListDialog *ui;

    ///Url used to get all notes from database
    const QString m_getAllNotesUrl = "http://192.168.1.103:8012/project/Notepad/userNotesGet.php";

    ///Vector witch has all notes header in first string, body in second
    QVector<QPair<QString,QString>> m_noteVector;

    ///Object of NetworkAccessManager
    QNetworkAccessManager * m_manager;

};

#endif // NOTELISTDIALOG_H
