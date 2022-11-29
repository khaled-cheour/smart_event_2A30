#include "dialog_chat.h"
#include "ui_dialog_chat.h"
#include"personnel.h"

Dialog_chat::Dialog_chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_chat)
{
    personnel P;
    ui->setupUi(this);
    ui->lineEdit_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_CIN->setModel(P.afficher_cin());
   // ui->tableView_Personnel->setModel (P.afficher());
    P.write(P.time(),"App started");
}

Dialog_chat::~Dialog_chat()
{
    delete ui;
}
void Dialog_chat::choix_chat()
{
    personnel P;
  //  ui->tableView_Personnel->setModel(P.afficher());

}

void Dialog_chat::on_pushButton_envoyer_clicked()
{



}
