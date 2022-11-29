#include "dialog_employe_du_mois.h"
#include "ui_dialog_employe_du_mois.h"
#include "personnel.h"
#include "dialog_perso.h"

Dialog_employe_du_mois::Dialog_employe_du_mois(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_employe_du_mois)
{
    ui->setupUi(this);
}

Dialog_employe_du_mois::~Dialog_employe_du_mois()
{
    delete ui;
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
