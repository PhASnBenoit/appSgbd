#include "cihmappsgbd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CIhmAppSgbd w;
    w.show();

    return a.exec();
}
