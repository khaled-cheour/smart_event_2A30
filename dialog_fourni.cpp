#include "dialog_fourni.h"
#include "ui_dialog_fourni.h"
#include "fournisseur.h"
#include "login_bd.h"
#include "connexion.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include "dialog_menu.h"

Dialog_Fourni::Dialog_Fourni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Fourni)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_ID->setModel(F.afficher_id());
    ui->tab_Fournisseur->setModel (F.afficher());
    F.write(F.time(),"App started");
    ui->text_Fournisseur->setText(F.read());
}

Dialog_Fourni::~Dialog_Fourni()
{
    delete ui;
}

void Dialog_Fourni::on_pB_AjouterF_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->LineEdit_Prenom->text();
    QString EMAIL=ui->lineEdit_Email->text();
    QString TYPE_MATERIEL=ui->lineEdit_TypeM->text();
    fournisseur F(ID,NOM,PRENOM,EMAIL,TYPE_MATERIEL);
    bool test=F.AjouterF();
    if(test)
    {
        ui->label_Info->setText("Ajout Effectué");
        ui->comboBox_ID->setModel(F.afficher_id());
        ui->tab_Fournisseur->setModel(F.afficher());
        F.write(F.time(),"FOURNISSEUR: Ajout effectué");
        ui->text_Fournisseur->setText(F.read());
    }
    else
    {
        ui->label_Info->setText("Ajout non Effectué");
    }
}

void Dialog_Fourni::on_pB_SupprimerF_clicked()
{
    fournisseur F;
    F.setid(ui->comboBox_ID->currentText().toInt());
    bool test=F.SupprimerF(F.getid());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tab_Fournisseur->setModel(F.afficher());
        ui->comboBox_ID->setModel(F.afficher_id());
        F.write(F.time(),"FOURNISSEUR: Supression effectué");
        ui->text_Fournisseur->setText(F.read());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void Dialog_Fourni::on_pB_ModifierF_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->LineEdit_Prenom->text();
    QString EMAIL=ui->lineEdit_Email->text();
    QString TYPE_MATERIEL=ui->lineEdit_TypeM->text();
    fournisseur F(ID,NOM,PRENOM,EMAIL,TYPE_MATERIEL);
    bool test=F.ModifierF();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_Fournisseur->setModel(F.afficher());
        ui->comboBox_ID->setModel(F.afficher_id());
        F.write(F.time(),"FOURNISSEUR: Modification effectué");
        ui->text_Fournisseur->setText(F.read());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void Dialog_Fourni::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Fournisseur->setModel(F.tri_nom());
}

void Dialog_Fourni::on_pB_TirerParTypeM_clicked()
{
    ui->label_Info->setText("Tri par Type Materiel effectué");
    ui->tab_Fournisseur->setModel(F.tri_typem());
}

void Dialog_Fourni::on_pushButton_SupprimerF_clicked()
{
    F.clearh();
    ui->text_Fournisseur->setText(F.read());
}

void Dialog_Fourni::on_comboBox_ID_currentIndexChanged(int)
{
    int id=ui->comboBox_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISSEUR where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_ID->setText(query.value(0).toString()) ;
            ui->lineEdit_Nom->setText(query.value(1).toString()) ;
            ui->LineEdit_Prenom->setText(query.value(2).toString()) ;
            ui->lineEdit_Email->setText(query.value(3).toString()) ;
            ui->lineEdit_TypeM->setText(query.value(4).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Dialog_Fourni::on_pushButton_Fermer_clicked()
{
    this->close();
    Dialog_menu menu;
    menu.setModal(true);
    menu.exec();
}
