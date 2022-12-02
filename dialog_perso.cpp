#include "dialog_perso.h"
#include "ui_dialog_perso.h"
#include "personnel.h"
#include "connexion.h"
#include "dialog_stats.h"
#include "dialog_chat.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QFileDialog>
#include <QPushButton>
#include "arduino.h"

Dialog_perso::Dialog_perso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_perso)
{
    arduino a;
    ui->setupUi(this);
    ui->lineEdit_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_CIN->setModel(P.afficher_cin());
    ui->tableView_Personnel->setModel (P.afficher());
    P.write(P.time(),"App started");
    ui->textBrowser_Perso->setText(P.read());

    int ret=a.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
    break;
    case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
    break;
    case(-1):qDebug()<<"arduino is not available";
    }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

Dialog_perso::~Dialog_perso()
{
    delete ui;
}

void Dialog_perso::on_pB_AjouterP_clicked()
{

    int CIN=ui->lineEdit_CIN->text().toInt();
    int NBR_ABSENCE=ui->lineEdit_NBR_ABSENCE->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    QString ADRESSE=ui->lineEdit_Adresse->text();
    QString EMAIL=ui->lineEdit_Email->text();
    QString GENDER;
    if (ui->rb_homme->isChecked())
    {
        GENDER="Homme";
    }
    if (ui->rb_femme->isChecked())
    {
        GENDER="Femme";
    }
    if (ui->rb_autre->isChecked())
    {
        GENDER="Autre";
    }
    QDate DATE_DE_NAISSANCE=ui->dateEdit_DateDeNaissance->date();
    int CIN_DIRIGEUR = 0;
    personnel p(CIN,NOM,PRENOM,ADRESSE,EMAIL,GENDER,DATE_DE_NAISSANCE,CIN_DIRIGEUR,NBR_ABSENCE);
    bool test=p.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBox_CIN->setModel(p.afficher_cin());
        ui->tableView_Personnel->setModel(p.afficher());
        p.write(p.time(),"ajout d'un personnel est effectué");
        ui->textBrowser_Perso->setText(p.read());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Ajout non effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Dialog_perso::on_pB_SupprimerP_clicked()
{
    personnel P;
    P.setcin(ui->comboBox_CIN->currentText().toInt());
    bool test=P.supprimer(P.getcin());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
   ui->tableView_Personnel->setModel(P.afficher());
   ui->comboBox_CIN->setModel(P.afficher_cin());
   P.write(P.time(),"supression d'un personnel est effectuée");
   ui->textBrowser_Perso->setText(P.read());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Suppression non effectué.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void Dialog_perso::on_pB_pdf_clicked()
{




             ///////////////////////////////

                 QPdfWriter pdf("C:/Users/User/Desktop/ProjetCPP/liste_personnel.pdf");

                 QPainter painter(&pdf);

                 int i = 4000;
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Arial", 30));
                 painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/User/Desktop/ProjetCPP/logo.png"));
                 painter.drawText(3000,1500,"LISTE DES EMPLOYES");
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Arial", 50));
                 painter.drawRect(2700,200,6300,2600);
                 painter.drawRect(0,3000,9600,500);
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Arial", 9));
                 painter.drawText(300,3300,"CIN");
                 painter.drawText(1500,3300,"NOM");
                 painter.drawText(2500,3300,"PRENOM");
                 painter.drawText(3900,3300,"ADRESS");
                 painter.drawText(5000,3300,"EMAIL");
                 painter.drawText(6000,3300,"DATE_DE_NAISSANCE");
                 painter.drawText(8000,3300,"NBR_ABSENCE");
                 QSqlQuery query;
                 query.prepare("<SELECT CAST( PERSONNEL() AS Date ) ");
                 time_t tt;
                 struct tm* ti;
                 time(&tt);
                 ti=localtime(&tt);
                 asctime(ti);
                 painter.drawText(500,300, asctime(ti));
                 query.prepare("select * from PERSONNEL");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1500,i,query.value(1).toString());
                     painter.drawText(2500,i,query.value(2).toString());
                     painter.drawText(3900,i,query.value(3).toString());
                     painter.drawText(5000,i,query.value(4).toString());
                     painter.drawText(6400,i,query.value(5).toString());
                     painter.drawText(9000,i,query.value(7).toString());
                     i = i +500;
                 }

                 int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                 if (reponse == QMessageBox::Yes)
                 {
                     QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/User/Desktop/ProjetCPP/liste_personnel.pdf"));

                     painter.end();
                 }
                 if (reponse == QMessageBox::No)
                 {
                     painter.end();
                 }

}


