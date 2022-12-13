#include "evenement.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QTime>
evenement::evenement()
{
        ID=0;
        NOM=" ";
        TYPE=" ";
        LIEU=" ";
        NOMBRE_PERSONNES=0;
        DATE_E=QDate();
        TIME_E=QTime();
        PRIX_F=0;
        PRIX_L=0;
        FACTURATION=0;
}
evenement::evenement(int ID, QString NOM, QString TYPE,QString LIEU,int NOMBRE_PERSONNES, QDate DATE_E, QTime TIME_E, int PRIX_F, int PRIX_L,int FACTURATION){
    this->ID=ID;
    this->NOM=NOM;
    this->TYPE=TYPE;
    this->LIEU=LIEU;
    this->NOMBRE_PERSONNES=NOMBRE_PERSONNES;
    this->DATE_E=DATE_E;
    this->TIME_E=TIME_E;
    this->PRIX_F=PRIX_F;
    this->PRIX_L=PRIX_L;
    this->FACTURATION=FACTURATION;
}
/**************************************/
int evenement::getid(){return ID;}
QString evenement::getnom(){return NOM;}
QString evenement::gettype(){return TYPE;}
QString evenement::getlieu(){return LIEU;}
int evenement::getnbrpersonnes(){return NOMBRE_PERSONNES;}
QDate evenement::getdate(){return DATE_E;}
QTime evenement::gettime(){return TIME_E;}
int evenement::getprix_f(){return PRIX_F;}
int evenement::getprix_l(){return PRIX_L;}
int evenement::getfact(){return FACTURATION;}
/**************************************/
void evenement::setid(int ID){this->ID=ID;}
void evenement::setnom(QString NOM){this->NOM=NOM;}
void evenement::settype(QString TYPE){this->TYPE=TYPE;}
void evenement::setlieu(QString LIEU){this->LIEU=LIEU;}
void evenement::setnbrpersonnes(int NOMBRE_PERSONNES){this->NOMBRE_PERSONNES=NOMBRE_PERSONNES;}
void evenement::setdate(QDate DATE_E){this->DATE_E=DATE_E;}
void evenement::settime(QTime TIME_E){this->TIME_E=TIME_E;}
void evenement::setprix_f(int PRIX_F){this->PRIX_F=PRIX_F;}
void evenement::setprix_l(int PRIX_L){this->PRIX_L=PRIX_L;}
void evenement::setfact(int FACTURATION){this->FACTURATION=FACTURATION;}
/**************************************/
bool evenement::AjouterE(){
    QSqlQuery query;
    QString id_string=QString::number(ID);
         query.prepare("INSERT INTO EVENEMENT(ID,NOM,TYPE,LIEU,NOMBRE_PERSONNES,DATE_E,TIME_E,PRIX_F,PRIX_L,FACTURATION)" "VALUES (:ID,:NOM,:TYPE,:LIEU,:NOMBRE_PERSONNES,:DATE_E,:TIME_E,:PRIX_F,:PRIX_L,:FACTURATION)");
         query.bindValue(":ID", ID);
         query.bindValue(":NOM", NOM);
         query.bindValue(":TYPE", TYPE);
         query.bindValue(":LIEU", LIEU);
         query.bindValue(":NOMBRE_PERSONNES", NOMBRE_PERSONNES);
         query.bindValue(":DATE_E", DATE_E);
         query.bindValue(":TIME_E", TIME_E);
         query.bindValue(":PRIX_F", PRIX_F);
         query.bindValue(":PRIX_L", PRIX_L);
         query.bindValue(":FACTURATION", FACTURATION);
    return query.exec();
}
bool evenement::SupprimerE(int ID){
    QSqlQuery query;
         query.prepare("DELETE FROM EVENEMENT where ID= :ID");
         query.bindValue(0, ID);
    return query.exec();
}
bool evenement::ModifierE()
{
    QSqlQuery query;
        query.prepare("UPDATE EVENEMENT SET NOM=:NOM, TYPE=:TYPE, LIEU=:LIEU, NOMBRE_PERSONNES=:NOMBRE_PERSONNES, DATE_E=:DATE_E, TIME_E=:TIME_E, PRIX_L=:PRIX_L, PRIX_F=:PRIX_F, FACTURATION=:FACTURATION WHERE ID=:ID");
        query.bindValue(":ID", ID);
        query.bindValue(":NOM", NOM);
        query.bindValue(":TYPE", TYPE);
        query.bindValue(":LIEU", LIEU);
        query.bindValue(":NOMBRE_PERSONNES", NOMBRE_PERSONNES);
        query.bindValue(":DATE_E", DATE_E);
        query.bindValue(":TIME_E", TIME_E);
        query.bindValue(":PRIX_F", PRIX_F);
        query.bindValue(":PRIX_L", PRIX_L);
        query.bindValue(":FACTURATION", FACTURATION);
    return query.exec();
}
/**************************************/
QSqlQueryModel* evenement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EVENEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE_PERSONNES"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_E"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("TIME_E"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_F"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_L"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("FACTURATION"));
    return  model;
}
QSqlQueryModel* evenement::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT ID from EVENEMENT");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return model;
}
/**************************************/
QSqlQueryModel * evenement::tri_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from EVENEMENT order by ID");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE_PERSONNES"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_E"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("TIME_E"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_F"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_L"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("FACTURATION"));
    return model;
}
QSqlQueryModel * evenement::tri_type()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from EVENEMENT order by TYPE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE_PERSONNES"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_E"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("TIME_E"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_F"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_L"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("FACTURATION"));
    return model;
}
QSqlQueryModel * evenement::tri_nbrpersonnes()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from EVENEMENT order by NOMBRE_PERSONNES");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE_PERSONNES"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_E"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("TIME_E"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_F"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRIX_L"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("FACTURATION"));
    return model;
}

QSqlQueryModel * evenement::tri_date()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from EVENEMENT order by DATE_E");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    return model;
}
/**************************************/
QString evenement::read()
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Evenement.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void evenement::write(QString time, QString txt)
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Evenement.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString evenement::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void evenement::clearh()
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Evenement.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void evenement::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void evenement::chercheID(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from EVENEMENT where regexp_like(ID,:ID);");
   query->bindValue(":ID",x);
   if(x==0)
   {
       query->prepare("select * from EVENEMENT;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void evenement::chercheNom(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from EVENEMENT where regexp_like(NOM,:NOM);");
    query->bindValue(":NOM",x);
    if(x==0)
    {
        query->prepare("select * from EVENEMENT;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
QSqlQueryModel* evenement::afficher1()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT ID,DATE_E FROM EVENEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_E"));

    return model;
}
QSqlQueryModel* evenement::triasc()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT ID,DATE_E FROM EVENEMENT ORDER BY ID ASC");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_E"));

    return model;
}
QSqlQueryModel* evenement::tridesc()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT ID,DATE_E FROM EVENEMENT ORDER BY ID DESC");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_E"));

    return model;
}
