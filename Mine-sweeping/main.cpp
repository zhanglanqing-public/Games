#include "minesweepwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MIneSweepWindow w;
    w.show();
    w.resize(500,500);
    w.move(100,100);
    return a.exec();
}
