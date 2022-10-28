#ifndef LOCAL_H
#define LOCAL_H

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

class local
{
public:
    local();
    local(QString,QString,QString,int,int,QString);

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
    QSqlQueryModel* afficher_nom();
    QSqlQueryModel* tri_Nom();
    QSqlQueryModel* tri_Prix();
    QSqlQueryModel* tri_NbPlace();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();

private:
    QString NOM;
    QString ADRESSE;
    QString SUPERFICIE;
    int NOMBRE_PLACES;
    int PRIX;
    QString DESCRIPTION;
};

#endif // LOCAL_H
