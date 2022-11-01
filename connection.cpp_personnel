#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
connection::connection()
{

}
bool connection::CreateConnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet_c++");
    db.setUserName("khaled");
    db.setPassword("khaled");
    if (db.open())
        test=true;
    return  test;
}

void connection::FermerConnexion(){db.close();}

bool connection::OuvrirConnexion(){
    if (db.open())
        return true ;
    else
        return false;

}
