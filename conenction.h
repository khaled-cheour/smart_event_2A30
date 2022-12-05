#ifndef CONENCTION_H
#define CONENCTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class conenction
{
public:
    conenction();
    bool CreateConnexion();
    bool OuvrirConnexion();
    void FermerConnexion();
    QSqlDatabase db;
};

#endif // CONENCTION_H
