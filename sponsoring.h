#ifndef SPONSORING_H
#define SPONSORING_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QDate>

class sponsoring
{
public:
    sponsoring();
    sponsoring(int,int,QString);

    int getid();
    int getnumtel();
    QString getdescription();

    void setid(int);
    void setnumtel(int);
    void setdescription(QString);

    bool ajouterS();
    bool modifierS();
    bool supprimerS(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_numtel();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();

private:
    int ID;
    int NUM_TEL;
    QString DESCRIPTION;

};

#endif // SPONSORING_H
