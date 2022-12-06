#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class connexion
{
public:
    connexion();
    bool CreateConnexion();
    bool OuvrirConnexion();
    void FermerConnexion();
    QSqlDatabase db;
};

#endif // CONNEXION_H
