#include "dialog_sponso.h"
#include "ui_dialog_sponso.h"
#include "sponsoring.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include "dialog_menu.h"


Dialog_sponso::Dialog_sponso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_sponso)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_ID->setModel(S.afficher_id());
    S.write(S.time(),"App started");
    ui->tab_Spornors->setModel (S.afficher());
}

Dialog_sponso::~Dialog_sponso()
{
    delete ui;
}

void Dialog_sponso::on_pB_Ajouter_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    int NUM_TEL=ui->lineEdit_NumTel->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->text();
    sponsoring S(ID,NUM_TEL,DESCRIPTION);
    bool test=S.ajouterS();
    if(test)
    {
        ui->label_Info->setText("Ajout effectué");
        ui->comboBox_ID->setModel(S.afficher_id());
        ui->tab_Spornors->setModel(S.afficher());
        S.write(S.time(),"SPONSORING: Ajout effectué");
        ui->textBrowser_Sponso->setText(S.read());
    }
    else
    {
        ui->label_Info->setText("Ajout non effectué");
    }
}

void Dialog_sponso::on_pB_Supprimer_clicked()
{
    sponsoring S;
    S.setid(ui->comboBox_ID->currentText().toInt());
    bool test=S.supprimerS(S.getid());
    if(test)
    {
        ui->label_Info->setText("Suppression non effectué");
        ui->tab_Spornors->setModel(S.afficher());
        ui->comboBox_ID->setModel(S.afficher_id());
        S.write(S.time(),"SPONSORING: Suppression effectué");
        ui->textBrowser_Sponso->setText(S.read());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void Dialog_sponso::on_pB_Modifier_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    int NUM_TEL=ui->lineEdit_NumTel->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->text();
    sponsoring S(ID,NUM_TEL,DESCRIPTION);
    bool test=S.modifierS();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_Spornors->setModel(S.afficher());
        ui->comboBox_ID->setModel(S.afficher_id());
        S.write(S.time(),"SPONSORING: Modification effectué");
        ui->textBrowser_Sponso->setText(S.read());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void Dialog_sponso::on_pB_TirerParID_clicked()
{
    ui->label_Info->setText("Tri par ID effectué");
    ui->tab_Spornors->setModel(S.tri_id());
}

void Dialog_sponso::on_pB_TirerParNumtel_clicked()
{
    ui->label_Info->setText("Tri par Num Tel effectué");
    ui->tab_Spornors->setModel(S.tri_numtel());
}

void Dialog_sponso::on_pushButton_SupprimerS_clicked()
{
    S.clearh();
    ui->textBrowser_Sponso->setText(S.read());
}

void Dialog_sponso::on_comboBox_ID_currentIndexChanged(int)
{
    int id=ui->comboBox_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORING where CIN='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_ID->setText(query.value(0).toString()) ;
            ui->lineEdit_NumTel->setText(query.value(1).toString()) ;
            ui->lineEdit_Description->setText(query.value(2).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Dialog_sponso::on_pushButton_Fermer_clicked()
{
    Dialog_menu menu;
    menu.setModal(true);
    menu.exec();
}
