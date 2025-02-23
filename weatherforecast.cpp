#include "weatherforecast.h"
#include "./ui_weatherforecast.h"
#include <QHBoxLayout>
#include <qpixmap.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qdatetime.h>
#include <QDate>
#include <qtablewidget.h>

WeatherForecast::WeatherForecast(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherForecast)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &WeatherForecast::callWeatherApi);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &WeatherForecast::callWeatherApi);

    QFont font;
    font.setPointSize(16);
    qApp->setFont(font);

    ui->tableWidget->setColumnCount(4);
    QStringList headers = {"Day", "Hour", "Temp (°C)", ""};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}


WeatherForecast::~WeatherForecast()
{
    delete ui;
}

void WeatherForecast::callWeatherApi() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

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
    } else {
        QByteArray data = reply->readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format!";
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
            }
        }

    }
    reply->deleteLater();
}

void WeatherForecast::addWeather(QJsonObject jsonObj){
    QWidget *dayWidget = new QWidget;
    QWidget *hourWidget = new QWidget;
    QWidget *tempWidget = new QWidget;
    QWidget *iconWidget = new QWidget;
    QHBoxLayout *dayLayout = new QHBoxLayout(dayWidget);
    dayLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout *hourLayout = new QHBoxLayout(hourWidget);
    hourLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout *tempLayout = new QHBoxLayout(tempWidget);
    tempLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout *iconLayout = new QHBoxLayout(iconWidget);
    iconLayout->setAlignment(Qt::AlignCenter);

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

    QLabel *labelDay = new QLabel(weekDay,dayWidget);
    dayLayout->addWidget(labelDay);
    QLabel *labelHour = new QLabel(hour,hourWidget);
    hourLayout->addWidget(labelHour);

    qDebug() << weekDay << hour;

    double temperature = mainObj["temp"].toDouble();
    QString temp = QString::number(temperature);
    qDebug() << temp;
    QLabel *label = new QLabel(temp,tempWidget);
    tempLayout->addWidget(label);

    QLabel *iconLabel = new QLabel(iconWidget);
    QString icon;
    QJsonArray weatherArray = jsonObj["weather"].toArray();
    if (!weatherArray.isEmpty()) {
        QJsonObject weatherObj = weatherArray.first().toObject();
        icon = weatherObj["icon"].toString();
        QString iconPath = getPath(icon);
        qDebug() << "Icon ID:" << icon;

        QPixmap pix(iconPath);
        iconLabel->setPixmap(pix);
        iconLayout->addWidget(iconLabel);
    }

    iconWidget->setLayout(iconLayout);

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    dayWidget->setLayout(dayLayout);
    ui->tableWidget->setCellWidget(row, 0, dayWidget);

    hourWidget->setLayout(hourLayout);
    ui->tableWidget->setCellWidget(row, 1, hourWidget);

    tempWidget->setLayout(tempLayout);
    ui->tableWidget->setCellWidget(row, 2, tempWidget);
    ui->tableWidget->setCellWidget(row, 3, iconWidget);
    ui->tableWidget->setStyleSheet("QTableWidget::item { height: 80px; }");

    qDebug() << "Row count in table: " << ui->tableWidget->rowCount();

}
