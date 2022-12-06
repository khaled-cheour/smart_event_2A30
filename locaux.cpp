#include "locaux.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QMessageBox>
/**************************************/
locaux::locaux()
{
    ADRESSE=" ";
    NOM=" ";
    SUPERFICIE=" ";
    NPLACES=0;
    PRIX=0;
    DESCRIPTION=" ";
}
/**************************************/
locaux::locaux(QString ADRESSE,QString NOM, QString SUPERFICIE ,int NPLACES ,int PRIX, QString DESCRIPTION)
{
    this->ADRESSE=ADRESSE;
    this->NOM=NOM;
    this->SUPERFICIE=SUPERFICIE;
    this->NPLACES=NPLACES;
    this->PRIX=PRIX;
    this->DESCRIPTION=DESCRIPTION;
}
/**************************************/
QString locaux::getadresse(){return ADRESSE;}
QString locaux::getnom(){return NOM;}
QString locaux::getsuperficie(){return SUPERFICIE;}
int locaux::getnombreplace(){return NPLACES;}
int locaux::getprix(){return PRIX;}
QString locaux::getdescription(){return DESCRIPTION;}
/**************************************/
void locaux::setadresse(QString ADRESSE){this->ADRESSE=ADRESSE;}
void locaux::setnom(QString NOM){this->NOM=NOM;}
void locaux::setsuperficie(QString SUPERFICIE){this->SUPERFICIE=SUPERFICIE;}
void locaux::setnomberplace(int NPLACES){this->NPLACES=NPLACES;}
void locaux::setprix(int PRIX){this->PRIX=PRIX;}
void locaux::setdescription(QString DESCRIPTION){this->DESCRIPTION=DESCRIPTION;}
/**************************************/
bool locaux::AjouterL()
{
    QSqlQuery query;
    QString id_string=QString::const_reference(NOM);
         query.prepare("INSERT INTO LOCAUX(ADRESSE,NOM,SUPERFICIE,NPLACES,PRIX,DESCRIPTION)" "VALUES (:ADRESSE,:NOM,:SUPERFICIE,:NPLACES,:PRIX,:DESCRIPTION)");
         query.bindValue(":ADRESSE", ADRESSE);
         query.bindValue(":NOM", NOM);
         query.bindValue(":SUPERFICIE", SUPERFICIE);
         query.bindValue(":NPLACES", NPLACES);
         query.bindValue(":PRIX", PRIX);
         query.bindValue(":DESCRIPTION", DESCRIPTION);
    return query.exec();
}
bool locaux::SupprimerL(QString ADRESSE)
{
    QSqlQuery query;
         query.prepare("DELETE FROM LOCAUX where NOM= :NOM");
         query.bindValue(0, ADRESSE);
    return query.exec();
}
bool locaux::ModifierL()
{
    QSqlQuery query;
        query.prepare("UPDATE LOCAUX SET ADRESSE=:ADRESSE, SUPERFICIE=:SUPERFICIE, NPLACES=:NPLACES, PRIX=:PRIX, DESCRIPTION=:DESCRIPTION WHERE NOM=:NOM ");
        query.bindValue(":NOM", NOM);
        query.bindValue(":SUPERFICIE", SUPERFICIE);
        query.bindValue(":NPLACES", NPLACES);
        query.bindValue(":PRIX", PRIX);
        query.bindValue(":DESCRIPTION", DESCRIPTION);
        query.bindValue(":ADRESSE", ADRESSE);
    return query.exec();
}
/**************************************/
QSqlQueryModel* locaux::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * from LOCAUX order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NPLACES"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return  model;
}
QSqlQueryModel* locaux::afficher_adresse()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT ADRESSE from LOCAUX");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ADRESSE"));
    return model;
}
/**************************************/
QSqlQueryModel * locaux::tri_Nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LOCAUX order by NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NPLACES"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
QSqlQueryModel * locaux::tri_Prix()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LOCAUX order by PRIX");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NPLACES"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
QSqlQueryModel * locaux::tri_NbPlace()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LOCAUX order by NPLACES");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("SUPERFICIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NPLACES"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
/**************************************/
QString locaux::read()
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Locaux.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void locaux::write(QString time, QString txt)
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Locaux.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString locaux::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void locaux::clearh()
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Locaux.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void locaux::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void locaux::chercheNom(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from LOCAUX where regexp_like(NOM,:NOM);");
   query->bindValue(":NOM",x);
   if(x==0)
   {
       query->prepare("select * from LOCAUX;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void locaux::chercheAdresse(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from LOCAUX where regexp_like(ADRESSE,:ADRESSE);");
    query->bindValue(":ADRESSE",x);
    if(x==0)
    {
        query->prepare("select * from LOCAUX;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
