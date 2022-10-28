#include "sponsoring.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QFile>

sponsoring::sponsoring()
{
    ID=0;
    NUM_TEL=0;
    DESCRIPTION=" ";
}
sponsoring::sponsoring(int ID, int NUM_TEL, QString DESCRIPTION)
{
    this->ID=ID;
    this->NUM_TEL=NUM_TEL;
    this->DESCRIPTION=DESCRIPTION;
}
/**************************************/
int sponsoring::getid()
{
    return ID;
}
int sponsoring::getnumtel()
{
    return NUM_TEL;
}
QString sponsoring::getdescription()
{
    return DESCRIPTION;
}
/**************************************/
void sponsoring::setid(int ID)
{
    this->ID=ID;
}
void sponsoring::setnumtel(int NUM_TEL)
{
    this->NUM_TEL=NUM_TEL;
}
void sponsoring::setdescription(QString DESCRIPTION)
{
    this->DESCRIPTION=DESCRIPTION;
}
/**************************************/
bool sponsoring::ajouterS()
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
         query.prepare("INSERT INTO SPONSORING(ID,NUM_TEL,DESCRIPTION)" "VALUES (:ID,:NUM_TEL,:DESCRIPTION)");
         query.bindValue(":ID", ID);
         query.bindValue(":NUM_TEL", NUM_TEL);
         query.bindValue(":DESCRIPTION", DESCRIPTION);
    return query.exec();
}
bool sponsoring::supprimerS(int ID)
{
    QSqlQuery query;
         query.prepare("DELETE FROM SPONSORING where ID= :ID");
         query.bindValue(0, ID);
    return query.exec();
}
bool sponsoring::modifierS()
{
    QSqlQuery query;
        query.prepare("UPDATE SPONSORING SET NUM_TEL=:NUM_TEL, DESCRIPTION=:DESCRIPTION WHERE ID=:ID ");
        query.bindValue(":ID", ID);
        query.bindValue(":NUM_TEL", NUM_TEL);
        query.bindValue(":DESCRIPTION", DESCRIPTION);
    return query.exec();
}
/**************************************/
QSqlQueryModel* sponsoring::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM SPONSORING");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM_TEL"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return  model;
}
QSqlQueryModel* sponsoring ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT ID from SPONSORING");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return model;
}
/**************************************/

QSqlQueryModel * sponsoring::tri_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from SPONSORING order by ID");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
QSqlQueryModel * sponsoring::tri_numtel()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from SPONSORING order by NUM_TEL");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    return model;
}
/**************************************/

QString sponsoring::read()
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/historysponso.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void sponsoring::write(QString time, QString txt)
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/historysponso.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString sponsoring::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void sponsoring::clearh()
{
    QFile file("C:/Users/alamo/Desktop/ProjetCPP/historysponso.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
