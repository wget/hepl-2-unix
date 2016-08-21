#include "controle.h"
#include <QApplication>

int	idQ,idS,idM;

Controle*	w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new Controle();
    w->show();

    return a.exec();
}
