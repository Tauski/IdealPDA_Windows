#include "weatherdatacaller.h"

WeatherDataCaller::WeatherDataCaller(QObject *parent, int typeID)
    : QObject(parent),
      m_typeID(typeID)
{
    //Manager ---------------------------------------------------------------------------------------------------------
    m_webCtrl = new QNetworkAccessManager();
    connect(m_webCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));

    //Request ---------------------------------------------------------------------------------------------------------
    QString urlStartTime;
    QString urlEndTime;

    if(!getTimes().isEmpty())
    {
        QVector<QString> times = getTimes();
        urlStartTime = times.at(0);
        urlEndTime = times.at(1);
    }
    else
    {
        qCritical() << "Error! couldn't retrieve current time";
    }

    qDebug()<<"got time";

    if(m_typeID == 0) ///we wanted current weather data
    {
        QUrl weatherUrl("http://opendata.fmi.fi/wfs/fin");
        weatherUrl.setQuery("?service=WFS&version=2.0.0&request=GetFeature&storedquery_id=fmi::observations::weather::simple&fmisid=101799&fmisid=101794&fmisid=101786&parameters=ws,temperature,pressure&starttime=" + urlStartTime + "&endtime=" + urlEndTime + "&timestep=1&");
        QNetworkRequest request(weatherUrl);
        qDebug()<<"created requeset with url:" << weatherUrl;
        m_webCtrl->get(request);
        qDebug()<<"get Request";
    }
    else /// we wanted weather forecast
    {
        QUrl weatherUrl("http://opendata.fmi.fi/wfs");
        weatherUrl.setQuery("?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::forecast::hirlam::surface::point::multipointcoverage&place=otanmäki&");
        QNetworkRequest request(weatherUrl);
        qDebug()<<"created requeset with url:" << weatherUrl;
        m_webCtrl->get(request);
        qDebug()<<"get Request";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WeatherDataCaller::~WeatherDataCaller()
{
    qDebug()<<"wdc destructor";
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDataCaller::fileDownloaded(QNetworkReply* pReply)
{
    qDebug()<<"got to downloaded";
    m_downloadedData = pReply->readAll();
    pReply->deleteLater();
    m_webCtrl->deleteLater();

    emit downloaded(m_downloadedData);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QVector<QString> WeatherDataCaller::getTimes()
{
    QVector<QString> returnVector;

    QDateTime dateTime;

    //Get datetime in ISO format that the url also uses,
    //StartTime and endTime can be the same in the url, this will only give one set of parameters regardless of the timestep.
    QString startTime = dateTime.currentDateTimeUtc().toString(Qt::ISODate);
    QString endTime = dateTime.currentDateTimeUtc().toString(Qt::ISODate);

    //check if min is divisible by 10, becouse url can only target 10 min intervals
    int min = dateTime.currentDateTimeUtc().time().minute();
    if(min % 10 == 0)
    {
        //current time is mostly usable, replace seconds, becouse if not 00 and using the same startTime/endtime calling the feature doesn't seem to work
        startTime.replace(17,2,QString::number(0));
        returnVector.push_back(startTime);

    }else
    {
        if(min < 10)
        {
            startTime.replace(17,2,QString::number(0));
            startTime.replace(14,2,QString::number(0));
        }
        else if(min > 10 && min < 20)
        {
            startTime.replace(17,2,QString::number(0));
            startTime.replace(14,2,QString::number(10));
        }
        else if(min > 20 && min < 30)
        {
            startTime.replace(17,2,QString::number(0));
            startTime.replace(14,2,QString::number(20));
        }
        else if(min > 30 && min < 40)
        {
            startTime.replace(17,2,QString::number(0));
            startTime.replace(14,2,QString::number(30));
        }
        else if(min > 40 && min < 50)
        {
            startTime.replace(17,2,QString::number(0));
            startTime.replace(14,2,QString::number(40));
        }
        else
        {
            startTime.replace(17,2,QString::number(0));
            startTime.replace(14,2,QString::number(50));
        }

        returnVector.push_back(startTime);
    }

    endTime = startTime;
    returnVector.push_back(endTime);

    return returnVector;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///Previous solver side
void WeatherDataCaller::solveData(QByteArray resultArray)
{
    //non pointer approach
    QXmlStreamReader m_XMLreader(resultArray);

    //container for xml numerical values
    QVector<QString> xmlVector;
    //container for all values with corresponding station
    QVector<QPair<QString,QString>> allValues;

    //Searching for tokens that give name and value from whole file
    while(!m_XMLreader.atEnd() && !m_XMLreader.hasError())
    {
        QXmlStreamReader::TokenType token = m_XMLreader.readNext();

        //If token is startDocument go to next
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement)
        {
            //Elements with ParameterValue holds the numerical data
            if(m_XMLreader.name() == "ParameterValue")
            {
                xmlVector.push_back(m_XMLreader.readElementText());
            }
            else if(m_XMLreader.name() == "doubleOrNilReasonTupleList")
            {
                xmlVector.push_back(m_XMLreader.readElementText());
            }
        }
    }
    if(m_XMLreader.hasError())
    {
        qCritical() << "Error while parsing XML has occurred" << m_XMLreader.errorString();
        return;
    }
    else
    {
        qDebug() << "this is the size ";
/*
        //handle data from different stations
        if(!xmlVector.empty())
        {
            //iterate every other element to only include numeric values
            QPair<QString, QString> station_valuePair;
            for(int i = 0; i < xmlVector.size(); i++)
            {
                    if(i < 3)
                    {
                        station_valuePair.first = "Oulu Oulunsalo Station";
                        station_valuePair.second = xmlVector.at(i);
                        allValues.push_back(station_valuePair);
                    }
                    else if(i > 2 && i < 6)
                    {
                        station_valuePair.first = "Oulu Vihreäsaari Station";
                        station_valuePair.second = xmlVector.at(i);
                        allValues.push_back(station_valuePair);
                    }
                    else{
                        station_valuePair.first = "Oulu airport Station";
                        station_valuePair.second = xmlVector.at(i);
                        allValues.push_back(station_valuePair);
                    }
            }
        }
        else
        {
            qCritical() << "Error! Parsed XML data vector was empty!";
        }
*/
    }

    qDebug()<<"this is all values: "<< allValues;
    findHighest(&allValues);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WeatherDataCaller::findHighest(QVector<QPair<QString, QString>> *compVector)
{
    QVector<double> wsVec = {0};
    QString wsStation = "";
    QVector<double> tempVec = {0};
    QString tempStation = "";
    QVector<double> apVec = {0};
    QString apStation = "";

    //Check number of stations that has data
    int size = compVector->size();

    //highest ws
    for(int i = 0; i < compVector->size(); i += 3)
    {
        wsVec.push_back(compVector->at(i).second.toDouble());
    }

    double max_ws = *std::max_element(wsVec.begin(),wsVec.end());

    for(int i = 0; i < compVector->size(); i += 3)
    {
        if(compVector->at(i).second.toDouble() == max_ws)
        {
            wsStation = compVector->at(i).first;
        }
    }

    //highest temp
    for(int i = 1; i < compVector->size(); i += 3)
    {
        tempVec.push_back(compVector->at(i).second.toDouble());
    }

    double max_temp = *std::max_element(tempVec.begin(),tempVec.end());

    for(int i = 1; i < compVector->size(); i += 3)
    {
        if(compVector->at(i).second.toDouble() == max_temp)
        {
            tempStation = compVector->at(i).first;
        }
    }

    //highest airpressure
    for(int i = 2; i < compVector->size(); i += 3)
    {
        apVec.push_back(compVector->at(i).second.toDouble());
    }

    double max_ap = *std::max_element(apVec.begin(),apVec.end());

    for(int i = 2; i < compVector->size(); i += 3)
    {
        if(compVector->at(i).second.toDouble() == max_ap)
        {
            apStation = compVector->at(i).first;
        }
    }

    m_highestVector.push_back(QPair<QString,QString>(wsStation,QString::number(max_ws)));
    m_highestVector.push_back(QPair<QString,QString>(tempStation,QString::number(max_temp)));
    m_highestVector.push_back(QPair<QString,QString>(apStation,QString::number(max_ap)));
    m_highestVector.push_back(QPair<QString,QString>(QString::number(size/3),QString::number(size/3)));
    emit finished();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QVector<QPair<QString,QString>> WeatherDataCaller::getWeatherData() const
{
    return m_highestVector;
}
