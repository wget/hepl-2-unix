/********************************************************************************
** Form generated from reading UI file 'vehicle.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef VEHICLE_UI_H
#define VEHICLE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Vehicle
{
public:
    QWidget *centralWidget;
    QLabel *labelMessagePatron;
    QLabel *labelMessageReceived;
    QLabel *labelOperation;
    QLabel *labelState;
    QLineEdit *lineMessagePatron;
    QLineEdit *lineMessageReceived;
    QLineEdit *lineMessageIntervention;
    QPushButton *PauseButton;
    QPushButton *ReturnButton;
    QPushButton *SendButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Vehicle)
    {
        if (Vehicle->objectName().isEmpty())
            Vehicle->setObjectName(QStringLiteral("Vehicle"));
        Vehicle->resize(400, 230);
        centralWidget = new QWidget(Vehicle);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelMessagePatron = new QLabel(centralWidget);
        labelMessagePatron->setObjectName(QStringLiteral("labelMessagePatron"));
        labelMessagePatron->setGeometry(QRect(20, 10, 150, 13));
        labelMessageReceived = new QLabel(centralWidget);
        labelMessageReceived->setObjectName(QStringLiteral("labelMessageReceived"));
        labelMessageReceived->setGeometry(QRect(20, 60, 150, 13));
        labelOperation = new QLabel(centralWidget);
        labelOperation->setObjectName(QStringLiteral("labelOperation"));
        labelOperation->setGeometry(QRect(20, 110, 150, 13));
        labelState = new QLabel(centralWidget);
        labelState->setObjectName(QStringLiteral("labelState"));
        labelState->setGeometry(QRect(240, 10, 140, 16));
        labelState->setLayoutDirection(Qt::LeftToRight);
        labelState->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineMessagePatron = new QLineEdit(centralWidget);
        lineMessagePatron->setObjectName(QStringLiteral("lineMessagePatron"));
        lineMessagePatron->setGeometry(QRect(20, 30, 260, 20));
        lineMessagePatron->setReadOnly(false);
        lineMessageReceived = new QLineEdit(centralWidget);
        lineMessageReceived->setObjectName(QStringLiteral("lineMessageReceived"));
        lineMessageReceived->setGeometry(QRect(20, 80, 260, 20));
        lineMessageReceived->setReadOnly(true);
        lineMessageIntervention = new QLineEdit(centralWidget);
        lineMessageIntervention->setObjectName(QStringLiteral("lineMessageIntervention"));
        lineMessageIntervention->setGeometry(QRect(20, 130, 260, 20));
        lineMessageIntervention->setReadOnly(true);
        PauseButton = new QPushButton(centralWidget);
        PauseButton->setObjectName(QStringLiteral("PauseButton"));
        PauseButton->setGeometry(QRect(20, 160, 75, 23));
        ReturnButton = new QPushButton(centralWidget);
        ReturnButton->setObjectName(QStringLiteral("ReturnButton"));
        ReturnButton->setGeometry(QRect(305, 160, 75, 23));
        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(305, 30, 75, 23));
        Vehicle->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Vehicle);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        Vehicle->setMenuBar(menuBar);
        statusBar = new QStatusBar(Vehicle);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Vehicle->setStatusBar(statusBar);

        retranslateUi(Vehicle);

        QMetaObject::connectSlotsByName(Vehicle);
    } // setupUi

    void retranslateUi(QMainWindow *Vehicle)
    {
        Vehicle->setWindowTitle(QApplication::translate("Vehicle", "Vehicle", 0));
        labelMessagePatron->setText(QApplication::translate("Vehicle", "message au patron :", 0));
        labelMessageReceived->setText(QApplication::translate("Vehicle", "message recu :", 0));
        labelOperation->setText(QApplication::translate("Vehicle", "Intervention chez :", 0));
        labelState->setText(QApplication::translate("Vehicle", "TextLabel", 0));
        PauseButton->setText(QApplication::translate("Vehicle", "Pause", 0));
        ReturnButton->setText(QApplication::translate("Vehicle", "Retour", 0));
        SendButton->setText(QApplication::translate("Vehicle", "Envoyer", 0));
    } // retranslateUi

};

namespace Ui {
    class Vehicle: public Ui_Vehicle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // VEHICLE_UI_H
