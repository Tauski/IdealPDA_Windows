#ifndef WEATHERDIALOG_H
#define WEATHERDIALOG_H

#include <QMessageBox>
#include <QDialog>
#include "weatherdatacaller.h"
#include "ProgramSettings.h"

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

    ///Sets new values for forecast labels
    void setForecastValues();

    ///Current weather button pressed
    void on_wd_pb_curWeather_clicked();

    ///Shows Forecast
    void on_wd_pb_forecast_clicked();

    ///Shows previous hour on forecast
    void on_wd_pb_forecast_previoushour_clicked();

    ///Shows next hour in forecast
    void on_wd_pb_forecast_nexthour_clicked();

    ///Returns to current weather page
    void on_wd_pb_forecast_back_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:

    Ui::WeatherDialog *ui;

    ///WeatherDataCaller instance, retrieves current weather data from open API
    WeatherDataCaller *m_weatherCaller;

    ///Forecast can hold up to 36 hours of data this keeps hold of current hour
    int m_forecastHour;

    ///String of location we want weather data from
    QString m_location;
};

#endif // WEATHERDIALOG_H
