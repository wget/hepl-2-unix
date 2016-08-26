#include <QApplication>
#include "manager.h"

int idQ, idS, idM;

Manager *w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new Manager();
    w->show();
    return a.exec();
}
