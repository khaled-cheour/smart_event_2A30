#ifndef PERSONNEL_H
#define PERSONNEL_H
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

class personnel
{
public:
    personnel();
    personnel(int,QString,QString,QString,QString,QDate,int);

    int getcin();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getemail();
    QDate getdate();

    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setemail(QString);
    void setdate(QDate);

    bool ajouter();
    bool ajouter1();
    bool modifierP();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* tri_cin();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_email();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();

    QString USERNAME;
    QString PASSWORD;

private:
    int CIN;
    QString NOM;
    QString PRENOM;
    QString ADRESSE;
    QString EMAIL;
    QDate DATE_DE_NAISSANCE;
    int CIN_DIRIGEUR;

};

#endif // PERSONNEL_H
