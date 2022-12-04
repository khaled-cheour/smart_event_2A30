#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locaux.h"
#include "dialog_map.h"
#include <QDoubleValidator>
#include <QPushButton>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QPainter>
#include "dialog_stats.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Prix->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_NbPlaces->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_Nomloc->setModel(L.afficher_nom());
    ui->tab_Locals->setModel (L.afficher());
    L.write(L.time(),"App started");
    ui->textBrowser_local->setText(L.read());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_AjouterP_clicked()
{
    QString NOM=ui->lineEdit_NomLocal->text();
    QString ADRESSE=ui->lineEdit_AdresseLocal->text();
    QString SUPERFICIE=ui->LineEdit_Superficie->text();
    int NPLACES=ui->lineEdit_NbPlaces->text().toInt();
    int PRIX=ui->lineEdit_Prix->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->text();
    locaux L(NOM,ADRESSE,SUPERFICIE,NPLACES,PRIX,DESCRIPTION);
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

void MainWindow::on_pB_ModifierP_clicked()
{
    QString NOM=ui->lineEdit_NomLocal->text();
    QString ADRESSE=ui->lineEdit_AdresseLocal->text();
    QString SUPERFICIE=ui->LineEdit_Superficie->text();
    int NPLACES=ui->lineEdit_NbPlaces->text().toInt();
    int PRIX=ui->lineEdit_Prix->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->text();
    locaux L(NOM,ADRESSE,SUPERFICIE,NPLACES,PRIX,DESCRIPTION);
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

void MainWindow::on_pB_SupprimerP_clicked()
{
    locaux PL;
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

void MainWindow::on_pB_TirerParNbPlaces_clicked()
{
    ui->label_Info->setText("Tri par Nbr Places effectué");
    ui->tab_Locals->setModel(L.tri_NbPlace());
}

void MainWindow::on_pB_TireParPrix_clicked()
{
    ui->label_Info->setText("Tri par Prix effectué");
    ui->tab_Locals->setModel(L.tri_Prix());
}

void MainWindow::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Locals->setModel(L.tri_Nom());
}

void MainWindow::on_pushButton_SupprimerL_clicked()
{
    L.clearh();
    ui->textBrowser_local->setText(L.read());
}

void MainWindow::on_comboBox_Nomloc_currentIndexChanged(int)
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

void MainWindow::on_pushButton_Fermer_clicked()
{
    close();
}

void MainWindow::on_pushButton_Stats_clicked()
{
    Dialog_stats stats;
    stats.setModal(true);
    stats.exec();
}

void MainWindow::on_pushButton_map_clicked()
{
    Dialog_map map;
    map.setModal(true);
    map.exec();
}

void MainWindow::on_pushButton_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/chikh/Desktop/GestionDesLocaux/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/chikh/Desktop/GestionDesLocaux/Liste.pdf"));
    painter.drawText(3000,1500,"LISTE DES LOCAUX");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    //painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ADRESSE");
    painter.drawText(2300,3300,"NOM");
    painter.drawText(4300,3300,"SUPERFICIE");
    painter.drawText(6300,3300,"PRIX");
    painter.drawText(8000,3300,"NBR PLACES");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from LOCAUX");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        painter.drawText(10000,i,query.value(5).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/chikh/Desktop/GestionDesLocaux/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_pB_Recherh_clicked()
{
    locaux L;
    QString text;

    if (ui->radioButton->isChecked()==true)
    {
        L.clearTable(ui->tab_Locals);
            QString NOM=ui->lineEdit_AdresseLocal_2->text();
            L.chercheNom(ui->tab_Locals,NOM);
    }
    if (ui->radioButton_2->isChecked()==true)
    {
        L.clearTable(ui->tab_Locals);
            QString adresse=ui->lineEdit_AdresseLocal_2->text();
            L.chercheAdresse(ui->tab_Locals,adresse);
    }
}
