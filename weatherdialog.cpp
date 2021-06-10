#include "weatherdialog.h"
#include "ui_weatherdialog.h"

WeatherDialog::WeatherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeatherDialog),
    m_location("")
{
    ui->setupUi(this);

    ///set placeholders for labels
    ui->wd_label_temperature->setText("0°C");
    ui->wd_label_weather->setText("fair weather");
    ui->wd_label_wind->setText("0/ms");
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
    m_weatherCaller = new WeatherDataCaller(nullptr,0);
    connect(m_weatherCaller, SIGNAL(finished()), this, SLOT(setLabelValues()));
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
        qWarning() << "Warning! No weather data";
    }

    //Manual delete for solver
    //delete m_weatherSolver;
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
    m_weatherCaller = new WeatherDataCaller(nullptr,1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDialog::on_wd_pb_change_clicked()
{
    if(!ui->wd_le_newLocation->text().isEmpty())
    {
        m_location = ui->wd_le_newLocation->text();
    }
}
