#include "saver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    saver w;
    w.show();
    return a.exec();
}
