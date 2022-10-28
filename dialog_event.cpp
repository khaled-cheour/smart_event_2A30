#include "dialog_event.h"
#include "ui_dialog_event.h"
#include "evenement.h"
#include "login_bd.h"
#include "connexion.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include "dialog_menu.h"

Dialog_event::Dialog_event(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_event)
{
    ui->setupUi(this);
    ui->lineEdit_EventID->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_EventID->setModel(E.afficher_id());
    ui->tab_Events->setModel (E.afficher());
    E.write(E.time(),"App started");
    ui->text_Events->setText(E.read());
}

Dialog_event::~Dialog_event()
{
    delete ui;
}

void Dialog_event::on_pB_AjouterP_clicked()
{
    int ID=ui->lineEdit_EventID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString TYPE=ui->LineEdit_Type->text();
    QString LIEU=ui->lineEdit_Lieu->text();
    int NOMBRE_PERSONNES=ui->lineEdit_NbPersonnes->text().toInt();
    QDate DATE_E=ui->dateEdit_DateE->date();
    QTime TIME_E=ui->timeEdit_HeureE->time();
    evenement E(ID,NOM,TYPE,LIEU,NOMBRE_PERSONNES,DATE_E,TIME_E);
    bool test=E.AjouterE();
    if(test)
    {
        ui->label_Info->setText("Ajout Effectué");
        ui->comboBox_EventID->setModel(E.afficher_id());
        ui->tab_Events->setModel(E.afficher());
        E.write(E.time(),"EVENEMENT: Ajout effectué");
        ui->text_Events->setText(E.read());
    }
    else
    {
        ui->label_Info->setText("Ajout non effectué");
    }
}

void Dialog_event::on_pB_SupprimerP_clicked()
{
    evenement E;
    E.setid(ui->comboBox_EventID->currentText().toInt());
    bool test=E.SupprimerE(E.getid());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tab_Events->setModel(E.afficher());
        ui->comboBox_EventID->setModel(E.afficher_id());
        E.write(E.time(),"EVENEMENT: Supression effectuée");
        ui->text_Events->setText(E.read());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void Dialog_event::on_pB_ModifierP_clicked()
{
    int ID=ui->lineEdit_EventID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString TYPE=ui->LineEdit_Type->text();
    QString LIEU=ui->lineEdit_Lieu->text();
    int NOMBRE_PERSONNES=ui->lineEdit_NbPersonnes->text().toInt();
    QDate DATE_E=ui->dateEdit_DateE->date();
    QTime TIME_E=ui->timeEdit_HeureE->time();
    evenement E(ID,NOM,TYPE,LIEU,NOMBRE_PERSONNES,DATE_E,TIME_E);
    bool test=E.ModifierE();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_Events->setModel(E.afficher());
        ui->comboBox_EventID->setModel(E.afficher_id());
        E.write(E.time(),"EVENEMENT: Modification Effectuée");
        ui->text_Events->setText(E.read());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void Dialog_event::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Events->setModel(E.tri_nom());
}

void Dialog_event::on_pB_TireParType_clicked()
{
    ui->label_Info->setText("Tri par Type effectué");
    ui->tab_Events->setModel(E.tri_type());
}

void Dialog_event::on_pB_TirerParNbPersonnes_clicked()
{
    ui->label_Info->setText("Tri par Nbr Personnes effectué");
    ui->tab_Events->setModel(E.tri_nbrpersonnes());
}

void Dialog_event::on_pushButton_SupprimerE_clicked()
{
    E.clearh();
    ui->text_Events->setText(E.read());
}

void Dialog_event::on_comboBox_Nomloc_currentIndexChanged(int)
{
    int id=ui->comboBox_EventID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM EVENEMENT where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_EventID->setText(query.value(0).toString());
            ui->lineEdit_Nom->setText(query.value(1).toString());
            ui->LineEdit_Type->setText(query.value(2).toString());
            ui->lineEdit_Lieu->setText(query.value(3).toString());
            ui->lineEdit_NbPersonnes->setText(query.value(4).toString()) ;
            ui->dateEdit_DateE->setDate(query.value(5).toDate()) ;
            ui->timeEdit_HeureE->setTime(query.value(6).toTime()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Dialog_event::on_pushButton_Fermer_clicked()
{
    this->close();
    Dialog_menu menu;
    menu.setModal(true);
    menu.exec();
}
