#ifndef VEHICULE_H
#define VEHICULE_H

#include <QMainWindow>

namespace Ui {
class Vehicule;
}

class Vehicule : public QMainWindow
{
    Q_OBJECT

public:
    explicit Vehicule(QWidget *parent = 0);
    ~Vehicule();
    void AfficheMessageIntervention(const char*);
    void AfficheMessageRecu(const char*);
    void AfficheEtat(const char*);

private slots:
    void on_BouttonEnvoyer_clicked();
    void on_BouttonPause_clicked();
    void on_BouttonRetour_clicked();

private:
    Ui::Vehicule *ui;
};

#endif // VEHICULE_H
