#include "mainwindow.h"
#include <QDebug>
#include "DuMessengerServer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DuMessengerServer Server;
    if(!Server.startServer(3333)){
    qDebug()<<"error:" << Server.errorString();
    return 1;
    }
    qDebug() << "Server started ...";
    return a.exec();
}
