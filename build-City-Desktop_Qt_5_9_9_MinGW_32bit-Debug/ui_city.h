/********************************************************************************
** Form generated from reading UI file 'city.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CITY_H
#define UI_CITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_City
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;

    void setupUi(QWidget *City)
    {
        if (City->objectName().isEmpty())
            City->setObjectName(QStringLiteral("City"));
        City->resize(1952, 1076);
        label = new QLabel(City);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(640, 250, 201, 91));
        label_2 = new QLabel(City);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(860, 10, 121, 51));
        label_3 = new QLabel(City);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1220, 220, 111, 51));
        label_4 = new QLabel(City);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1120, 160, 81, 51));
        label_5 = new QLabel(City);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(780, 430, 121, 71));
        label_6 = new QLabel(City);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(900, 520, 91, 51));
        label_7 = new QLabel(City);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1000, 570, 121, 61));
        label_8 = new QLabel(City);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(1270, 510, 121, 41));
        label_9 = new QLabel(City);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(400, 360, 121, 61));
        label_10 = new QLabel(City);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(190, 320, 131, 61));
        label_11 = new QLabel(City);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(540, 130, 91, 51));

        retranslateUi(City);

        QMetaObject::connectSlotsByName(City);
    } // setupUi

    void retranslateUi(QWidget *City)
    {
        City->setWindowTitle(QApplication::translate("City", "City", Q_NULLPTR));
        label->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">0WH</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">2BJ</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">1SH</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">7NJ</span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">5CS</span></p></body></html>", Q_NULLPTR));
        label_6->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">6GZ</span></p></body></html>", Q_NULLPTR));
        label_7->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">4SZ</span></p></body></html>", Q_NULLPTR));
        label_8->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">9XM</span></p></body></html>", Q_NULLPTR));
        label_9->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">8CQ</span></p></body></html>", Q_NULLPTR));
        label_10->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">3CD</span></p></body></html>", Q_NULLPTR));
        label_11->setText(QApplication::translate("City", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600;\">10XA</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class City: public Ui_City {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CITY_H
