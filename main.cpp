#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connexion c;
    bool test=c.CreateConnexion();
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("DataBase is open"),
                    QObject::tr("Connection Successful."), QMessageBox::Close);

}

    else
        QMessageBox::critical(nullptr, QObject::tr("DataBase in not open"),
                    QObject::tr("Connection Failed."), QMessageBox::Close);
    return a.exec();
}
