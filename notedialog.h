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

class NoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteDialog(QWidget *parent = nullptr);
    ~NoteDialog();



private slots:

    void noteSent(QNetworkReply * nReply);

    void on_buttonBox_accepted();

private:
    Ui::NoteDialog *ui;
    const QString m_saveUrl = "http://192.168.1.103:8012/project/Notepad/userNotesInsert.php";

    QNetworkAccessManager* m_manager;
};

#endif // NOTEDIALOG_H
