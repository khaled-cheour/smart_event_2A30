#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPdfWriter>
#include <QIntValidator>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include <QRadioButton>
#include <dialog_stats.h>
#include <dialog_mailing.h>
#include<QObject>
#include <QMessageBox>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QTextDocument>
#include <QImage>
#include <QPixmap>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QPlainTextEdit>
#include <QPrintDialog>
#include <QSystemTrayIcon>
#include <QDateEdit>
#include <QDate>
#include <QDateTime>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"Arduino is available and connected:"<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"Arduino is available and not connected to:"<<A.getarduino_port_name();
            break;
    case(-1):qDebug()<<"Arduino is not available:";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    ui->lineEdit_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_ID->setModel(F.afficher_id());
    ui->tab_Fournisseur->setModel (F.afficher());
    F.write(F.time(),"App started");
    ui->text_Fournisseur->setText(F.read());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_AjouterF_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->LineEdit_Prenom->text();
    QString EMAIL=ui->lineEdit_Email->text();
    QString TYPE_MATERIEL=ui->lineEdit_TypeM->text();
    QString img=ui->image->text();

    int PRIX=ui->lineEdit_PrixM->text().toInt();
    fournisseur F(ID,NOM,PRENOM,EMAIL,TYPE_MATERIEL,PRIX,img);
    bool test=F.AjouterF();
    if(test)
    {A.write_to_arduino("1");
        ui->label_Info->setText("Ajout Effectué");
        ui->comboBox_ID->setModel(F.afficher_id());
        ui->tab_Fournisseur->setModel(F.afficher());
        F.write(F.time(),"FOURNISSEUR: Ajout effectué");
        ui->text_Fournisseur->setText(F.read());
    }
    else
    {A.write_to_arduino("0");
        ui->label_Info->setText("Ajout non Effectué");
    }
}

void MainWindow::on_pB_SupprimerF_clicked()
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

void MainWindow::on_pB_ModifierF_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->LineEdit_Prenom->text();
    QString EMAIL=ui->lineEdit_Email->text();
    QString TYPE_MATERIEL=ui->lineEdit_TypeM->text();
    int PRIX=ui->lineEdit_PrixM->text().toInt();
    QString img=ui->img_name->text();
    fournisseur F(ID,NOM,PRENOM,EMAIL,TYPE_MATERIEL,PRIX,img);
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

void MainWindow::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Fournisseur->setModel(F.tri_nom());
}

void MainWindow::on_pB_TirerParTypeM_clicked()
{
    ui->label_Info->setText("Tri par Type Materiel effectué");
    ui->tab_Fournisseur->setModel(F.tri_typem());
}

void MainWindow::on_pushButton_SupprimerF_clicked()
{
    F.clearh();
    ui->text_Fournisseur->setText(F.read());
}

void MainWindow::on_comboBox_ID_currentIndexChanged(int)
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
            ui->lineEdit_PrixM->setText(query.value(5).toString()) ;
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

void MainWindow::on_pB_TirerParTypeM_2_clicked()
{
    QPdfWriter pdf("C:/Users/Lina Cherif/Desktop/GestionDesFournisseurs/liste.pdf");

              QPainter painter(&pdf);

              int i = 4000;
              painter.setPen(Qt::black);
              painter.setFont(QFont("Arial", 30));
              painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/Lina Cherif/Desktop/GestionDesFournisseurs/Liste.pdf"));
              painter.drawText(3000,1500,"LISTE DES FOURNISSEUR");
              painter.setPen(Qt::blue);
              painter.setFont(QFont("Arial", 50));
              painter.drawRect(2700,200,6300,2600);
              painter.drawRect(0,3000,9600,500);
              painter.setPen(Qt::black);
              painter.setFont(QFont("Arial", 9));
              painter.drawText(300,3300,"ID");
              painter.drawText(2300,3300,"NOM");
              painter.drawText(3600,3300,"PRENOM");
              painter.drawText(5000,3300,"EMAIL");
              painter.drawText(7300,3300,"TYPE");
              painter.drawText(9300,3300,"PRIX");
              QSqlQuery query;
              query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
              time_t tt;
              struct tm* ti;
              time(&tt);
              ti=localtime(&tt);
              asctime(ti);
              painter.drawText(500,300, asctime(ti));
              query.prepare("select * from FOURNISSEUR");
              query.exec();
              while (query.next())
              {
                  painter.drawText(300,i,query.value(0).toString());
                  painter.drawText(2300,i,query.value(1).toString());
                  painter.drawText(3600,i,query.value(2).toString());
                  painter.drawText(5000,i,query.value(3).toString());
                  painter.drawText(7300,i,query.value(4).toString());
                  painter.drawText(9300,i,query.value(5).toString());
                  i = i +500;
              }

              int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
              if (reponse == QMessageBox::Yes)
              {
                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Lina Cherif/Desktop/GestionDesFournisseurs/liste.pdf"));

                  painter.end();
              }
              if (reponse == QMessageBox::No)
              {
                  painter.end();
              }
          }



void MainWindow::on_pB_sts_clicked()
{
    Dialog_stats stats;
    stats.setModal(true);
    stats.exec();
}

void MainWindow::on_pB_sts_2_clicked()
{
    Dialog_mailing mail;
    mail.setModal(true);
    mail.exec();
}
void MainWindow::update_label()
{
    data=A.read_from_arduino();
    if(data=="1")
    ui->label_->setText("ON");
            else if(data=="0")
        ui->label_->setText("OFF");

}



void MainWindow::on_image_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr(""));

       if(QString::compare(filename,QString())!=0)
       {QImage image;
           bool valid=image.load(filename);
           if(valid){

               ui->image->setText(filename);
               image=image.scaledToWidth(ui->img_name->width(),Qt::SmoothTransformation);
               ui->img_name->setPixmap(QPixmap::fromImage(image));

           }
           else
           {
               QMessageBox::information(this, tr("ERROR"), QString(tr("Not Valid!")));
           }
       }
}

void MainWindow::on_tab_Fournisseur_pressed(const QModelIndex &index)
{
    index.data();
         QString filename = index.data().toString();
         if(QString::compare(filename,QString())!=0)
         {QImage image;
             bool valid=image.load(filename);
             if(valid){


                 image=image.scaledToWidth(ui->mage->width(),Qt::SmoothTransformation);
                 ui->mage->setPixmap(QPixmap::fromImage(image));

             }
             else
             {
                 QMessageBox::information(this, tr("ERROR"), QString(tr("Not Valid!")));
    }}}
