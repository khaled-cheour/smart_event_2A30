#ifndef LOCAUX_H
#define LOCAUX_H
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
class locaux
{
public:
    locaux();
    locaux(QString,QString,QString,int,int,QString);

        QString getnom();
        QString getadresse();
        QString getsuperficie();
        int getnombreplace();
        int getprix();
        QString getdescription();

        void setnom(QString);
        void setadresse(QString);
        void setsuperficie(QString);
        void setnomberplace(int);
        void setprix(int);
        void setdescription(QString);

        bool AjouterL();
        bool ModifierL();
        bool SupprimerL(QString);
        QSqlQueryModel* afficher();
        QSqlQueryModel* afficher_adresse();
        QSqlQueryModel* tri_Nom();
        QSqlQueryModel* tri_Prix();
        QSqlQueryModel* tri_NbPlace();

        QString read();
        void write(QString,QString);
        QString time();
        void clearh();
        void clearTable(QTableView * table);
        void chercheNom(QTableView *table, QString x);
        void chercheAdresse(QTableView *table, QString x);


    private:
        QString NOM;
        QString ADRESSE;
        QString SUPERFICIE;
        int NPLACES;
        int PRIX;
        QString DESCRIPTION;
};

#endif // LOCAUX_H
