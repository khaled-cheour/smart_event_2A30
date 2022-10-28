#include "login_bd.h"

login_bd::login_bd()
{

}

bool login_bd::CreateConnexion1()
{
    bool test=false;
QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC");
db1.setDatabaseName("ProjetA2");
db1.setUserName("Raydux");
db1.setPassword("Raydux");

if (db1.open())
test=true;
    return  test;
}

void login_bd::FermerConnexion1()
{
    db1.close();
}

bool login_bd::OuvrirConnexion1()
{
    if (db1.open())
        return true ;
    else
        return false;
}