void Dialog_perso::on_pB_ModifierP_clicked()
{
    int CIN=ui->lineEdit_CIN->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    QString ADRESSE=ui->lineEdit_Adresse->text();
    QString EMAIL=ui->lineEdit_Email->text();
    QString GENDER;
    if (ui->rb_homme->isChecked())
    {
        GENDER="Homme";
    }
    if (ui->rb_femme->isChecked())
    {
        GENDER="Femme";
    }
    if (ui->rb_autre->isChecked())
    {
        GENDER="Autre";
    }
    QDate DATE_DE_NAISSANCE=ui->dateEdit_DateDeNaissance->date();
    int NBR_ABSENCE=ui->lineEdit_NBR_ABSENCE ->text().toInt();
    int CIN_DIRIGEUR = 0;
    personnel P(CIN,NOM,PRENOM,ADRESSE,EMAIL,GENDER,DATE_DE_NAISSANCE,CIN_DIRIGEUR,NBR_ABSENCE);
    bool test=P.modifierP();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Modification effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_Personnel->setModel(P.afficher());
        ui->comboBox_CIN->setModel(P.afficher_cin());
        P.write(P.time(),"PERSONNEL: Modification effectuée");
        ui->textBrowser_Perso->setText(P.read());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Modification non effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void Dialog_perso::on_pushButton_InsererPhotoPerso_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
    if (QString::compare(filename,QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->label_imageperso->width(), Qt::SmoothTransformation);
                    ui->label_imageperso->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //ERROR HANDLING
        }
    }
}

void Dialog_perso::on_pB_TireParCIN_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                             QObject::tr("tri effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_Personnel->setModel(P.tri_cin());
}

void Dialog_perso::on_pB_TirerParNom_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                             QObject::tr("tri effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_Personnel->setModel(P.tri_nom());
}

void Dialog_perso::on_pB_TirerParEmail_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                             QObject::tr("tri effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_Personnel->setModel(P.tri_email());
}
void Dialog_perso::on_pushButton_employe_de_mois_clicked()
{
    personnel p;
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                             QObject::tr("employe du mois  effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_Personnel_2->setModel(P.NBR__ABSENCE());
    QSqlQuery query;
    qDebug()<<query.prepare("SELECT * FROM PERSONNEL ");
    query.last();
    ui->lineEdit_NBR_ABSENCE->setText( query.value(7).toString());
}


void Dialog_perso::on_pushButton_SupprimerP_clicked()
{
    P.clearh();
    ui->textBrowser_Perso->setText(P.read());
}

void Dialog_perso::on_pushButton_Fermer_clicked()
{
    close();
}

void Dialog_perso::on_comboBox_CIN_currentIndexChanged(int)
{
    int cin=ui->comboBox_CIN->currentText().toInt();
         QString cin_1=QString::number(cin);
        QSqlQuery query;
        query.prepare("SELECT * FROM PERSONNEL where CIN='"+cin_1+"'");
        if(query.exec())
        {
            while (query.next())
            {
              ui->lineEdit_CIN->setText(query.value(0).toString()) ;
              ui->lineEdit_Nom->setText(query.value(1).toString()) ;
              ui->lineEdit_Prenom->setText(query.value(2).toString()) ;
              ui->lineEdit_Adresse->setText(query.value(3).toString()) ;
              ui->lineEdit_Email->setText(query.value(4).toString()) ;
              ui->dateEdit_DateDeNaissance->setDate(query.value(5).toDate()) ;
              ui->lineEdit_NBR_ABSENCE->setText(query.value(7).toString());
              QString GENDER;
              if (ui->rb_homme->isChecked())
              {
                  GENDER="Homme";
              }
              if (ui->rb_femme->isChecked())
              {
                  GENDER="Femme";
              }
              if (ui->rb_autre->isChecked())
              {
                  GENDER="Autre";
              }
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                                  QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void Dialog_perso::on_pushButton_recherche_clicked()
{
    personnel p;
    QString text;

    if (ui->rb_cin->isChecked()==true)
    {
        p.clearTable(ui->tableView_Personnel);
            int cin=ui->lineEdit_IDRecherche->text().toInt();
            p.cherchecin(ui->tableView_Personnel,cin);
    }
    if (ui->rb_nom->isChecked()==true)
    {
        p.clearTable(ui->tableView_Personnel);
           QString  nom=ui->lineEdit_IDRecherche->text();
            p.cherchenom(ui->tableView_Personnel,nom);
    }
}



void Dialog_perso::on_pushButton_PorteP_4_clicked()
{
    this->hide();
    DS = new Dialog_stats();
     DS->setWindowTitle("Statistique");
     DS->choix_pie();
     DS->show();
}

void Dialog_perso::on_pushButton_chatbox_clicked()
{
    this->hide();
    DC = new Dialog_chat();
     DC->setWindowTitle("ChatBox");
     DC->choix_chat();
     DC->show();
}




void Dialog_perso::on_pushButton_clicked()
{
    arduino a;
    a.write_to_arduino("1");
}
