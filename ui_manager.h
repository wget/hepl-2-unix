/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLE_H
#define UI_CONTROLE_H

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

class Ui_Manager
{
public:
    QWidget *centralWidget;
    QLabel *labelV1;
    QLabel *labelV2;
    QLabel *labelV3;
    QLineEdit *lineV1;
    QLineEdit *lineV2;
    QLineEdit *lineV3;
    QLabel *labelMessage;
    QLineEdit *lineMessage;
    QLabel *label_5;
    QLineEdit *lineIntervention;
    QPushButton *BouttonEnregistrer;
    QPushButton *BouttonTransmettre;
    QLabel *labelMessageRecu;
    QLineEdit *lineMessageRecu;
    QPushButton *BouttonFacture;
    QPushButton *BouttonTerminer;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Manager)
    {
        if (Manager->objectName().isEmpty())
            Manager->setObjectName(QString::fromUtf8("Manager"));
        Manager->resize(570, 525);
        centralWidget = new QWidget(Manager);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelV1 = new QLabel(centralWidget);
        labelV1->setObjectName(QString::fromUtf8("labelV1"));
        labelV1->setGeometry(QRect(20, 300, 100, 15));
        labelV2 = new QLabel(centralWidget);
        labelV2->setObjectName(QString::fromUtf8("labelV2"));
        labelV2->setGeometry(QRect(20, 325, 100, 15));
        labelV3 = new QLabel(centralWidget);
        labelV3->setObjectName(QString::fromUtf8("labelV3"));
        labelV3->setGeometry(QRect(20, 350, 100, 15));
        lineV1 = new QLineEdit(centralWidget);
        lineV1->setObjectName(QString::fromUtf8("lineV1"));
        lineV1->setGeometry(QRect(120, 300, 120, 20));
        lineV1->setReadOnly(true);
        lineV2 = new QLineEdit(centralWidget);
        lineV2->setObjectName(QString::fromUtf8("lineV2"));
        lineV2->setGeometry(QRect(120, 325, 120, 20));
        lineV2->setReadOnly(true);
        lineV3 = new QLineEdit(centralWidget);
        lineV3->setObjectName(QString::fromUtf8("lineV3"));
        lineV3->setGeometry(QRect(120, 350, 120, 20));
        lineV3->setReadOnly(true);
        labelMessage = new QLabel(centralWidget);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));
        labelMessage->setGeometry(QRect(20, 385, 100, 13));
        lineMessage = new QLineEdit(centralWidget);
        lineMessage->setObjectName(QString::fromUtf8("lineMessage"));
        lineMessage->setGeometry(QRect(20, 410, 400, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(270, 300, 150, 16));
        lineIntervention = new QLineEdit(centralWidget);
        lineIntervention->setObjectName(QString::fromUtf8("lineIntervention"));
        lineIntervention->setGeometry(QRect(270, 325, 150, 20));
        BouttonEnregistrer = new QPushButton(centralWidget);
        BouttonEnregistrer->setObjectName(QString::fromUtf8("BouttonEnregistrer"));
        BouttonEnregistrer->setGeometry(QRect(270, 350, 80, 23));
        BouttonTransmettre = new QPushButton(centralWidget);
        BouttonTransmettre->setObjectName(QString::fromUtf8("BouttonTransmettre"));
        BouttonTransmettre->setGeometry(QRect(470, 410, 80, 23));
        labelMessageRecu = new QLabel(centralWidget);
        labelMessageRecu->setObjectName(QString::fromUtf8("labelMessageRecu"));
        labelMessageRecu->setGeometry(QRect(20, 435, 100, 15));
        lineMessageRecu = new QLineEdit(centralWidget);
        lineMessageRecu->setObjectName(QString::fromUtf8("lineMessageRecu"));
        lineMessageRecu->setGeometry(QRect(20, 460, 400, 20));
        lineMessageRecu->setReadOnly(true);
        BouttonFacture = new QPushButton(centralWidget);
        BouttonFacture->setObjectName(QString::fromUtf8("BouttonFacture"));
        BouttonFacture->setGeometry(QRect(470, 350, 80, 23));
        BouttonTerminer = new QPushButton(centralWidget);
        BouttonTerminer->setObjectName(QString::fromUtf8("BouttonTerminer"));
        BouttonTerminer->setGeometry(QRect(470, 460, 80, 23));
        Manager->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Manager);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        Manager->setMenuBar(menuBar);
        statusBar = new QStatusBar(Manager);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Manager->setStatusBar(statusBar);

        retranslateUi(Manager);

        QMetaObject::connectSlotsByName(Manager);
    } // setupUi

    void retranslateUi(QMainWindow *Manager)
    {
        Manager->setWindowTitle(QApplication::translate("Manager", "Manager", 0));
        labelV1->setText(QApplication::translate("Manager", "Vehicle 1 :", 0));
        labelV2->setText(QApplication::translate("Manager", "Vehicle 2 :", 0));
        labelV3->setText(QApplication::translate("Manager", "Vehicle 3 :", 0));
        labelMessage->setText(QApplication::translate("Manager", "Message :", 0));
        label_5->setText(QApplication::translate("Manager", "Nouvelle intervention :", 0));
        BouttonEnregistrer->setText(QApplication::translate("Manager", "Enregistrer", 0));
        BouttonTransmettre->setText(QApplication::translate("Manager", "Tranmettre", 0));
        labelMessageRecu->setText(QApplication::translate("Manager", "Message recu :", 0));
        BouttonFacture->setText(QApplication::translate("Manager", "Facturation", 0));
        BouttonTerminer->setText(QApplication::translate("Manager", "Terminer", 0));
    } // retranslateUi

};

namespace Ui {
    class Manager: public Ui_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLE_H
