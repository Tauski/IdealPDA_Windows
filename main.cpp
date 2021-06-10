#include "mainwindow.h"
#include "logindialog.h"

/**

        /// all included data
        /// GeopHeight                        0     exlucde
        /// Temperature                       1     include
        /// Pressure                          2     include
        /// Humidity                          3     include
        /// WindDirection                     4     include
        /// WindSpeedMS                       5     include
        /// WindUMS                           6     exclude
        /// WindVMS                           7     exclude
        /// MaximumWind                       8     exclude
        /// WindGust                          9     include
        /// DewPoint                          10    exclude
        /// TotalCloudCover                   11    exclude
        /// WeatherSymbol3                    12    include, gives symbol of what weather it should be in common languege

        /// 1 selkeää
        /// 2 puolipilvistä
        /// 21 heikkoja sadekuuroja
        /// 22 sadekuuroja
        /// 23 voimakkaita sadekuuroja
        /// 3 pilvistä
        /// 31 heikkoa vesisadetta
        /// 32 vesisadetta
        /// 33 voimakasta vesisadetta
        /// 41 heikkoja lumikuuroja
        /// 42 lumikuuroja
        /// 43 voimakkaita lumikuuroja
        /// 51 heikkoa lumisadetta
        /// 52 lumisadetta
        /// 53 voimakasta lumisadetta
        /// 61 ukkoskuuroja
        /// 62 voimakkaita ukkoskuuroja
        /// 63 ukkosta
        /// 64 voimakasta ukkosta
        /// 71 heikkoja räntäkuuroja
        /// 72 räntäkuuroja
        /// 73 voimakkaita räntäkuuroja
        /// 81 heikkoa räntäsadetta
        /// 82 räntäsadetta
        /// 83 voimakasta räntäsadetta
        /// 91 utua
        /// 92 sumua

        /// LowCloudCover                     13    exclude
        /// MediumCloudCover                  14    exclude
        /// HighCloudCover                    15    exclude
        /// Precipitation1h                   16    exclude
        /// PrecipitationAmount               17    exclude
        /// RadiationGlobalAccumulation       18    exclude
        /// RadiationLWAccumulation           19    exclude
        /// RadiationNetSurfaceLWAccumulation 20    exclude
        /// RadiationNetSurfaceSWAccumulation 21    exclude
        /// RadiationDiffuseAccumulation      22    exclude
        /// LandSeaMask                       23    exclude
        ///
        /// 1,2,3,4,5,9,12

*/

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    LoginDialog ld;
    if(ld.exec() == QDialog::Accepted)
    {
       qDebug() << "accepted emitted";
       w.show();
    }
    qDebug()<< "returning a exec";
    return a.exec();
}
