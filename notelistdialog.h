#ifndef NOTELISTDIALOG_H
#define NOTELISTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QNetworkAccessManager>
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

class NoteListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteListDialog(QWidget *parent = nullptr);
    ~NoteListDialog();

    void populateList();

public slots:

    void onRequestFinished(QNetworkReply *nlReply);

private:
    Ui::NoteListDialog *ui;

    const QString m_getAllNotesUrl = "http://192.168.1.103:8012/project/Notepad/userNotesGet.php";
    const QString m_getOneNoteUrl = "http://192.168.1.103:8012/project/Notepad/userNotesUpdate.php";

    QNetworkAccessManager * m_manager;

};

#endif // NOTELISTDIALOG_H
