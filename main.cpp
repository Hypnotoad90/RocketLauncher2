#include "rocketlauncher2.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RocketLauncher2 w(0, argc, argv);
    w.show();

    return a.exec();
}
