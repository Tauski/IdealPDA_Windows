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

    WeatherDataCaller(QObject *parent = nullptr, int typeID = 0, QString location = "");
    ~WeatherDataCaller();

    ///Create new update request for manager
    void updateRequest(QString newRequest);

    ///Return weather data (usually to weatherDialog)
    QVector<QPair<QString,QString>> getWeatherData() const;

    ///Return forecast data (usually to weatherDialog)
    QVector<QPair<QString,QVector<QString>>> getWeatherForecast() const;

    ///Sets new location for current weather and forecast calls
    void setNewLocation(QString newLocation);

signals:

    ///Emitted when manager has requests reply
    void downloaded(QByteArray);

    ///Emitted when class has solved XML result for current weather
    void weatherFinished();

    ///Emitted when class has solver XML result for forecast
    void forecastFinished();

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

    ///Holds 36h forecast for chosen location
    QVector<QPair<QString,QVector<QString>>> m_forecastVector;

    ///Manager instance
    QNetworkAccessManager *m_webCtrl;

    ///Holds non modified reply from manager
    QByteArray m_downloadedData;

    ///Type of wichh request we wanted 0 = weather, 1 = forecast
    const int m_typeID;

    ///Location to search weather data from
    const QString m_location;

};

#endif // WEATHERDATACALLER_H
