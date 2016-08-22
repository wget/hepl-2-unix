#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui/QPainter>

namespace Ui {
    class Manager;
}

class Manager:public QMainWindow {

    Q_OBJECT
    
public:
    explicit Manager(QWidget * parent = 0);
    ~Manager();
    void printMessageV1(const char *);
    void printMessageV2(const char *);
    void printMessageV3(const char *);
    void AfficheIntervention(const char *);
    void printMessage(const char *);
    void refresh();

private slots:
    void onSaveButtonClicked();
    void onInvoiceButtonClicked();
    void onSendButtonClicked();
    void onFinishButtonClicked();
    void drawSection(QPainter *, int, int);
    void paintEvent(QPaintEvent * event);

private:
    Ui::Manager *ui;
};

#endif // MANAGER_H
