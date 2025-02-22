#include "weatherforecast.h"
#include "./ui_weatherforecast.h"
#include <QHBoxLayout>
#include <qpixmap.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qdatetime.h>
#include <QDate>
WeatherForecast::WeatherForecast(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherForecast)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &WeatherForecast::callWeatherApi);
}


WeatherForecast::~WeatherForecast()
{
    delete ui;
}

void WeatherForecast::callWeatherApi() {
    QUrl url("https://api.openweathermap.org/data/2.5/forecast");
    QUrlQuery query;
    query.addQueryItem("q",ui->lineEdit->text());
    query.addQueryItem("units","metric");
    query.addQueryItem("appid", "eadfc5c80b4489360e41c8efba3ad396");
    url.setQuery(query);

    QNetworkRequest request(url);
    qDebug() << "Weather API Request URL: " << url.toString();

    QNetworkReply *replyWeather = manager->get(request);
    connect(replyWeather, &QNetworkReply::finished, this, [this, replyWeather]() {
        this->onFinishedWeather(replyWeather);
    });
}

void WeatherForecast::onFinishedWeather(QNetworkReply *reply) {
    qDebug() << "onFinishedWeather called";

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: " << reply->errorString();
        ui->temperature->setText("Error fetching weather data");
    } else {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format!";
            ui->temperature->setText("Invalid JSON format");
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        QJsonArray list = jsonObj["list"].toArray();

        for (const QJsonValue &value : list){
            QWidget *itemWidget = new QWidget;
            QHBoxLayout *layout = new QHBoxLayout(itemWidget);
            QJsonObject currentWeather = value.toObject()["main"].toObject();
            addWeather(value.toObject());
            if (currentWeather.contains("temp")) {
                double temperature = currentWeather["temp"].toDouble();
                QString temp = QString::number(temperature);
                QLabel *label = new QLabel(temp,itemWidget);
                ui->temperature->setText("Temperature: " + QString::number(temperature, 'f', 2) + "°C");
            } else {
                ui->temperature->setText("Temperature data missing");
            }
        }

    }
    reply->deleteLater();
}

void WeatherForecast::addWeather(QJsonObject jsonObj){
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);

    QJsonObject mainObj = jsonObj["main"].toObject();

    QString dtTxt = jsonObj["dt_txt"].toString();
    QDateTime dateTime = QDateTime::fromString(dtTxt, "yyyy-MM-dd hh:mm:ss");

    QString dateaux = dateTime.toString("yyyy-MM-dd");
    int year,month,day;
    QString time = dateTime.toString("hh:mm:ss");
    QStringList hourParts = time.split(":");
    QString hour = hourParts[0];

    QStringList parts = dateaux.split("-");
    if (parts.size() == 3) {
        year = parts[0].toInt();
        month = parts[1].toInt();
        day = parts[2].toInt();
    }
    qDebug() << dtTxt << dateaux << time;

    QDate date(year,month,day);
    int sDay = date.dayOfWeek();
    QString weekDay = getDay(sDay);

    QLabel *labelDay = new QLabel(weekDay,itemWidget);
    layout->addWidget(labelDay);
    QLabel *labelHour = new QLabel(hour,itemWidget);
    layout->addWidget(labelHour);

    qDebug() << weekDay << hour;

    double temperature = mainObj["temp"].toDouble();
    QString temp = QString::number(temperature);
    qDebug() << temp;
    QLabel *label = new QLabel(temp,itemWidget);
    layout->addWidget(label);

    QLabel *iconLabel = new QLabel(itemWidget);
    QString icon;
    QJsonArray weatherArray = jsonObj["weather"].toArray();
    if (!weatherArray.isEmpty()) {
        QJsonObject weatherObj = weatherArray.first().toObject();
        icon = weatherObj["icon"].toString();
        QString iconPath = getPath(icon);
        qDebug() << "Icon ID:" << icon;

        QPixmap pix(iconPath);
        iconLabel->setPixmap(pix);
        layout->addWidget(iconLabel);
    }

    itemWidget->setLayout(layout);
    //itemWidget->setStyleSheet("background-color: white;");

    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->addItem(item);

    ui->listWidget->setItemWidget(item,itemWidget);
    ui->listWidget->setStyleSheet("QListWidget::item { height: 75px; }");
    //ui->listWidget->setStyleSheet("font-size: 10px;");
    qDebug() << "Widget count in layout: " << ui->listWidget->count();
    qDebug() << Qt::endl;

    QString iconPath = QCoreApplication::applicationDirPath() + "/resources/icons/01d.png";
    qDebug() << "Resolved path: " << iconPath;

    QPixmap pix(iconPath);
    if (pix.isNull()) {
        qDebug() << "Image file not found at: " << iconPath;
    } else {
        qDebug() << "Image loaded successfully from: " << iconPath;
    }
}

QString  WeatherForecast::getPath(QString id){
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

QString WeatherForecast::getDay(int day){
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
