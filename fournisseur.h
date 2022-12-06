#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
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
#include <QTableView>
class fournisseur
{
public:
    fournisseur();
    fournisseur(int,QString,QString,QString,QString,int,QString);

        int getid();
        QString getnom();
        QString getprenom();
        QString getemail();
        QString gettypem();
        int getprix();
        QString getimg();

        void setid(int);
        void setnom(QString);
        void setprenom(QString);
        void setemail(QString);
        void settypem(QString);
        void setprix(int);
        void setimg(QString);

        bool AjouterF();
        bool ModifierF();
        bool SupprimerF(int);
        QSqlQueryModel* afficher();
        QSqlQueryModel* afficher_id();
        QSqlQueryModel* tri_nom();
        QSqlQueryModel* tri_typem();

        QString read();
        void write(QString,QString);
        QString time();
        void clearh();
        void clearTable(QTableView *table);
        void chercheID(QTableView *table, QString x);
        void chercheNom(QTableView *table, QString x);
    private:
        int ID;
        QString NOM;
        QString PRENOM;
        QString EMAIL;
        QString TYPE_MATERIEL;
        int PRIX;
        QString img;
};

#endif // FOURNISSEUR_H
