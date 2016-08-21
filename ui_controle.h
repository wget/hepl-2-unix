/********************************************************************************
** Form generated from reading UI file 'controle.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLE_H
#define UI_CONTROLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Controle
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

    void setupUi(QMainWindow *Controle)
    {
        if (Controle->objectName().isEmpty())
            Controle->setObjectName(QString::fromUtf8("Controle"));
        Controle->resize(570, 525);
        centralWidget = new QWidget(Controle);
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
        Controle->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Controle);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        Controle->setMenuBar(menuBar);
        statusBar = new QStatusBar(Controle);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Controle->setStatusBar(statusBar);

        retranslateUi(Controle);

        QMetaObject::connectSlotsByName(Controle);
    } // setupUi

    void retranslateUi(QMainWindow *Controle)
    {
        Controle->setWindowTitle(QApplication::translate("Controle", "Controle", 0, QApplication::UnicodeUTF8));
        labelV1->setText(QApplication::translate("Controle", "Vehicule 1 :", 0, QApplication::UnicodeUTF8));
        labelV2->setText(QApplication::translate("Controle", "Vehicule 2 :", 0, QApplication::UnicodeUTF8));
        labelV3->setText(QApplication::translate("Controle", "Vehicule 3 :", 0, QApplication::UnicodeUTF8));
        labelMessage->setText(QApplication::translate("Controle", "Message :", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Controle", "Nouvelle intervention :", 0, QApplication::UnicodeUTF8));
        BouttonEnregistrer->setText(QApplication::translate("Controle", "Enregistrer", 0, QApplication::UnicodeUTF8));
        BouttonTransmettre->setText(QApplication::translate("Controle", "Tranmettre", 0, QApplication::UnicodeUTF8));
        labelMessageRecu->setText(QApplication::translate("Controle", "Message recu :", 0, QApplication::UnicodeUTF8));
        BouttonFacture->setText(QApplication::translate("Controle", "Facturation", 0, QApplication::UnicodeUTF8));
        BouttonTerminer->setText(QApplication::translate("Controle", "Terminer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Controle: public Ui_Controle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLE_H
