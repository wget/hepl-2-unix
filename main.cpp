#include "controle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controle w;
    w.show();

    return a.exec();
}
