# smart_event_2A30
#ifndef EVENEMENT_H
#define EVENEMENT_H

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
#include <QTime>

class evenement
{
public:
    evenement();
    evenement(int,QString,QString,QString,int,QDate,QTime);

    int getid();
    QString getnom();
    QString gettype();
    QString getlieu();
    int getnbrpersonnes();
    QDate getdate();
    QTime gettime();

    void setid(int);
    void setnom(QString);
    void settype(QString);
    void setlieu(QString);
    void setnbrpersonnes(int);
    void setdate(QDate);
    void settime(QTime);

    bool AjouterE();
    bool ModifierE();
    bool SupprimerE(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_type();
    QSqlQueryModel* tri_nbrpersonnes();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();

private:
    int ID;
    QString NOM;
    QString TYPE;
    QString LIEU;
    int NOMBRE_PERSONNES;
    QDate DATE_E;
    QTime TIME_E;


};

#endif // EVENEMENT_H
