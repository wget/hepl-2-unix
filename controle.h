#ifndef CONTROLE_H
#define CONTROLE_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui/QPainter>

namespace Ui {
class Controle;
}

class Controle : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controle(QWidget *parent = 0);
    ~Controle();

    void AfficheMessageV1(const char* );
    void AfficheMessageV2(const char* );
    void AfficheMessageV3(const char* );
    void AfficheIntervention(const char* );
    void AfficheMessage(const char* );
    void Rafraichir();
private slots:
    void on_BouttonEnregistrer_clicked();
    void on_BouttonFacture_clicked();
    void on_BouttonTransmettre_clicked();
    void on_BouttonTerminer_clicked();

    void TraceTroncon(QPainter*, int ,int );
    void paintEvent(QPaintEvent *event);




private:
    Ui::Controle *ui;
};

#endif // CONTROLE_H
