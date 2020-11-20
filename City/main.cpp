#include "city.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    City w;
    w.show();
    return a.exec();
}
