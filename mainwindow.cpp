#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "dialog_statistiques.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include <QRadioButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QHttpMultiPart>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_NumTel->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox_ID->setModel(S.afficher_id());
    S.write(S.time(),"App started");
    ui->tab_Spornors->setModel (S.afficher());
    connection c;
    bool test=c.CreateConnexion();
    if(test)
    {
        ui->label_db->setText("Database: CONNECTED");

    }
    else
        ui->label_db->setText("Database: FAILED");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pB_Ajouter_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    int NUM_TEL=ui->lineEdit_NumTel->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->toPlainText();
    QString PACK;
    if (ui->RadB_Pack1->isChecked())
        PACK="Pack 1";
    if (ui->RadB_Pack2->isChecked())
        PACK="Pack 2";
    if (ui->RadB_Pack3->isChecked())
        PACK="Pack 3";
    sponsoring S(ID,NUM_TEL,DESCRIPTION,PACK);
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

void MainWindow::on_pB_Modifier_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    int NUM_TEL=ui->lineEdit_NumTel->text().toInt();
    QString DESCRIPTION=ui->lineEdit_Description->toPlainText();
    QString PACK;
    if (ui->RadB_Pack1->isChecked())
        PACK="Pack 1";
    if (ui->RadB_Pack2->isChecked())
        PACK="Pack 2";
    if (ui->RadB_Pack3->isChecked())
        PACK="Pack 3";
    sponsoring S(ID,NUM_TEL,DESCRIPTION,PACK);
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

void MainWindow::on_pB_Supprimer_clicked()
{
    sponsoring S;
    S.setid(ui->comboBox_ID->currentText().toInt());
    bool test=S.supprimerS(S.getid());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
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

void MainWindow::on_pB_TirerParNom_clicked()
{
    ui->label_Info->setText("Tri par Num Tel effectué");
    ui->tab_Spornors->setModel(S.tri_numtel());
}

void MainWindow::on_pB_TirerParID_clicked()
{
    ui->label_Info->setText("Tri par ID effectué");
    ui->tab_Spornors->setModel(S.tri_id());
}

void MainWindow::on_pushButton_SupprimerS_clicked()
{
    S.clearh();
    ui->textBrowser_Sponso->setText(S.read());
}

void MainWindow::on_comboBox_ID_currentIndexChanged(int)
{
    int id=ui->comboBox_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query1,query2,query3,query4;
    query1.prepare("SELECT * FROM SPONSORING where ID='"+id_1+"'");
    if(query1.exec())
    {
        while (query1.next())
        {
            ui->lineEdit_ID->setText(query1.value(0).toString());
            ui->lineEdit_NumTel->setText(query1.value(1).toString());
            ui->lineEdit_Description->setText(query1.value(2).toString());

            query2.prepare("SELECT * FROM SPONSORING WHERE PACK='Pack 1' ");
            if(query2.exec()){ while (query2.next()) { ui->RadB_Pack1->setChecked(3);; }}

            query3.prepare("SELECT * FROM SPONSORING WHERE PACK='Pack 2' ");
            if(query3.exec()){ while (query3.next()) { ui->RadB_Pack1->setChecked(3);; }}

            query4.prepare("SELECT * FROM SPONSORING WHERE PACK='Pack 3' ");
            if(query4.exec()){ while (query4.next()) { ui->RadB_Pack1->setChecked(3);; }}
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

void MainWindow::on_pB_ExPDF_clicked()
{
    QPdfWriter pdf("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Logo.png"));
    painter.drawText(3000,1500,"LISTE DES SPONSORS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2300,3300,"NUM_TEL");
    painter.drawText(4300,3300,"DESCRIPTION");
    painter.drawText(9300,3300,"PACK");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from SPONSORING");
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
        QDesktopServices::openUrl(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_pB_Stats_clicked()
{
    DS = new Dialog_Statistiques();

  DS->setWindowTitle("Statistique");
  DS->choix_pie();
  DS->show();
}

void MainWindow::on_pushPlay_clicked()
{
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);

    if (ui->RadB_Pack1->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Sources/Pack1.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->RadB_Pack2->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Sources/Pack2.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->RadB_Pack3->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Sources/Pack3.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }

    vw->show();
    player->play();
}

void MainWindow::on_pushStop_clicked()
{
    player->stop();
    vw->close();
}
void MainWindow::postrequest(QString smsmsg,QString phonenumber)
{

    // create custom temporary event loop on stack
       QEventLoop eventLoop;

       // "quit()" the event-loop, when the network request "finished()"
       QNetworkAccessManager mgr;
       QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

       // the HTTP request
       QNetworkRequest req( QUrl( QString("https://api.orange.com/smsmessaging/v1/outbound/tel%3A%2B322804/requests") ) );

      req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



req.setRawHeader("Authorization", "Bearer hqRfnJmzVeHwrGeV3Ar8iSvQvrbl");
QJsonObject msg;
msg["message"] = smsmsg;
QJsonObject obj;
obj["address"] = "tel:+216"+phonenumber;
obj["senderAddress"] = "tel:+322804";
obj["outboundSMSTextMessage"] = msg;
QJsonObject body;
body["outboundSMSMessageRequest"] = obj;
QJsonDocument doc(body);
QByteArray data = doc.toJson();
       QNetworkReply *reply = mgr.post(req,data);
       eventLoop.exec(); // blocks stack until "finished()" has been called

       if (reply->error() == QNetworkReply::NoError) {
           //success
           qDebug() << "Success" <<reply->readAll();
           delete reply;
       }
       else {
           //failure
           qDebug() << "Failure" <<reply->errorString() << reply->error();
           delete reply;
       }
}
void MainWindow::on_pB_EnvoyerSMS_clicked()
{
    QString numtel=ui->lineEdit_NumTel->text();
    QString msg=ui->TextEdit_SMSBody->toPlainText();
    postrequest(msg,numtel);
}

void MainWindow::on_lineEdit_IDRecherche_textChanged(const QString &arg1)
{
    if (ui->rB_ID->isChecked()==true)
    {
        S.clearTable(ui->tab_Spornors);
        S.chercheID(ui->tab_Spornors,arg1);
    }
    if (ui->rB_NumTel->isChecked()==true)
    {
        S.clearTable(ui->tab_Spornors);
        S.chercheNumTel(ui->tab_Spornors,arg1);
    }
}
