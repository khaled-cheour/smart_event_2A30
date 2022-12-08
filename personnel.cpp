#include "personnel.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QMessageBox>
#include "arduino.h"
#include "connexion.h"
personnel::personnel(){
    CIN=0;
    NOM=" ";
    PRENOM=" ";
    ADRESSE=" ";
    EMAIL=" ";
    GESTION=" ";
    GENDER=" ";
    DATE_DE_NAISSANCE=QDate();
    ABSANCE=0;
    PASSWORD=" ";
    RFID=" ";
    PHOTO=" ";
}
personnel::personnel(int CIN,QString NOM,QString PRENOM,QString GENDER,QDate DATE_DE_NAISSANCE,QString EMAIL,QString ADRESSE,QString GESTION,int ABSANCE,QString PASSWORD,QString RFID,QString PHOTO){
    this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->ADRESSE=ADRESSE;
    this->EMAIL=EMAIL;
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
    this->ABSANCE=ABSANCE;
    this->PASSWORD=PASSWORD;
    this->GENDER=GENDER;
    this->GESTION=GESTION;
    this->RFID=RFID;
    this->PHOTO=PHOTO;
}
/**************************************/
int personnel::getcin() {  return CIN; }
QString personnel::getnom() { return NOM; }
QString personnel::getprenom() { return PRENOM; }
QString personnel::getgender() { return GENDER; }
QDate personnel::getdate() { return DATE_DE_NAISSANCE; }
QString personnel::getemail() { return EMAIL; }
QString personnel::getadresse() { return ADRESSE; }
QString personnel::getgestion() { return GESTION; }
int personnel::getabsance() {  return ABSANCE; }
QString personnel::getrfid() { return RFID; }
QString personnel::getphoto() { return PHOTO; }
/**************************************/
void personnel::setcin(int CIN) { this->CIN=CIN; }
void personnel::setnom(QString NOM) { this->NOM=NOM; }
void personnel::setprenom(QString PRENOM) { this->PRENOM=PRENOM; }
void personnel::setgender(QString GENDER) { this->GENDER=GENDER; }
void personnel::setdate(QDate DATE_DE_NAISSANCE) { this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE; }
void personnel::setemail(QString EMAIL) { this->EMAIL=EMAIL; }
void personnel::setadresse(QString ADRESSE) { this->ADRESSE=ADRESSE; }
void personnel::setgestion(QString GESTION) { this->GESTION=GESTION; }
void personnel::setabsance(int ABSANCE) { this->ABSANCE=ABSANCE; }
void personnel::setrfid(QString RFID) { this->RFID=RFID; }
void personnel::setphoto(QString PHOTO) { this->PHOTO=PHOTO; }
/**************************************/
bool personnel::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(CIN);
    query.prepare("INSERT INTO PERSONNEL(CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,ABSANCE,PASSWORD,RFID,PHOTO)" "VALUES (:CIN,:NOM,:PRENOM,:GENDER,:DATE_DE_NAISSANCE,:EMAIL,:ADRESSE,:GESTION,:ABSANCE,:PASSWORD,:RFID,:PHOTO)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":GENDER", GENDER);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":GESTION", GESTION);
    query.bindValue(":ABSANCE", ABSANCE);
    query.bindValue(":PASSWORD", PASSWORD);
    query.bindValue(":RFID", RFID);
    query.bindValue(":PHOTO", PHOTO);
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
    model->setQuery("SELECT CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,ABSANCE,RFID,PHOTO FROM PERSONNEL");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ABSANCE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RFID"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("PHOTO"));
    return  model;
}
bool personnel::modifierP()
{
    QSqlQuery query;
    query.prepare("UPDATE PERSONNEL SET NOM=:NOM, PRENOM=:PRENOM, GENDER=:GENDER, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE, EMAIL=:EMAIL, ADRESSE=:ADRESSE, GESTION=:GESTION, ABSANCE=:ABSANCE, PASSWORD=:PASSWORD, RFID=:RFID, PHOTO=:PHOTO WHERE CIN=:CIN ");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":GENDER", GENDER);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":GESTION", GESTION);
    query.bindValue(":ABSANCE", ABSANCE);
    query.bindValue(":PASSWORD", PASSWORD);
    query.bindValue(":RFID", RFID);
    query.bindValue(":PHOTO", PHOTO);
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
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ABSANCE"));
    return model;
}
QSqlQueryModel * personnel::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * from PERSONNEL order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ABSANCE"));
    return model;
}
QSqlQueryModel * personnel::tri_email()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * from PERSONNEL order by EMAIL");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("ABSANCE"));
    return model;
}
QString personnel::read()
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Personnel.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void personnel::write(QString time, QString txt)
{
    QFile file("D:/Studies/SmartEventPlanner/Historique_Personnel.txt");
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
    QFile file("D:/Studies/SmartEventPlanner/Historique_Personnel.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void personnel::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void personnel::chercheCIN(QTableView *table, QString x)
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
void personnel::chercheNom(QTableView *table, QString x)
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
QSqlQueryModel* personnel::afficher_MDM()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GESTION,ABSANCE FROM PERSONNEL");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GESTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ABSANCE"));
    return  model;
}
QSqlQueryModel* personnel::triMDM()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GESTION,ABSANCE FROM EVENEMENT ORDER BY ABSANCE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GESTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ABSANCE"));
    return model;
}
