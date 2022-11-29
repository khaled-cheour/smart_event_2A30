#include "connexion.h"

connexion::connexion() {}

bool connexion::CreateConnexion()
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

void connexion::FermerConnexion(){db.close();}

bool connexion::OuvrirConnexion(){
    if (db.open())
        return true ;
    else
        return false;

}
