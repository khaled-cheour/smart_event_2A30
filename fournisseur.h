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

class fournisseur
{
public:
    fournisseur();
    fournisseur(int,QString,QString,QString,QString);

    int getid();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString gettypem();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setemail(QString);
    void settypem(QString);

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

private:
    int ID;
    QString NOM;
    QString PRENOM;
    QString EMAIL;
    QString TYPE_MATERIEL;
};

#endif // FOURNISSEUR_H
