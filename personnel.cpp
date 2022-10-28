#include "personnel.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QMessageBox>

personnel::personnel()
{
    CIN=0;
    NOM=" ";
    PRENOM=" ";
    ADRESSE=" ";
    EMAIL=" ";
    DATE_DE_NAISSANCE;
}
personnel::personnel(int CIN, QString NOM, QString PRENOM ,QString ADRESSE ,QString EMAIL, QDate DATE_DE_NAISSANCE,int CIN_DIRIGEUR)
{
    this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->ADRESSE=ADRESSE;
    this->EMAIL=EMAIL;
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
    this->CIN_DIRIGEUR=0;
}
/**************************************/

int personnel::getcin()
{
    return CIN;
}
QString personnel::getnom()
{
    return NOM;
}
QString personnel::getprenom()
{
    return PRENOM;
}
QString personnel::getadresse()
{
    return ADRESSE;
}
QString personnel::getemail()
{
    return EMAIL;
}
QDate personnel::getdate()
{
    return DATE_DE_NAISSANCE;
}
/**************************************/
void personnel::setcin(int CIN)
{
    this->CIN=CIN;
}
void personnel::setnom(QString NOM)
{
    this->NOM=NOM;
}
void personnel::setprenom(QString PRENOM)
{
    this->PRENOM=PRENOM;
}
void personnel::setadresse(QString ADRESSE)
{
    this->ADRESSE=ADRESSE;
}
void personnel::setemail(QString EMAIL)
{
    this->EMAIL=EMAIL;
}

void personnel::setdate(QDate DATE_DE_NAISSANCE)
{
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
}
/**************************************/
bool personnel::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(CIN);
         query.prepare("INSERT INTO PERSONNEL(CIN,NOM,PRENOM,ADRESSE,EMAIL,DATE_DE_NAISSANCE,CIN_DIRIGEUR)" "VALUES (:CIN,:NOM,:PRENOM,:ADRESSE,:EMAIL,:DATE_DE_NAISSANCE,:CIN_DIRIGEUR)");
         query.bindValue(":CIN", CIN);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":ADRESSE", ADRESSE);
         query.bindValue(":EMAIL", EMAIL);
         query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
         query.bindValue(":CIN_DIRIGEUR", CIN_DIRIGEUR);
    return query.exec();
}
bool personnel::supprimer(int CIN)
{
    QSqlQuery query;
         query.prepare("DELETE FROM PERSONNEL where CIN= :CIN");
         query.bindValue(0, CIN);
    return query.exec();
}
QSqlQueryModel* personnel::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM PERSONNEL");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    return  model;
}

bool personnel::modifierP()
{
    QSqlQuery query;
        query.prepare("UPDATE PERSONNEL SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, EMAIL=:EMAIL, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE WHERE CIN=:CIN ");
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":ADRESSE", ADRESSE);
        query.bindValue(":EMAIL", EMAIL);
        query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
        query.bindValue(":CIN", CIN);
    return query.exec();
}

QSqlQueryModel* personnel ::afficher_cin()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT CIN from PERSONNEL");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    return model;
}

QSqlQueryModel * personnel::tri_cin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from PERSONNEL order by CIN");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    return model;
}

QSqlQueryModel * personnel::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from PERSONNEL order by NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    return model;
}

QSqlQueryModel * personnel::tri_email()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from PERSONNEL order by EMAIL");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    return model;
}

bool personnel::ajouter1()
{
    QSqlQuery query;
         query.prepare("INSERT INTO LOGIN(USERNAME,PASSWORD)" "VALUES (:USERNAME,:PASSWORD)");
         query.bindValue(":USERNAME", USERNAME);
         query.bindValue(":PASSWORD", PASSWORD);
         return query.exec();
}

QString personnel::read()
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/history.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}

void personnel::write(QString time, QString txt)
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/history.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}

QString personnel::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}

void personnel::clearh()
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/history.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
