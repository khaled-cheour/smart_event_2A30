#include "local.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QMessageBox>
/**************************************/
local::local()
{
    ADRESSE=" ";
    NOM=" ";
    SUPERFICIE=" ";
    NOMBRE_PLACES=0;
    PRIX=0;
    DESCRIPTION=" ";
}
/**************************************/
local::local(QString ADRESSE,QString NOM, QString SUPERFICIE ,int NOMBRE_PLACES ,int PRIX, QString DESCRIPTION)
{
    this->ADRESSE=ADRESSE;
    this->NOM=NOM;
    this->SUPERFICIE=SUPERFICIE;
    this->NOMBRE_PLACES=NOMBRE_PLACES;
    this->PRIX=PRIX;
    this->DESCRIPTION=DESCRIPTION;
}
/**************************************/
QString local::getadresse()
{
    return ADRESSE;
}
QString local::getnom()
{
    return NOM;
}
QString local::getsuperficie()
{
    return SUPERFICIE;
}
int local::getnombreplace()
{
    return NOMBRE_PLACES;
}
int local::getprix()
{
    return PRIX;
}
QString local::getdescription()
{
    return DESCRIPTION;
}
/**************************************/
void local::setadresse(QString ADRESSE)
{
    this->ADRESSE=ADRESSE;
}
void local::setnom(QString NOM)
{
    this->NOM=NOM;
}
void local::setsuperficie(QString SUPERFICIE)
{
    this->SUPERFICIE=SUPERFICIE;
}
void local::setnomberplace(int NOMBRE_PLACES)
{
    this->NOMBRE_PLACES=NOMBRE_PLACES;
}
void local::setprix(int PRIX)
{
    this->PRIX=PRIX;
}
void local::setdescription(QString DESCRIPTION)
{
    this->DESCRIPTION=DESCRIPTION;
}
/**************************************/
bool local::AjouterL()
{
    QSqlQuery query;
    QString id_string=QString::const_reference(NOM);
         query.prepare("INSERT INTO LOCAUX(ADRESSE,NOM,SUPERFICIE,NOMBRE_PLACES,PRIX,DESCRIPTION)" "VALUES (:ADRESSE,:NOM,:SUPERFICIE,:NOMBRE_PLACES,:PRIX,:DESCRIPTION)");
         query.bindValue(":ADRESSE", ADRESSE);
         query.bindValue(":NOM", NOM);
         query.bindValue(":SUPERFICIE", SUPERFICIE);
         query.bindValue(":NOMBRE_PLACES", NOMBRE_PLACES);
         query.bindValue(":PRIX", PRIX);
         query.bindValue(":DESCRIPTION", DESCRIPTION);
    return query.exec();
}
bool local::SupprimerL(QString ADRESSE)
{
    QSqlQuery query;
         query.prepare("DELETE FROM LOCAUX where ADRESSE= :ADRESSE");
         query.bindValue(0, ADRESSE);
    return query.exec();
}
bool local::ModifierL()
{
    QSqlQuery query;
        query.prepare("UPDATE LOCAUX SET NOM=:NOM, SUPERFICIE=:SUPERFICIE, NOMBRE_PLACES=:NOMBRE_PLACES, PRIX=:PRIX, DESCRIPTION=:DESCRIPTION WHERE ADRESSE=:ADRESSE ");
        query.bindValue(":NOM", NOM);
        query.bindValue(":SUPERFICIE", SUPERFICIE);
        query.bindValue(":NOMBRE_PLACES", NOMBRE_PLACES);
        query.bindValue(":PRIX", PRIX);
        query.bindValue(":DESCRIPTION", DESCRIPTION);
        query.bindValue(":ADRESSE", ADRESSE);
    return query.exec();
}
/**************************************/
QSqlQueryModel* local::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * from LOCAUX order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_PLACES"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return  model;
}
QSqlQueryModel* local::afficher_nom()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT NOM from LOCAUX");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    return model;
}
/**************************************/
QSqlQueryModel * local::tri_Nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LOCAUX order by NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_PLACES"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
QSqlQueryModel * local::tri_Prix()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LOCAUX order by PRIX");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_PLACES"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
QSqlQueryModel * local::tri_NbPlace()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LOCAUX order by NOMBRE_PLACES");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_PLACES"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
/**************************************/
QString local::read()
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/historylocaux.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void local::write(QString time, QString txt)
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/historylocaux.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString local::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void local::clearh()
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/historylocaux.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
