#include "manager.h"
#include <QApplication>
int idQ, idS, idM;

anager *w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new Manager();
    w->show();
    return a.exec();
}
