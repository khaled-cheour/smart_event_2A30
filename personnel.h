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
#include <QTableView>

class personnel
{
public:
    personnel();
    personnel(int,QString,QString,QString,QString,QString,QDate,int,int);

    int getcin();
    int getNBR_ABSENCE();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getemail();
    QString getGENDER();
    QDate getdate();

    void setcin(int);
    void setNBR_ABSENCE(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setemail(QString);
    void setGENDER(QString);
    void setdate(QDate);

    bool ajouter();
    bool empolye();
    bool ajouter1();
    bool modifierP();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* affichercaht();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* afficher_NBR_ABSENCE();
    QSqlQueryModel* tri_cin();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_email();
    QSqlQueryModel* NBR__ABSENCE();
    QSqlQueryModel* employe_du_mois();


    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void cherchecin(QTableView *table, int x);
    void cherchenom(QTableView *table, QString x);
    //void employe_du_mois(QTableView *table ,int x);
    void employe_mois();
    QString USERNAME;
    QString PASSWORD;

private:
    int CIN;
    int NBR_ABSENCE;
    QString NOM;
    QString PRENOM;
    QString ADRESSE;
    QString EMAIL;
    QString GENDER;
    QDate DATE_DE_NAISSANCE;
    int CIN_DIRIGEUR;

};

#endif // PERSONNEL_H
