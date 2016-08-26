#ifndef VEHICLE_H
#define VEHICLE_H

#include <QtWidgets>

namespace Ui {
    class Vehicle;
}

class Vehicle:public QMainWindow {

  Q_OBJECT 

public:
    explicit Vehicle(QWidget * parent = 0);
    ~Vehicle();
    void printMessageIntervention(const char *);
    void printMessageRecu(const char *);
    void printState(const char *);
    void manageTasks();

private slots:
    void onSendButtonClicked();
    void onPauseButtonClicked();
    void onReturnButtonClicked();

private:
    Ui::Vehicle *ui;
};


#endif // VEHICLE_H
