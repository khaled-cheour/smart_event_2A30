#include "mainwindow.h"
#include "connection.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
