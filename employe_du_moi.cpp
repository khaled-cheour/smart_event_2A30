#include "employe_du_moi.h"
#include "ui_employe_du_moi.h"
#include "personnel.h"
#include <QSqlQuery>

employe_du_moi::employe_du_moi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employe_du_moi)
{
    ui->setupUi(this);
    employe_moi();
}

employe_du_moi::~employe_du_moi()
{
    delete ui;
}
void employe_du_moi::employe_moi()
{
    personnel p;
    bool test=p.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);

        ui->tableView_Personnel2->setModel(p.afficher());
        p.write(p.time(),"ajout d'un personnel est effectué");
        ui->textBrowser_Personnel2->setText(p.read());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Ajout non effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    QDialog *diag=new employe_du_moi();
    diag->show();
    QSqlQuery query;
    qDebug()<<query.prepare("SELECT * FROM PERSONNEL ");
    query.first();

  /*ui->lineEdit_NBR_PRESENCE->setText( query.value(7).toString());*/

}
