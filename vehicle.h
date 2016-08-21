#ifndef VEHICULE_H
#define VEHICULE_H

#include <QtWidgets>
namespace Ui {
    class Vehicle;
} class Vehicle:public QMainWindow {

  Q_OBJECT public: explicit Vehicle(QWidget * parent = 0);
    ~Vehicle();
    void AfficheMessageIntervention(const char *);
    void AfficheMessageRecu(const char *);
    void AfficheEtat(const char *);
    private slots:void on_BouttonEnvoyer_clicked();
    void on_BouttonPause_clicked();
    void on_BouttonRetour_clicked();
  private: Ui::Vehicle * ui;
};


#endif				// VEHICULE_H
