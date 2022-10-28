#include "dialog_menu.h"
#include "ui_dialog_menu.h"

Dialog_menu::Dialog_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_menu)
{
    ui->setupUi(this);
}

Dialog_menu::~Dialog_menu()
{
    delete ui;
}

void Dialog_menu::on_pushButton_GestionPersonnelsMain_clicked()
{
    this->hide();
    Dialog_perso personnel;
    personnel.setModal(true);
    personnel.exec();
}

void Dialog_menu::on_pushButton_GestionEvenementsMain_clicked()
{
    this->hide();
    Dialog_event evenement;
    evenement.setModal(true);
    evenement.exec();
}

void Dialog_menu::on_pushButton_GestionFournisseurMain_clicked()
{
    this->hide();
    Dialog_Fourni fournisseur;
    fournisseur.setModal(true);
    fournisseur.exec();
}

void Dialog_menu::on_pushButton_GestionLocauxMain_clicked()
{
    this->hide();
    Dialog_Locaux locaux;
    locaux.setModal(true);
    locaux.exec();
}

void Dialog_menu::on_pushButton_GestionSponsorsMain_clicked()
{
    this->hide();
    Dialog_sponso sponsoring;
    sponsoring.setModal(true);
    sponsoring.exec();
}

void Dialog_menu::on_pushButton_QuitterMain_clicked()
{
    close();
}
