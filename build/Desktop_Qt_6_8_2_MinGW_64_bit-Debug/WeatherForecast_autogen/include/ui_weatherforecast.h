/********************************************************************************
** Form generated from reading UI file 'weatherforecast.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHERFORECAST_H
#define UI_WEATHERFORECAST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeatherForecast
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *temperature;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WeatherForecast)
    {
        if (WeatherForecast->objectName().isEmpty())
            WeatherForecast->setObjectName("WeatherForecast");
        WeatherForecast->resize(800, 600);
        centralwidget = new QWidget(WeatherForecast);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 10, 311, 51));
        QFont font;
        font.setPointSize(16);
        lineEdit->setFont(font);
        lineEdit->setToolTipDuration(-3);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(390, 10, 121, 51));
        temperature = new QLineEdit(centralwidget);
        temperature->setObjectName("temperature");
        temperature->setGeometry(QRect(20, 460, 311, 51));
        temperature->setFont(font);
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 80, 741, 361));
        listWidget->setFont(font);
        WeatherForecast->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WeatherForecast);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        WeatherForecast->setMenuBar(menubar);
        statusbar = new QStatusBar(WeatherForecast);
        statusbar->setObjectName("statusbar");
        WeatherForecast->setStatusBar(statusbar);

        retranslateUi(WeatherForecast);

        QMetaObject::connectSlotsByName(WeatherForecast);
    } // setupUi

    void retranslateUi(QMainWindow *WeatherForecast)
    {
        WeatherForecast->setWindowTitle(QCoreApplication::translate("WeatherForecast", "WeatherForecast", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit->setToolTip(QCoreApplication::translate("WeatherForecast", "meow", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit->setPlaceholderText(QCoreApplication::translate("WeatherForecast", "Enter a city", nullptr));
        pushButton->setText(QCoreApplication::translate("WeatherForecast", "Seach", nullptr));
        temperature->setPlaceholderText(QCoreApplication::translate("WeatherForecast", "Temperature", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WeatherForecast: public Ui_WeatherForecast {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHERFORECAST_H
