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
#include <QTableView>

class evenement
{
public:
    evenement();
    evenement(int,QString,QString,QString,int,QDate,QTime,int,int);

    int getid();
    QString getnom();
    QString gettype();
    QString getlieu();
    int getnbrpersonnes();
    QDate getdate();
    QTime gettime();
    int getprix_f();
    int getprix_l();

    void setid(int);
    void setnom(QString);
    void settype(QString);
    void setlieu(QString);
    void setnbrpersonnes(int);
    void setdate(QDate);
    void settime(QTime);
    void setprix_f(int);
    void setprix_l(int);

    bool AjouterE();
    bool ModifierE();
    bool SupprimerE(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_type();
    QSqlQueryModel* tri_nbrpersonnes();
    QSqlQueryModel* tri_date();
    QSqlQueryModel* afficher1();
    QSqlQueryModel* triasc();
    QSqlQueryModel* tridesc();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void chercheID(QTableView *table, QString x);
    void chercheNom(QTableView *table, QString x);

private:
    int ID;
    QString NOM;
    QString TYPE;
    QString LIEU;
    int NOMBRE_PERSONNES;
    QDate DATE_E;
    QTime TIME_E;
    int PRIX_F;
    int PRIX_L;
};

#endif // EVENEMENT_H
