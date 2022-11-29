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
    GENDER=" ";
    NBR_ABSENCE=0;
    DATE_DE_NAISSANCE;
}
personnel::personnel(int CIN, QString NOM, QString PRENOM ,QString ADRESSE ,QString EMAIL,QString GENDER, QDate DATE_DE_NAISSANCE,int CIN_DIRIGEUR ,int NBR_ABSENCE)
{
    this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->ADRESSE=ADRESSE;
    this->EMAIL=EMAIL;
    this->GENDER=GENDER;
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
    this->NBR_ABSENCE=NBR_ABSENCE;
    this->CIN_DIRIGEUR=0;
}
/**************************************/

int personnel::getcin()
{
    return CIN;
}
int personnel::getNBR_ABSENCE()
{
    return NBR_ABSENCE;
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
QString personnel::getGENDER()
{
    return GENDER;
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
void personnel::setNBR_ABSENCE(int NBR_ABSENCE)
{
    this->NBR_ABSENCE=NBR_ABSENCE;
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
void personnel::setGENDER(QString GENDER)
{
    this->GENDER=GENDER;
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
         query.prepare("INSERT INTO PERSONNEL(CIN,NBR_ABSENCE,NOM,PRENOM,ADRESSE,EMAIL,GENDER,DATE_DE_NAISSANCE,CIN_DIRIGEUR)" "VALUES (:CIN,:NBR_ABSENCE,:NOM,:PRENOM,:ADRESSE,:EMAIL,:GENDER,:DATE_DE_NAISSANCE,:CIN_DIRIGEUR)");

         query.bindValue(":CIN",QString::number(CIN));
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":ADRESSE", ADRESSE);
         query.bindValue(":EMAIL", EMAIL);
         query.bindValue(":GENDER", GENDER);
         query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
         query.bindValue(":CIN_DIRIGEUR", CIN_DIRIGEUR);
         query.bindValue(":NBR_ABSENCE",QString::number(NBR_ABSENCE));
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
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("GENDER"));
    return  model;
}


bool personnel::modifierP()
{
    QSqlQuery query;
        query.prepare("UPDATE PERSONNEL SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, EMAIL=:EMAIL,GENDER=:GENDER, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE, NBR_ABSENCE=:NBR_ABSENCE WHERE CIN=:CIN ");
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":ADRESSE", ADRESSE);
        query.bindValue(":EMAIL", EMAIL);
        query.bindValue(":GENDER", GENDER);
        query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
        query.bindValue(":NBR_ABSENCE", NBR_ABSENCE);
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
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("GENDER"));
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
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}

QSqlQueryModel * personnel::tri_email()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from PERSONNEL order by EMAIL ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}

QSqlQueryModel * personnel::NBR__ABSENCE()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("SELECT * from PERSONNEL order by NBR_ABSENCE");
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
return model;
QSqlQuery query;


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
void personnel::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void personnel::cherchecin(QTableView *table, int x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from PERSONNEL where regexp_like(CIN,:CIN);");
    query->bindValue(":CIN",x);
    if(x==0)
    {
        query->prepare("select * from PERSONNEL;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
void personnel::cherchenom(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from PERSONNEL where regexp_like(NOM,:NOM);");
   query->bindValue(":NOM",x);
   if(x==0)
   {
       query->prepare("select * from PERSONNEL;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
QSqlQueryModel * personnel::employe_du_mois()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from PERSONNEL order by NBR_ABSENCE   TOP 1");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
//    QSqlQueryModel *model=new QSqlQueryModel();
//    QSqlQuery *query =new QSqlQuery;

//    model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));
//    query->prepare("select * from PERSONNEL where regexp_like(NBR_ABSENCE,:NBR_ABSENCE);");
//    query->bindValue(":NBR_ABSENCE",x);
//    if(x==0)
//    {
//        query->prepare("select * from PERSONNEL;");
//    }
//    query->exec();
//    model->setQuery(*query);
//    table->setModel(model);
//    table->show();
}

void personnel::employe_mois()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("NBR_ABSENCE"));

    QSqlQuery query;

}

