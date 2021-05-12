#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include <QDialog>

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QByteArray>
#include <QObject>
#include <QVector>
#include <QUrl>

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
    explicit NoteDialog(QWidget *parent = nullptr);
    ~NoteDialog();

private slots:

    ///Slot for managers reply
    void noteSent(QNetworkReply * nReply);

    void on_pb_noteDiagSave_clicked();

    void on_pb_noteDiagDelete_clicked();

private:
    Ui::NoteDialog *ui;

    ///Specific url for saving user given notes.
    const QString m_saveUrl = "http://192.168.1.103:8012/project/Notepad/userNotesInsert.php";

    const QString m_deleteUrl = "http://192.168.1.103:8012/project/Notepad/userNotesDelete.php";

    ///object of manager
    QNetworkAccessManager* m_manager;
};

#endif // NOTEDIALOG_H