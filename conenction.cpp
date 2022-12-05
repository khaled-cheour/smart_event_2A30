#include "conenction.h"

conenction::conenction()
{

}
bool conenction::CreateConnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("ProjetA2");
    db.setUserName("lina");
    db.setPassword("lina");
    if (db.open())
        test=true;
    return  test;
}

void conenction::FermerConnexion(){db.close();}

bool conenction::OuvrirConnexion(){
    if (db.open())
        return true ;
    else
        return false;

}
