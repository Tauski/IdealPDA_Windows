#include "weatherdialog.h"
#include "ui_weatherdialog.h"

WeatherDialog::WeatherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeatherDialog),
    m_forecastHour(0),
    m_location("")
{
    ui->setupUi(this);

    ///set placeholders for labels
    ui->wd_label_temperature->setText("0°C");
    ui->wd_label_weather->setText("fair weather");
    ui->wd_label_wind->setText("0/ms");

    ///start with page 1
    ui->stackedwidget_wd->setCurrentIndex(0);

    ///disable previous forecast from start
    ui->wd_pb_forecast_previoushour->setDisabled(true);

    ///default location if not placeholder
    if(g_userLocation != "locationPlaceHolder")
    {
        m_location = g_userLocation;
        ui->wd_label_p1header->setText(g_userLocation);
    }
    onWeatherRefresh();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

WeatherDialog::~WeatherDialog()
{
    delete ui;
    delete m_weatherCaller;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::onWeatherRefresh()
{
    ///Update weather
    if(ui->wd_le_newLocation->text().isEmpty() && g_userLocation == "locationPlaceHolder")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You don't have default location selected, so please type wanted location on field below");
        msgBox.exec();
    }
    else /// we have some location
    {
        ///if we have empty location lineedit
        if(g_userLocation != "locationPlaceHolder" && ui->wd_le_newLocation->text().isEmpty())
        {
            m_weatherCaller = new WeatherDataCaller(nullptr,0,g_userLocation);
        }
        else if(g_userLocation != "locationPlaceHolder")/// line edit has data
        {
            m_weatherCaller = new WeatherDataCaller(nullptr,0,ui->wd_le_newLocation->text());
        }
        connect(m_weatherCaller, SIGNAL(weatherFinished()), this, SLOT(setLabelValues()));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::setLabelValues()
{

    QVector<QPair<QString,QString>> weatherVector = m_weatherCaller->getWeatherData();
    qDebug()<<"setting values";

    if(!m_weatherCaller->getWeatherData().empty())
    {
        ui->wd_label_wind->setText(weatherVector.at(0).second + " m/s : " + weatherVector.at(0).first);
        ui->wd_label_temperature->setText(weatherVector.at(1).second + " °C : " + weatherVector.at(1).first);
        ui->wd_label_weather->setText(weatherVector.at(2).second + " hPa : " + weatherVector.at(2).first);
        ui->wd_label_station->setText("Stations that provide fresh data: " + weatherVector.back().second+ "/3");
    }
    else
    {
        qWarning() << "Warning! No weather data!";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::setForecastValues()
{
    //Get forecast data from caller and insert it into local vector
    QVector<QPair<QString,QVector<QString>>> forecastVector = m_weatherCaller->getWeatherForecast();

    QString weatherType = "";
    switch (forecastVector.at(m_forecastHour).second.at(6).split(".").first().toInt())
    {

    case 1:
        weatherType = "Clear";
    break;

    case 2:
        weatherType = "Partly cloudy";
    break;

    case 3:
        weatherType = "Cloudy";
    break;

    case 21:
        weatherType = "Periodical rain showers";
    break;

    case 22:
        weatherType = "Rain showers";
    break;

    case 23:
        weatherType = "Intense rain showers";
    break;

    case 31:
        weatherType = "Faint rain";
    break;

    case 32:
        weatherType = "Rain";
    break;

    case 33:
        weatherType = "Intense rain";
    break;

    case 41:
        weatherType = "Periodical snow showers";
    break;

    case 42:
        weatherType = "snow showers";
    break;

    case 43:
        weatherType = "Intense snow showers";
    break;

    case 51:
        weatherType = "Fain snowfall";
    break;

    case 52:
        weatherType = "Snowfall";
    break;

    case 53:
        weatherType = "Intense snowfall";
    break;

    case 61:
        weatherType = "Thunder showers";
    break;

    case 62:
        weatherType = "Intense thunder showers";
    break;

    case 63:
        weatherType = "Thunder";
    break;

    case 64:
        weatherType = "Intense thundering";
    break;

    case 71:
        weatherType = "Faint sleet showers";
    break;

    case 72:
        weatherType = "Sleet showers";
    break;

    case 73:
        weatherType = "Intense sleet showers";
    break;

    case 81:
        weatherType = "Faint sleeting";
    break;

    case 82:
        weatherType = "Sleeting";
    break;

    case 83:
        weatherType = "Intense sleeting";
    break;

    case 91:
        weatherType = "Haze";
    break;

    case 92:
        weatherType = "Fog";
    break;

    }

    //update UI

    QString locationString;
    if(ui->wd_le_newLocation->text().isEmpty())
    {
        locationString = g_userLocation;
    }
    else
    {
        locationString = ui->wd_le_newLocation->text();
    }

    if(!forecastVector.isEmpty())
    {
        QDateTime curTime;
        curTime.setSecsSinceEpoch(forecastVector.at(m_forecastHour).first.toLongLong());
        ui->wd_label_p2header->setText(curTime.toString() + " " + locationString);
        ui->wd_label_forecast_temperature->setText("Temperature C°:   " + forecastVector.at(m_forecastHour).second.at(0));
        ui->wd_label_forecast_weather->setText("Weather type:   " + weatherType);
        ui->wd_label_forecast_windspeed->setText("Windspeed m/s:   " +forecastVector.at(m_forecastHour).second.at(4));
        ui->wd_label_forecast_winddirection->setText("Wind Direction 360°:   " +forecastVector.at(m_forecastHour).second.at(3));
        ui->wd_label_forecast_gust->setText("Wind gusts at m/s:   " +forecastVector.at(m_forecastHour).second.at(5));
        ui->wd_label_forecast_humidity->setText("Humidity %   " +forecastVector.at(m_forecastHour).second.at(2));
        ui->wd_label_forecast_airpressure->setText("Airpressure hPa:   " +forecastVector.at(m_forecastHour).second.at(1));

        m_forecastHour == 0 ? ui->wd_pb_forecast_previoushour->setDisabled(true) : ui->wd_pb_forecast_previoushour->setEnabled(true);
        m_forecastHour == 35 ? ui->wd_pb_forecast_nexthour->setDisabled(true) : ui->wd_pb_forecast_nexthour->setEnabled(true);
    }
    else
    {
        qWarning() << "Warning! No forecast data!";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::on_wd_pb_curWeather_clicked()
{
    onWeatherRefresh();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Shows hourly forecast
void WeatherDialog::on_wd_pb_forecast_clicked()
{
    if(ui->wd_le_newLocation->text().isEmpty() && g_userLocation == "locationPlaceHolder")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("You don't have default location selected, so please type wanted location on field below");
        msgBox.exec();
    }
    else /// we have some location
    {
        ///change to page 2
        ui->stackedwidget_wd->setCurrentIndex(1);

        ///if we have empty location lineedit
        if(g_userLocation != "locationPlaceHolder" && ui->wd_le_newLocation->text().isEmpty())
        {
            m_weatherCaller = new WeatherDataCaller(nullptr,1,g_userLocation);
        }
        else if(g_userLocation != "locationPlaceHolder")/// line edit has data
        {           
            m_weatherCaller = new WeatherDataCaller(nullptr,1,ui->wd_le_newLocation->text());
        }

        connect(m_weatherCaller, SIGNAL(forecastFinished()), this, SLOT(setForecastValues()));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::on_wd_pb_forecast_previoushour_clicked()
{
    //If next button is not enabled when we press previous hour we enable this
    if(!ui->wd_pb_forecast_nexthour->isEnabled())
    {
        ui->wd_pb_forecast_nexthour->setEnabled(true);
    }

    //remove from hours and reset UI
    m_forecastHour -= 1;
    setForecastValues();

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::on_wd_pb_forecast_nexthour_clicked()
{
    //If previous button is not enabled when we press next hour we enable this
    if(!ui->wd_pb_forecast_previoushour->isEnabled())
    {
        ui->wd_pb_forecast_previoushour->setEnabled(true);
    }

    //add to hours and reset UI
    m_forecastHour += 1;
    setForecastValues();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::on_wd_pb_forecast_back_clicked()
{
    ui->stackedwidget_wd->setCurrentIndex(0);
}
