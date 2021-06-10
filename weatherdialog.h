#ifndef WEATHERDIALOG_H
#define WEATHERDIALOG_H

#include <QDialog>
#include "weatherdatacaller.h"

namespace Ui {
class WeatherDialog;
}


/**
    \brief Dialog
*/
class WeatherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WeatherDialog(QWidget *parent = nullptr);
    ~WeatherDialog();

private slots:

    ///Retrieves newest weather data from solver
    void onWeatherRefresh();

    ///Sets new values for dialogs labels
    void setLabelValues();

    ///Current weather button pressed
    void on_wd_pb_curWeather_clicked();

    ///Shows Forecast
    void on_wd_pb_forecast_clicked();

    void on_wd_pb_change_clicked();

private:

    Ui::WeatherDialog *ui;

    ///WeatherDataCaller instance, retrieves current weather data from open API
    WeatherDataCaller *m_weatherCaller;

    ///String of location we want weather data from
    QString m_location;
};

#endif // WEATHERDIALOG_H
