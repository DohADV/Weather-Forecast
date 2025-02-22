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
    QString getPath(QString id);
    QString getDay(int day);
private slots:
    void callWeatherApi();
    void onFinishedWeather(QNetworkReply* reply);
};
#endif // WEATHERFORECAST_H
