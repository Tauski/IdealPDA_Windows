#ifndef NOTELISTDIALOG_H
#define NOTELISTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QSignalMapper>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QObject>
#include <QVector>
#include <QUrl>
#include <QByteArrayList>




namespace Ui {
class NoteListDialog;
}

/**
    \brief Dynamically scalable list that holds buttons for each note in the
    database. By pressing on note we open new noteDialog with given note
*/
class NoteListDialog : public QDialog
{
    Q_OBJECT

public:

    explicit NoteListDialog(QWidget *parent = nullptr);
    ~NoteListDialog();

public slots:

    ///Sends request to get all notes from database
    void retrieveNotes();

    ///Itarate through all notes and add QPushButtons for each note
    void onRequestFinished(QNetworkReply *nlReply);

    ///Open new noteDialog with saved notes data
    void noteClicked();

private:

    ///NoteListDialog UI object
    Ui::NoteListDialog *ui;

    ///Url used to get all notes from database
    const QString m_getAllNotesUrl = "http://192.168.1.103:8012/project/Notepad/userNotesGet.php";

    ///Vector witch has all notes
    QVector<QString> m_noteVector;

    ///Object of NetworkAccessManager
    QNetworkAccessManager * m_manager;

};

#endif // NOTELISTDIALOG_H
