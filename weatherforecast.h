#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class WeatherForecast;
}
QT_END_NAMESPACE

class WeatherForecast : public QMainWindow
{
    Q_OBJECT

public:
    WeatherForecast(QWidget *parent = nullptr);
    ~WeatherForecast();

private:
    Ui::WeatherForecast *ui;
    QNetworkAccessManager* manager;
    void addWeather(QJsonObject jsonObj);
    QString getPath(QString id){
        if (id == "01d") return QCoreApplication::applicationDirPath() + "/resources/icons/01d.png";
        else if (id == "01n") return QCoreApplication::applicationDirPath() + "/resources/icons/01n.png";
        else if (id == "02d") return QCoreApplication::applicationDirPath() + "/resources/icons/02d.png";
        else if (id == "02n") return QCoreApplication::applicationDirPath() + "/resources/icons/02n.png";
        else if (id == "03d") return QCoreApplication::applicationDirPath() + "/resources/icons/03d.png";
        else if (id == "03n") return QCoreApplication::applicationDirPath() + "/resources/icons/03n.png";
        else if (id == "04d") return QCoreApplication::applicationDirPath() + "/resources/icons/04d.png";
        else if (id == "04n") return QCoreApplication::applicationDirPath() + "/resources/icons/04n.png";
        else if (id == "09d") return QCoreApplication::applicationDirPath() + "/resources/icons/09d.png";
        else if (id == "09n") return QCoreApplication::applicationDirPath() + "/resources/icons/09n.png";
        else if (id == "10d") return QCoreApplication::applicationDirPath() + "/resources/icons/10d.png";
        else if (id == "10n") return QCoreApplication::applicationDirPath() + "/resources/icons/10n.png";
        else if (id == "11d") return QCoreApplication::applicationDirPath() + "/resources/icons/11d.png";
        else if (id == "11n") return QCoreApplication::applicationDirPath() + "/resources/icons/11n.png";
        else if (id == "13d") return QCoreApplication::applicationDirPath() + "/resources/icons/13d.png";
        else if (id == "13n") return QCoreApplication::applicationDirPath() + "/resources/icons/13n.png";
        else if (id == "50d") return QCoreApplication::applicationDirPath() + "/resources/icons/50d.png";
        return "icson/50n.png";
    }
    QString getDay(int day){
        switch (day){
        case 1:{
            return "Mon";
        }
        case 2:{
            return "Tue";
        }
        case 3:{
            return "Wed";
        }
        case 4:{
            return "Thu";
        }
        case 5:{
            return "Fri";
        }
        case 6:{
            return "Sat";
        }
        case 7:{
            return "Sun";
        }
        }
    }
private slots:
    void callWeatherApi();
    void onFinishedWeather(QNetworkReply* reply);
};
#endif // WEATHERFORECAST_H
