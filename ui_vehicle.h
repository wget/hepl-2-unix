/********************************************************************************
** Form generated from reading UI file 'vehicule.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEHICULE_H
#define UI_VEHICULE_H

#include <QtCore/QVariant>
// #include <QtGui/QAction>
#include <QtWidgets/QAction>
// #include <QtGui/QApplication>
#include <QtWidgets/QApplication>
// #include <QtGui/QButtonGroup>
#include <QtWidgets/QButtonGroup>
// #include <QtGui/QHeaderView>
#include <QtWidgets/QHeaderView>
// #include <QtGui/QLabel>
#include <QtWidgets/QLabel>
// #include <QtGui/QLineEdit>
#include <QtWidgets/QLineEdit>
// #include <QtGui/QMainWindow>
#include <QtWidgets/QMainWindow>
// #include <QtGui/QMenuBar>
#include <QtWidgets/QMenuBar>
// #include <QtGui/QPushButton>
#include <QtWidgets/QPushButton>
// #include <QtGui/QStatusBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_Vehicle
{
public:
    QWidget *centralWidget;
    QLabel *labelMessagePatron;
    QLabel *labelMessageRecu;
    QLabel *labelIntervention;
    QLabel *labelEtat;
    QLineEdit *lineMessagePatron;
    QLineEdit *lineMessageRecu;
    QLineEdit *lineMessageIntervention;
    QPushButton *BouttonPause;
    QPushButton *BouttonRetour;
    QPushButton *BouttonEnvoyer;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Vehicle)
    {
        if (Vehicle->objectName().isEmpty())
            Vehicle->setObjectName(QString::fromUtf8("Vehicle"));
        Vehicle->resize(400, 230);
        centralWidget = new QWidget(Vehicle);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelMessagePatron = new QLabel(centralWidget);
        labelMessagePatron->setObjectName(QString::fromUtf8("labelMessagePatron"));
        labelMessagePatron->setGeometry(QRect(20, 10, 150, 13));
        labelMessageRecu = new QLabel(centralWidget);
        labelMessageRecu->setObjectName(QString::fromUtf8("labelMessageRecu"));
        labelMessageRecu->setGeometry(QRect(20, 60, 150, 13));
        labelIntervention = new QLabel(centralWidget);
        labelIntervention->setObjectName(QString::fromUtf8("labelIntervention"));
        labelIntervention->setGeometry(QRect(20, 110, 150, 13));
        labelEtat = new QLabel(centralWidget);
        labelEtat->setObjectName(QString::fromUtf8("labelEtat"));
        labelEtat->setGeometry(QRect(240, 10, 140, 16));
        labelEtat->setLayoutDirection(Qt::LeftToRight);
        labelEtat->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineMessagePatron = new QLineEdit(centralWidget);
        lineMessagePatron->setObjectName(QString::fromUtf8("lineMessagePatron"));
        lineMessagePatron->setGeometry(QRect(20, 30, 260, 20));
        lineMessagePatron->setReadOnly(false);
        lineMessageRecu = new QLineEdit(centralWidget);
        lineMessageRecu->setObjectName(QString::fromUtf8("lineMessageRecu"));
        lineMessageRecu->setGeometry(QRect(20, 80, 260, 20));
        lineMessageRecu->setReadOnly(true);
        lineMessageIntervention = new QLineEdit(centralWidget);
        lineMessageIntervention->setObjectName(QString::fromUtf8("lineMessageIntervention"));
        lineMessageIntervention->setGeometry(QRect(20, 130, 260, 20));
        lineMessageIntervention->setReadOnly(true);
        BouttonPause = new QPushButton(centralWidget);
        BouttonPause->setObjectName(QString::fromUtf8("BouttonPause"));
        BouttonPause->setGeometry(QRect(20, 160, 75, 23));
        BouttonRetour = new QPushButton(centralWidget);
        BouttonRetour->setObjectName(QString::fromUtf8("BouttonRetour"));
        BouttonRetour->setGeometry(QRect(305, 160, 75, 23));
        BouttonEnvoyer = new QPushButton(centralWidget);
        BouttonEnvoyer->setObjectName(QString::fromUtf8("BouttonEnvoyer"));
        BouttonEnvoyer->setGeometry(QRect(305, 30, 75, 23));
        Vehicle->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Vehicle);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        Vehicle->setMenuBar(menuBar);
        statusBar = new QStatusBar(Vehicle);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Vehicle->setStatusBar(statusBar);

        retranslateUi(Vehicle);

        QMetaObject::connectSlotsByName(Vehicle);
    } // setupUi

    void retranslateUi(QMainWindow *Vehicle)
    {
        Vehicle->setWindowTitle(QApplication::translate("Vehicle", "Vehicle", 0));
        labelMessagePatron->setText(QApplication::translate("Vehicle", "Message au patron :", 0));
        labelMessageRecu->setText(QApplication::translate("Vehicle", "Message recu :", 0));
        labelIntervention->setText(QApplication::translate("Vehicle", "Intervention chez :", 0));
        labelEtat->setText(QApplication::translate("Vehicle", "TextLabel", 0));
        BouttonPause->setText(QApplication::translate("Vehicle", "Pause", 0));
        BouttonRetour->setText(QApplication::translate("Vehicle", "Retour", 0));
        BouttonEnvoyer->setText(QApplication::translate("Vehicle", "Envoyer", 0));
    } // retranslateUi

};

namespace Ui {
    class Vehicle: public Ui_Vehicle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEHICULE_H
