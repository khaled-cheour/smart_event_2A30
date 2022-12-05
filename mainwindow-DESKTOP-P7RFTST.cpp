#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include "dialog_stats.h"
#include "exportexcelobject.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_EventID->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_NbPersonnes->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_EventID->setModel(E.afficher_id());
    ui->tab_Events->setModel (E.afficher());
    E.write(E.time(),"App started");
    ui->text_Events->setText(E.read());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_AjouterP_clicked()
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

void MainWindow::on_pB_SupprimerP_clicked()
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

void MainWindow::on_pB_ModifierP_clicked()
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

void MainWindow::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Events->setModel(E.tri_nom());
}

void MainWindow::on_pB_TireParType_clicked()
{
    ui->label_Info->setText("Tri par Type effectué");
    ui->tab_Events->setModel(E.tri_type());
}

void MainWindow::on_pB_TirerParNbPersonnes_clicked()
{
    ui->label_Info->setText("Tri par Nbr Personnes effectué");
    ui->tab_Events->setModel(E.tri_nbrpersonnes());
}

void MainWindow::on_pushButton_SupprimerE_clicked()
{
    E.clearh();
    ui->text_Events->setText(E.read());
}

void MainWindow::on_comboBox_EventID_currentIndexChanged(int)
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

void MainWindow::on_pushButton_Fermer_clicked()
{
    close();
}

void MainWindow::on_pB_TirerParNbPersonnes_2_clicked()
{
    QPdfWriter pdf("C:/Users/MSI/OneDrive/Bureau/GestionDesEvenements/liste_event");

                QPainter painter(&pdf);

                int i = 4000;
                painter.setPen(Qt::black);
                painter.setFont(QFont("Arial", 30));
                painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/MSI/OneDrive/Bureau/GestionDesEvenements/liste_event"));
                painter.drawText(3000,1500,"LISTE DES EVENEMENTS");
                painter.setPen(Qt::blue);
                painter.setFont(QFont("Arial", 50));
                painter.drawRect(2700,200,6300,2600);
                painter.drawRect(0,3000,9600,500);
                painter.setPen(Qt::black);
                painter.setFont(QFont("Arial", 9));
                painter.drawText(300,3300,"NOM");
                painter.drawText(2300,3300,"TYPE");
                painter.drawText(4300,3300,"LIEUX");
                painter.drawText(6000,3300,"NOMBRE_PERSONNES");
                painter.drawText(8300,3300,"DATE_E");
                painter.drawText(10300,3300,"TIME_E");
                QSqlQuery query;
                query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
                time_t tt;
                struct tm* ti;
                time(&tt);
                ti=localtime(&tt);
                asctime(ti);
                painter.drawText(500,300, asctime(ti));
                query.prepare("select * from EVENEMENT");
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
                    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/MSI/OneDrive/Bureau/GestionDesEvenements/liste_event"));

                    painter.end();
                }
                if (reponse == QMessageBox::No)
                {
                    painter.end();
                }
            }






void MainWindow::on_pB_Recherche_clicked()
{
    evenement E;
    QString text;
    if (ui->rB_ID->isChecked()==true)
    {
        E.clearTable(ui->tab_Events);
            int ID=ui->lineEdit_Recherche->text().toInt();
            E.chercheID(ui->tab_Events,ID);
    }
    if (ui->rb_Nom->isChecked()==true)
    {
        E.clearTable(ui->tab_Events);
            QString Nom=ui->lineEdit_Recherche->text();
            E.chercheNom(ui->tab_Events,Nom);
    }
    if (ui->rB_Type->isChecked()==true)
    {
        E.clearTable(ui->tab_Events);
            QString Type=ui->lineEdit_Recherche->text();
            E.chercheType(ui->tab_Events,Type);
    }
}

void MainWindow::on_pB_Recherche_2_clicked()
{
        Dialog_Stats stats;
        stats.setModal(true);
        stats.exec();

}

/*void MainWindow::on_facture_clicked()
{
    float MainWindow::calculer()
    {
       EVENEMENT E ;
        float fact=0;
           QString cher =ui->select_esp->currentText();
           QSqlQuery qry;
           qry=ES.select(cher);
           if(qry.exec())
           {
               while(qry.next())
               {
                   fact+=qry.value(5).toFloat();
               }
           }
        if(ui->checkBox->isChecked())
            fact+=10;
        if(ui->checkBox_2->isChecked())
            fact+=20;

        if(ui->checkBox_3->isChecked())
            fact+=5;
        if(ui->checkBox_4->isChecked())
            fact+=5;
        if(ui->checkBox_5->isChecked())
            fact+=10;
      return fact;
    }
}
*/
void MainWindow::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                           tr("Excel Files (*.xls)"));
           if (fileName.isEmpty())
               return;

           ExportExcelObject obj(fileName, "mydata", ui->tabEx);

           //colums to export
           obj.addField(0, "linePrixFour", "char(20)");
           obj.addField(1, "LOCAL", "char(20)");




           int retVal = obj.export2Excel();
           if( retVal > 0)
           {
               QMessageBox::information(this, tr("Done"),
                                        QString(tr("%1 records exported!")).arg(retVal)
                                        );
           }
}

/* void MainWindow::on_calendarWidget_selectionChanged()
{

  ui->dateEdit->setDate(ui->calendarWidget->selectedDate());

} */
