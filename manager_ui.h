/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MANAGER_UI_H
#define MANAGER_UI_H

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
    QLineEdit *lineOperation;
    QPushButton *SaveButton;
    QPushButton *SendButton;
    QLabel *labelMessageReceived;
    QLineEdit *lineMessageReceived;
    QPushButton *InvoiceButton;
    QPushButton *FinishButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Manager)
    {
        if (Manager->objectName().isEmpty())
            Manager->setObjectName(QStringLiteral("Manager"));
        Manager->resize(570, 525);
        centralWidget = new QWidget(Manager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelV1 = new QLabel(centralWidget);
        labelV1->setObjectName(QStringLiteral("labelV1"));
        labelV1->setGeometry(QRect(20, 300, 100, 15));
        labelV2 = new QLabel(centralWidget);
        labelV2->setObjectName(QStringLiteral("labelV2"));
        labelV2->setGeometry(QRect(20, 325, 100, 15));
        labelV3 = new QLabel(centralWidget);
        labelV3->setObjectName(QStringLiteral("labelV3"));
        labelV3->setGeometry(QRect(20, 350, 100, 15));
        lineV1 = new QLineEdit(centralWidget);
        lineV1->setObjectName(QStringLiteral("lineV1"));
        lineV1->setGeometry(QRect(120, 300, 120, 20));
        lineV1->setReadOnly(true);
        lineV2 = new QLineEdit(centralWidget);
        lineV2->setObjectName(QStringLiteral("lineV2"));
        lineV2->setGeometry(QRect(120, 325, 120, 20));
        lineV2->setReadOnly(true);
        lineV3 = new QLineEdit(centralWidget);
        lineV3->setObjectName(QStringLiteral("lineV3"));
        lineV3->setGeometry(QRect(120, 350, 120, 20));
        lineV3->setReadOnly(true);
        labelMessage = new QLabel(centralWidget);
        labelMessage->setObjectName(QStringLiteral("labelMessage"));
        labelMessage->setGeometry(QRect(20, 385, 100, 13));
        lineMessage = new QLineEdit(centralWidget);
        lineMessage->setObjectName(QStringLiteral("lineMessage"));
        lineMessage->setGeometry(QRect(20, 410, 400, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(270, 300, 150, 16));
        lineOperation = new QLineEdit(centralWidget);
        lineOperation->setObjectName(QStringLiteral("lineOperation"));
        lineOperation->setGeometry(QRect(270, 325, 150, 20));
        SaveButton = new QPushButton(centralWidget);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        SaveButton->setGeometry(QRect(270, 350, 80, 23));
        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(470, 410, 80, 23));
        labelMessageReceived = new QLabel(centralWidget);
        labelMessageReceived->setObjectName(QStringLiteral("labelMessageReceived"));
        labelMessageReceived->setGeometry(QRect(20, 435, 100, 15));
        lineMessageReceived = new QLineEdit(centralWidget);
        lineMessageReceived->setObjectName(QStringLiteral("lineMessageReceived"));
        lineMessageReceived->setGeometry(QRect(20, 460, 400, 20));
        lineMessageReceived->setReadOnly(true);
        InvoiceButton = new QPushButton(centralWidget);
        InvoiceButton->setObjectName(QStringLiteral("InvoiceButton"));
        InvoiceButton->setGeometry(QRect(470, 350, 80, 23));
        FinishButton = new QPushButton(centralWidget);
        FinishButton->setObjectName(QStringLiteral("FinishButton"));
        FinishButton->setGeometry(QRect(470, 460, 80, 23));
        Manager->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Manager);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        Manager->setMenuBar(menuBar);
        statusBar = new QStatusBar(Manager);
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        labelMessage->setText(QApplication::translate("Manager", "message :", 0));
        label_5->setText(QApplication::translate("Manager", "New operation:", 0));
        SaveButton->setText(QApplication::translate("Manager", "Enregistrer", 0));
        SendButton->setText(QApplication::translate("Manager", "Tranmettre", 0));
        labelMessageReceived->setText(QApplication::translate("Manager", "message recu :", 0));
        InvoiceButton->setText(QApplication::translate("Manager", "Facturation", 0));
        FinishButton->setText(QApplication::translate("Manager", "Terminer", 0));
    } // retranslateUi

};

namespace Ui {
    class Manager: public Ui_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MANAGER_UI_H
