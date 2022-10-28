#include "dialog_locaux.h"
#include "ui_dialog_locaux.h"
#include "connexion.h"
#include "local.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include "dialog_menu.h"
#include <QPushButton>

Dialog_Locaux::Dialog_Locaux(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Locaux)
{
    ui->setupUi(this);
    ui->lineEdit_NomLocal->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_Nomloc->setModel(L.afficher_nom());
    ui->tab_Locals->setModel (L.afficher());
    L.write(L.time(),"App started");
    ui->textBrowser_local->setText(L.read());
}

Dialog_Locaux::~Dialog_Locaux()
{
    delete ui;
}

void Dialog_Locaux::on_pB_AjouterP_clicked()
{
    QString NOM=ui->lineEdit_NomLocal->text();
    QString ADRESSE=ui->lineEdit_AdresseLocal->text();
    QString SUPERFICIE=ui->LineEdit_Superficie->text();
    int NOMBRE_PLACES=ui->lineEdit_NbPlaces->text().toInt();
    int PRIX=ui->lineEdit_Prix->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->text();
    local L(NOM,ADRESSE,SUPERFICIE,NOMBRE_PLACES,PRIX,DESCRIPTION);
    bool test=L.AjouterL();
    if(test)
    {
        ui->label_Info->setText("Ajout effectué");
        ui->comboBox_Nomloc->setModel(L.afficher_nom());
        ui->tab_Locals->setModel(L.afficher());
        L.write(L.time(),"LOCAUX: ajout effectué");
        ui->textBrowser_local->setText(L.read());
    }
    else
    {
        ui->label_Info->setText("Ajout non effectué");
    }
}


void Dialog_Locaux::on_pB_SupprimerP_clicked()
{
    local PL;
    L.setnom(ui->comboBox_Nomloc->currentText());
    bool test=L.SupprimerL(L.getnom());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tab_Locals->setModel(L.afficher());
        ui->comboBox_Nomloc->setModel(L.afficher_nom());
        L.write(L.time(),"LOCAUX: Supression effectuée");
        ui->textBrowser_local->setText(L.read());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void Dialog_Locaux::on_pB_ModifierP_clicked()
{
    QString NOM=ui->lineEdit_NomLocal->text();
    QString ADRESSE=ui->lineEdit_AdresseLocal->text();
    QString SUPERFICIE=ui->LineEdit_Superficie->text();
    int NOMBRE_PLACES=ui->lineEdit_NbPlaces->text().toInt();
    int PRIX=ui->lineEdit_Prix->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->text();
    local L(NOM,ADRESSE,SUPERFICIE,NOMBRE_PLACES,PRIX,DESCRIPTION);
    bool test=L.ModifierL();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_Locals->setModel(L.afficher());
        ui->comboBox_Nomloc->setModel(L.afficher_nom());
        L.write(L.time(),"LOCAUX: Modification effectuée");
        ui->textBrowser_local->setText(L.read());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void Dialog_Locaux::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Locals->setModel(L.tri_Nom());
}

void Dialog_Locaux::on_pB_TireParPrix_clicked()
{
    ui->label_Info->setText("Tri par Prix effectué");
    ui->tab_Locals->setModel(L.tri_Prix());
}

void Dialog_Locaux::on_pB_TirerParNbPlaces_clicked()
{
    ui->label_Info->setText("Tri par Nbr Places effectué");
    ui->tab_Locals->setModel(L.tri_NbPlace());
}

void Dialog_Locaux::on_pushButton_SupprimerL_clicked()
{
    L.clearh();
    ui->textBrowser_local->setText(L.read());
}

void Dialog_Locaux::on_comboBox_Nomloc_currentIndexChanged(int)
{
    QString nom=ui->comboBox_Nomloc->currentText();
    QString nom_1=QString::const_reference(nom);
    QSqlQuery query;
    query.prepare("SELECT * FROM LOCAUX where NOM='"+nom_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_NomLocal->setText(query.value(0).toString()) ;
            ui->lineEdit_AdresseLocal->setText(query.value(1).toString()) ;
            ui->LineEdit_Superficie->setText(query.value(2).toString()) ;
            ui->lineEdit_NbPlaces->setText(query.value(3).toString()) ;
            ui->lineEdit_Prix->setText(query.value(4).toString()) ;
            ui->lineEdit_Description->setText(query.value(5).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Dialog_Locaux::on_pushButton_Fermer_clicked()
{
    this->close();
    Dialog_menu menu;
    menu.setModal(true);
    menu.exec();
}
