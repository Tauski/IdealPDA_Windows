#ifndef WEATHERDATACALLER_H
#define WEATHERDATACALLER_H

#include <QNetworkAccessManager>
#include <QXmlStreamReader>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QObject>
#include <QVector>
#include <QUrl>

/**
    \brief Retrieves either current weather data or coming forecast weather
    from given location. Query is constructed to comply with FMI open API
    weather services
*/
class WeatherDataCaller : public QObject
{
    Q_OBJECT

public:

    WeatherDataCaller(QObject *parent = nullptr, int typeID = 0);
    ~WeatherDataCaller();

    ///Create new update request for manager
    void updateRequest();

    ///Return weather data (usually to weatherDialog)
    QVector<QPair<QString,QString>> getWeatherData() const;

signals:

    ///Emitted when manager has requests reply
    void downloaded(QByteArray);

    ///Emitted when class has solved XML result and is ready to use in dialog
    void finished();

private slots:

    ///Recieves reply from manager and reads it. Emits downloaded signal when done.
    void fileDownloaded(QNetworkReply* pReply);

private:

    ///Solves replies xml to vectors and strings
    void solveData(QByteArray resultArray);

    ///Searches highest values of weather data from multiple stations
    void findHighest(QVector<QPair<QString,QString>> *compVector);

    ///Parses current time from platform into query friendly type
    QVector<QString> getTimes();

    ///Holds highest values of current weather data
    QVector<QPair<QString,QString>> m_highestVector;

    ///Manager instance
    QNetworkAccessManager *m_webCtrl;

    ///Holds non modified reply from manager
    QByteArray m_downloadedData;

    ///Type of wichh request we wanted 0 = weather, 1 = forecast
    const int m_typeID;

};

#endif // WEATHERDATACALLER_H
