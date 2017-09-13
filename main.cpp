#include <QtGui/QApplication>
#include "mainwindow.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0, "fichierDeConf.conf");
    w.show();

    return a.exec();
}
