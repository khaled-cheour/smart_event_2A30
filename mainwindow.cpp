#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connexion.h"
#include "exportexcelobject.h"
#include <QCalendarWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
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
#include <QPdfWriter>
#include <QPainter>
#include "chatboxconnectiondialog.h"
#include <QTcpSocket>
#include <QTextStream>
#include "smtp.h"
#include <QCoreApplication>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Login_line_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->stackedWidget->setCurrentIndex(0);
    ui->Main_push_Personnel->setDisabled(true);
    ui->Main_push_Evenement->setDisabled(true);
    ui->Main_push_Fournisseur->setDisabled(true);
    ui->Main_push_Locaux->setDisabled(true);
    ui->Main_push_Sponsoring->setDisabled(true);
    connexion c;
    bool test=c.CreateConnexion();
    if(test)
        ui->Login_label_Connection->setText("Datebase: Open.\nConnection: Successful.");
    else
        ui->Login_label_Connection->setText("Datebase: Closed.\nConnection: Failed.");
    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();
        break;
    case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
        break;
    case(-1):qDebug()<< "arduino is not availble";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_RFID()));
    /*Khaled Setup*/
    ui->Perso_line_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->Perso_line_Absance->setValidator( new QIntValidator(0, 999, this));
    ui->Perso_combo_CIN->setModel(P.afficher_cin());
    ui->Perso_TableView->setModel (P.afficher());
    ui->Perso_table_MDM->setModel (P.afficher_MDM());
    P.write(P.time(),"App started");
    ui->Perso_textbrowser->setText(P.read());
    nSocket=new QTcpSocket(this);
    connect(nSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(nSocket);
        auto text=T.readAll();
        ui->Perso_text_Chatbox->append(text);
    });
    /*Ala Setup*/
    ui->Sponso_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->Sponso_line_NumTel->setValidator( new QIntValidator(0, 99999999, this));
    ui->Sponso_line_NumTelSMS->setValidator( new QIntValidator(0, 99999999, this));
    S.write(S.time(),"App started");
    ui->Sponso_combo_ID->setModel(S.afficher_id());
    ui->Sponso_combo_IDSMS->setModel(S.afficher_id());
    ui->Sponso_TableView->setModel (S.afficher());
    /*Aziz Setup*/
    ui->Event_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->Event_line_NbrPerso->setValidator( new QIntValidator(0, 99999, this));
    ui->Event_combo_ID->setModel(E.afficher_id());
    ui->Event_TableView->setModel (E.afficher());
    E.write(E.time(),"App started");
    ui->Event_textbrowser->setText(E.read());
    MainWindow::on_Event_push_UpdateStats_clicked();
    /*Lina Setup*/
    ui->Four_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->Four_line_Prix->setValidator( new QIntValidator(0, 99999999, this));
    MainWindow::connect(ui->envoyer_dialog_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    MainWindow::connect(ui->annuler_mail_2, SIGNAL(clicked()),this, SLOT(close()));
    MainWindow::QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    ui->Four_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->Four_combo_ID->setModel(F.afficher_id());
    ui->Four_TableView->setModel (F.afficher());
    F.write(F.time(),"App started");
    ui->Four_textbrowser->setText(F.read());
    MainWindow::on_Four_push_UpdateStats_clicked();
    /*Farah Setup*/
    ui->Loc_line_Prix->setValidator( new QIntValidator(0, 99999999, this));
    ui->Loc_line_NbrPerso->setValidator( new QIntValidator(0, 99999999, this));
    ui->Loc_combo_Adresse->setModel(L.afficher_adresse());
    ui->Loc_TableView->setModel (L.afficher());
    L.write(L.time(),"App started");
    ui->Loc_textbrowser->setText(L.read());
    MainWindow::on_Loc_push_UpdateStats_clicked();
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
    ui->Loc_WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
}
MainWindow::MainWindow(QString e,QString n,QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString contenu="Contenu";
    ui->setupUi(this);
    ui->recipient_2->setText(e);
    ui->uname->setText("smarteventoplanner@gmail.com");
    ui->passwd_2->setText("okgxvskpbwjzyocr ");
    ui->passwd_2->setEchoMode(QLineEdit::Password);
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_Login_push_Login_clicked(){
    QString CIN = ui->Login_line_CIN->text();
    QString PASSWORD = ui->Login_line_Password->text();
    QSqlQuery query;
    QString gestion;
    if(query.exec("SELECT * from PERSONNEL where CIN='"+CIN+"' and PASSWORD='"+PASSWORD+"'" ))
    {
        if (query.next())
        {
            gestion=query.value(7).toString();
            
            ui->stackedWidget->setCurrentIndex(1);
            if (gestion.compare("Administrateur")==0){
                ui->Main_push_Personnel->setEnabled(true);
                ui->Main_push_Evenement->setEnabled(true);
                ui->Main_push_Fournisseur->setEnabled(true);
                ui->Main_push_Locaux->setEnabled(true);
                ui->Main_push_Sponsoring->setEnabled(true);
            }
            if (gestion.compare("Personnels")==0){
                ui->Main_push_Personnel->setEnabled(true);
                ui->Main_push_Evenement->setEnabled(false);
                ui->Main_push_Fournisseur->setEnabled(false);
                ui->Main_push_Locaux->setEnabled(false);
                ui->Main_push_Sponsoring->setEnabled(false);
            }
            if (gestion.compare("Evenements")==0){
                ui->Main_push_Personnel->setEnabled(false);
                ui->Main_push_Evenement->setEnabled(true);
                ui->Main_push_Fournisseur->setEnabled(false);
                ui->Main_push_Locaux->setEnabled(false);
                ui->Main_push_Sponsoring->setEnabled(false);
            }
            if (gestion.compare("Fournisseurs")==0){
                ui->Main_push_Personnel->setEnabled(false);
                ui->Main_push_Evenement->setEnabled(false);
                ui->Main_push_Fournisseur->setEnabled(true);
                ui->Main_push_Locaux->setEnabled(false);
                ui->Main_push_Sponsoring->setEnabled(false);
            }
            if (gestion.compare("Locaux")==0){
                ui->Main_push_Personnel->setEnabled(false);
                ui->Main_push_Evenement->setEnabled(false);
                ui->Main_push_Fournisseur->setEnabled(false);
                ui->Main_push_Locaux->setEnabled(true);
                ui->Main_push_Sponsoring->setEnabled(false);
            }
            if (gestion.compare("Sponsoring")==0){
                ui->Main_push_Personnel->setEnabled(false);
                ui->Main_push_Evenement->setEnabled(false);
                ui->Main_push_Fournisseur->setEnabled(false);
                ui->Main_push_Locaux->setEnabled(false);
                ui->Main_push_Sponsoring->setEnabled(true);
            }
            QString NOM=query.value(1).toString();
            QString PRENOM=query.value(2).toString();
            ui->Login_label_LoginInfo->setText("Connecté: "+NOM+" "+PRENOM+"");
            ui->Main_label_LoggedAs->setText("Logged in as: "+NOM+" "+PRENOM+"\nGestion: "+gestion+"");
        }
        else
        {
            ui->Login_label_LoginInfo->setText("CIN ou Password sont incorrect");
        }
    }
}
int modes=1;
void MainWindow::on_Login_check_PassShowHide_clicked()
{
    if(modes==1){ui->Login_line_Password->setEchoMode(QLineEdit::Normal);modes=0;}
    else{ui->Login_line_Password->setEchoMode(QLineEdit::Password);modes=1;}
}
void MainWindow::on_Main_push_Return_clicked(){ui->stackedWidget->setCurrentIndex(0);}
void MainWindow::on_Main_push_Personnel_clicked(){ui->stackedWidget->setCurrentIndex(2);}
void MainWindow::on_Main_push_Evenement_clicked(){ui->stackedWidget->setCurrentIndex(3);}
void MainWindow::on_Main_push_Fournisseur_clicked(){ui->stackedWidget->setCurrentIndex(4);}
void MainWindow::on_Main_push_Locaux_clicked(){ui->stackedWidget->setCurrentIndex(5);}
void MainWindow::on_Main_push_Sponsoring_clicked(){ui->stackedWidget->setCurrentIndex(6);}
void MainWindow::on_Main_push_Quitter_clicked(){close();}
/*------------INTEGRATION KHALED------------*/
void MainWindow::on_Perso_push_Ajouter_clicked(){
    int CIN=ui->Perso_line_CIN->text().toInt();
    QString NOM=ui->Perso_line_Nom->text();
    QString PRENOM=ui->Perso_line_Prenom->text();
    QString GENDER=ui->Perso_combo_Gender->currentText();
    QDate DATE_DE_NAISSANCE=ui->Perso_date_DDN->date();
    QString EMAIL=ui->Perso_line_Email->text();
    QString ADRESSE=ui->Perso_line_Adresse->text();
    QString GESTION=ui->Perso_combo_Gestion->currentText();
    int ABSANCE=ui->Perso_line_Absance->text().toInt();
    QString PASSWORD=ui->Perso_line_Password->text();
    QString RFID=ui->Perso_line_RFID->text();
    QString PHOTO=ui->Perso_label_Photo->text();
    personnel P(CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,ABSANCE,PASSWORD,RFID,PHOTO);
    bool test=P.ajouter();
    if(test)
    {
        ui->Perso_Label_GestionInfo->setText("Ajout Effectué");
        ui->Perso_TableView->setModel(P.afficher());
        ui->Perso_table_MDM->setModel (P.afficher_MDM());
        P.write(P.time(),"PERSONNEL: ajout effectué");
        ui->Perso_textbrowser->setText(P.read());
    }
    else
    {
        ui->Perso_Label_GestionInfo->setText("Ajout non effectué");
    }
}
void MainWindow::on_Perso_push_Modifier_clicked(){
    int CIN=ui->Perso_line_CIN->text().toInt();
    QString NOM=ui->Perso_line_Nom->text();
    QString PRENOM=ui->Perso_line_Prenom->text();
    QString GENDER=ui->Perso_combo_Gender->currentText();
    QDate DATE_DE_NAISSANCE=ui->Perso_date_DDN->date();
    QString EMAIL=ui->Perso_line_Email->text();
    QString ADRESSE=ui->Perso_line_Adresse->text();
    QString GESTION=ui->Perso_combo_Gestion->currentText();
    int ABSANCE=ui->Perso_line_Absance->text().toInt();
    QString PASSWORD=ui->Perso_line_Password->text();
    QString RFID=ui->Perso_line_RFID->text();
    QString PHOTO=ui->Perso_Label_Photoname->text();
    personnel P(CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,ABSANCE,PASSWORD,RFID,PHOTO);
    bool test=P.modifierP();
    if(test)
    {
        ui->Perso_Label_GestionInfo->setText("Modification effectué");
        ui->Perso_TableView->setModel(P.afficher());
        ui->Perso_table_MDM->setModel (P.afficher_MDM());
        ui->Perso_combo_CIN->setModel(P.afficher_cin());
        P.write(P.time(),"PERSONNEL: Modification effectuée");
        ui->Perso_textbrowser->setText(P.read());
    }
    else
    {
        ui->Perso_Label_GestionInfo->setText("Modification non effectué");
    }
}
void MainWindow::on_Perso_push_Supprimer_clicked(){
    personnel P;
    P.setcin(ui->Perso_combo_CIN->currentText().toInt());
    bool test=P.supprimer(P.getcin());
    if(test)
    {
        ui->Perso_Label_GestionInfo->setText("Suppression effectué");
        ui->Perso_TableView->setModel(P.afficher());
        ui->Perso_combo_CIN->setModel(P.afficher_cin());
        P.write(P.time(),"PERSONNEL: Supression effectuée");
        ui->Perso_table_MDM->setModel (P.afficher_MDM());
        ui->Perso_textbrowser->setText(P.read());
    }
    else
    {
        ui->Perso_Label_GestionInfo->setText("Suppression non effectué");
    }
}
void MainWindow::on_Perso_push_EDM_clicked(){
    ui->Perso_table_MDM->setModel(P.triMDM());
}
void MainWindow::on_Perso_push_Photo_clicked(){
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr(""));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid=image.load(filename);
        if(valid)
        {
            ui->Perso_Label_Photoname->setText(filename);
            image=image.scaledToWidth(ui->Perso_label_Photo->width(),Qt::SmoothTransformation);
            ui->Perso_label_Photo->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::information(this, tr("ERROR"), QString(tr("Not Valid!")));
        }
    }
}
void MainWindow::on_Perso_TableView_pressed(const QModelIndex &index)
{
    index.data();
    QString filename = index.data().toString();
    if(QString::compare(filename,QString())!=0)
    {QImage image;
        bool valid=image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->Perso_label_PhotoSelect->width(),Qt::SmoothTransformation);
            ui->Perso_label_PhotoSelect->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::information(this, tr("ERROR"), QString(tr("Not Valid!")));
        }
    }
}
void MainWindow::on_Perso_push_TriCIN_clicked(){
    ui->Perso_Label_ListeInfo->setText("Tri par CIN effectué");
    ui->Perso_TableView->setModel(P.tri_cin());
}
void MainWindow::on_Perso_push_TriNom_clicked(){
    ui->Perso_Label_ListeInfo->setText("Tri par Nom effectué");
    ui->Perso_TableView->setModel(P.tri_nom());
}
void MainWindow::on_Perso_push_TriEmail_clicked(){
    ui->Perso_Label_ListeInfo->setText("Tri par Email effectué");
    ui->Perso_TableView->setModel(P.tri_email());
}
void MainWindow::on_Perso_push_SupprimerTextBrowser_clicked(){
    P.clearh();
    ui->Perso_textbrowser->setText(P.read());
}
void MainWindow::on_Perso_combo_CIN_currentIndexChanged(int){
    int cin=ui->Perso_combo_CIN->currentText().toInt();
    QString cin_1=QString::number(cin);
    QSqlQuery query;
    query.prepare("SELECT * FROM PERSONNEL where CIN='"+cin_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Perso_line_CIN->setText(query.value(0).toString()) ;
            ui->Perso_line_Nom->setText(query.value(1).toString()) ;
            ui->Perso_line_Prenom->setText(query.value(2).toString()) ;
            ui->Perso_combo_Gender->setCurrentText(query.value(3).toString()) ;
            ui->Perso_date_DDN->setDate(query.value(4).toDate()) ;
            ui->Perso_line_Email->setText(query.value(5).toString()) ;
            ui->Perso_line_Adresse->setText(query.value(6).toString()) ;
            ui->Perso_combo_Gestion->setCurrentText(query.value(7).toString()) ;
            ui->Perso_line_Absance->setText(query.value(8).toString()) ;
            ui->Perso_line_Password->setText(query.value(9).toString()) ;
            ui->Perso_line_RFID->setText(query.value(10).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error "),
                              QObject::tr("ECHEC DE chargement"), QMessageBox::Cancel);
    }
}
void MainWindow::on_Perso_line_Recherche_textChanged(const QString &arg1){
    if (ui->Perso_radio_CIN->isChecked()==true)
    {
        P.clearTable(ui->Perso_TableView);
        P.chercheCIN(ui->Perso_TableView,arg1);
    }
    if (ui->Perso_radio_Nom->isChecked()==true)
    {
        P.clearTable(ui->Perso_TableView);
        P.chercheNom(ui->Perso_TableView,arg1);
    }
}
void MainWindow::Perso_choix_pie(){
    QChartView *chartView ;
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;
    q1.prepare("SELECT * FROM PERSONNEL");
    q1.exec(); q2.prepare("SELECT * FROM PERSONNEL WHERE GENDER='Homme'");
    q2.exec(); q3.prepare("SELECT * FROM PERSONNEL WHERE GENDER='Femme'");
    q3.exec(); q4.prepare("SELECT * FROM PERSONNEL WHERE GENDER='Autre'");
    q4.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    c1=c1/tot; c2=c2/tot; c3=c3/tot;
    QPieSeries *series = new QPieSeries();
    series->append("Homme",c1);
    series->append("Femme",c2);
    series->append("Autre",c3);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart,ui->Perso_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570,570);
    chartView->show();
}
void MainWindow::on_Perso_push_UpdateStats_clicked(){
    Perso_choix_pie();
    show();
}
void MainWindow::update_RFID(){
    QSqlQuery query,q2;
    QByteArray data="";
    QString UserMessage="";
    data=A.read_from_arduino();
    RFID=RFID+data;
    if(RFID!="" && RFID.length()==11)
    {
        query.prepare("select * from PERSONNEL where RFID='"+RFID+"'");
        if(query.exec())
        {
            if (query.next())
            {
                ui->Perso_line_CIN->setText(query.value(0).toString()) ;
                ui->Perso_line_Nom->setText(query.value(1).toString()) ;
                ui->Perso_line_Prenom->setText(query.value(2).toString()) ;
                ui->Perso_combo_Gender->setCurrentText(query.value(3).toString()) ;
                ui->Perso_date_DDN->setDate(query.value(4).toDate()) ;
                ui->Perso_line_Email->setText(query.value(5).toString()) ;
                ui->Perso_line_Adresse->setText(query.value(6).toString()) ;
                ui->Perso_combo_Gestion->setCurrentText(query.value(7).toString()) ;
                ui->Perso_line_Absance->setText(query.value(8).toString()) ;
                ui->Perso_line_Password->setText(query.value(9).toString()) ;
                QString NOM= query.value(1).toString();
                QString PRENOM= query.value(2).toString();
                UserMessage=NOM+" "+PRENOM;
                QString c;
                /*for (int i=0; i < UserMessage.length(); i++)
                    {
                        c = UserMessage.at(i);
                        QByteArray m= c.toUtf8();
                        A.write_to_arduino(m);
                    }*/
                QByteArray m= UserMessage.toUtf8();
                A.write_to_arduino(m);
                ui->Perso_line_RFID->setText(RFID);
                //QString message ="1 ";
                //QByteArray br = message. toUtf8();
                //A.write_to_arduino(br);
                ui->Perso_label_RFIDInfo->setText("Registred");
                qDebug() <<  " RFID is: " <<RFID;
                qDebug() <<  " User: " <<UserMessage;
                // qDebug() <<  " Arduino Signal: " <<message;
                
            }
            else
            {
                ui->Perso_line_RFID->setText(RFID);
                QString message ="Error";
                QByteArray br = message.toUtf8();
                A.write_to_arduino(br);
                ui->Perso_label_RFIDInfo->setText("Not Registered");
                qDebug() <<  " Arduino Signal: " <<message;
            }
        }
        if(RFID.length()==11)
        {
            RFID="";
        }
    }
}
void MainWindow::on_Perso_push_Arduino_clicked()
{
    Arduino A;
    A.write_to_arduino("1");
}
void MainWindow::on_Perso_push_Send_clicked(){
    QTextStream T(nSocket);
    T << ui->Perso_line_Nickname-> text() << ": " << ui->Perso_line_Message->text();
    nSocket->flush();
    ui->Perso_line_Message->clear();
}
void MainWindow::on_Perso_push_Bind_clicked(){
    chatboxconnectiondialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;
    }
    nSocket->connectToHost(D.hostname(),D.port());
}
void MainWindow::on_Perso_push_Fermer_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
/*------------INTEGRATION ALA------------*/
void MainWindow::on_Sponso_push_Ajouter_clicked(){
    int ID=ui->Sponso_line_ID->text().toInt();
    int NUM_TEL=ui->Sponso_line_NumTel->text().toInt();
    QString DESCRIPTION=ui->Sponso_text_Description->toPlainText();
    QString PACK;
    if (ui->Sponso_radio_Pack1->isChecked())
        PACK="Pack 1";
    if (ui->Sponso_radio_Pack2->isChecked())
        PACK="Pack 2";
    if (ui->Sponso_radio_Pack3->isChecked())
        PACK="Pack 3";
    sponsoring S(ID,NUM_TEL,DESCRIPTION,PACK);
    bool test=S.ajouterS();
    if(test)
    {
        ui->Sponso_Label_GestionInfo->setText("Ajout effectué");
        ui->Sponso_combo_ID->setModel(S.afficher_id());
        ui->Sponso_combo_IDSMS->setModel(S.afficher_id());
        ui->Sponso_TableView->setModel(S.afficher());
        S.write(S.time(),"SPONSORING: Ajout effectué");
        ui->Sponso_textbrowser->setText(S.read());
    }
    else
    {
        ui->Sponso_Label_GestionInfo->setText("Ajout non effectué");
    }
}
void MainWindow::on_Sponso_push_Modifier_clicked(){
    int ID=ui->Sponso_line_ID->text().toInt();
    int NUM_TEL=ui->Sponso_line_NumTel->text().toInt();
    QString DESCRIPTION=ui->Sponso_text_Description->toPlainText();
    QString PACK;
    if (ui->Sponso_radio_Pack1->isChecked())
        PACK="Pack 1";
    if (ui->Sponso_radio_Pack2->isChecked())
        PACK="Pack 2";
    if (ui->Sponso_radio_Pack3->isChecked())
        PACK="Pack 3";
    sponsoring S(ID,NUM_TEL,DESCRIPTION,PACK);
    bool test=S.modifierS();
    if(test)
    {
        ui->Sponso_Label_GestionInfo->setText("Modification effectué");
        ui->Sponso_combo_ID->setModel(S.afficher_id());
        ui->Sponso_combo_IDSMS->setModel(S.afficher_id());
        ui->Sponso_TableView->setModel(S.afficher());
        S.write(S.time(),"SPONSORING: Modification effectué");
        ui->Sponso_textbrowser->setText(S.read());
    }
    else
    {
        ui->Sponso_Label_GestionInfo->setText("Modification non effectué");
    }
}
void MainWindow::on_Sponso_push_Supprimer_clicked(){
    sponsoring S;
    S.setid(ui->Sponso_combo_ID->currentText().toInt());
    bool test=S.supprimerS(S.getid());
    if(test)
    {
        ui->Sponso_Label_GestionInfo->setText("Suppression effectué");
        ui->Sponso_TableView->setModel(S.afficher());
        ui->Sponso_combo_ID->setModel(S.afficher_id());
        ui->Sponso_combo_IDSMS->setModel(S.afficher_id());
        S.write(S.time(),"SPONSORING: Suppression effectué");
        ui->Sponso_textbrowser->setText(S.read());
    }
    else
    {
        ui->Sponso_Label_GestionInfo->setText("Suppression non effectué");
    }
}
void MainWindow::on_Sponso_push_TriID_clicked(){
    ui->Sponso_Label_ListeInfo->setText("Tri par ID effectué");
    ui->Sponso_TableView->setModel(S.tri_id());
}
void MainWindow::on_Sponso_push_TriNumTel_clicked(){
    ui->Sponso_Label_ListeInfo->setText("Tri par Num Tel effectué");
    ui->Sponso_TableView->setModel(S.tri_numtel());
}
void MainWindow::on_Sponso_push_SupprimerTextBrowser_clicked(){
    S.clearh();
    ui->Sponso_textbrowser->setText(S.read());
}
void MainWindow::on_Sponso_combo_ID_currentIndexChanged(int){
    int id=ui->Sponso_combo_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORING where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Sponso_line_ID->setText(query.value(0).toString()) ;
            ui->Sponso_line_NumTel->setText(query.value(1).toString()) ;
            ui->Sponso_text_Description->setText(query.value(2).toString()) ;
        }
    }
    else
    {
        ui->Sponso_Label_GestionInfo->setText("Echec de chargement");
    }
}
void MainWindow::on_Sponso_combo_IDSMS_currentIndexChanged(int){
    int id=ui->Sponso_combo_IDSMS->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORING where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Sponso_line_NumTelSMS->setText(query.value(1).toString()) ;
        }
    }
}
void MainWindow::on_Sponso_line_Recherche_textChanged(const QString &arg1){
    if (ui->Sponso_radio_ID->isChecked()==true)
    {
        S.clearTable(ui->Sponso_TableView);
        S.chercheID(ui->Sponso_TableView,arg1);
    }
    if (ui->Sponso_radio_NumTel->isChecked()==true)
    {
        S.clearTable(ui->Sponso_TableView);
        S.chercheNumTel(ui->Sponso_TableView,arg1);
    }
}
void MainWindow::on_Sponso_push_Play_clicked(){
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    if (ui->Sponso_radio_Pack1->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Sources/Pack1.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->Sponso_radio_Pack2->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Sources/Pack2.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->Sponso_radio_Pack3->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Sources/Pack3.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    vw->show();
    player->play();
}
void MainWindow::on_Sponso_push_Stop_clicked(){
    player->stop();
    vw->close();
}
void MainWindow::on_Sponso_push_EnvoyerSMS_clicked(){
    sponsoring S;
    QString numtel=ui->Sponso_line_NumTelSMS->text();
    QString msg=ui->Sponso_text_SMS->toPlainText();
    S.postrequest(msg,numtel);
}
void MainWindow::Sponso_choix_pie(){
    QChartView *chartView ;
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;
    q1.prepare("SELECT * FROM SPONSORING");
    q1.exec(); q2.prepare("SELECT * FROM SPONSORING WHERE PACK='Pack 1'");
    q2.exec(); q3.prepare("SELECT * FROM SPONSORING WHERE PACK='Pack 2'");
    q3.exec(); q4.prepare("SELECT * FROM SPONSORING WHERE PACK='Pack 3'");
    q4.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    c1=c1/tot; c2=c2/tot; c3=c3/tot;
    QPieSeries *series = new QPieSeries();
    series->append("Pack 1",c1);
    series->append("Pack 2",c2);
    series->append("Pack 3",c3);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart,ui->Sponso_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570,570);
    chartView->show();
}
void MainWindow::on_Sponso_push_UpdateStats_clicked(){
    Sponso_choix_pie();
    show();
}
void MainWindow::on_Sponso_push_ExportPDF_clicked(){
    QPdfWriter pdf("C:/Users/alamo/Desktop/ProjetCPP V2/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Logo.png"));
    painter.drawText(3000,1500,"LISTE DES SPONSORS");
    painter.setPen(Qt::cyan);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2300,3300,"NUM_TEL");
    painter.drawText(4300,3300,"DESCRIPTION");
    painter.drawText(9000,3300,"PACK");
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
        painter.drawText(9000,i,query.value(3).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/alamo/Desktop/ProjetCPP V2/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}
void MainWindow::on_Sponso_push_Fermer_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
/*------------INTEGRATION AZIZ------------*/
void MainWindow::on_Event_push_Ajouter_clicked(){
    int ID=ui->Event_line_ID->text().toInt();
    QString NOM=ui->Event_line_Nom->text();
    QString TYPE=ui->Event_line_Type->text();
    QString LIEU=ui->Event_line_Lieu->text();
    int NOMBRE_PERSONNES=ui->Event_line_NbrPerso->text().toInt();
    QDate DATE_E=ui->Event_date_Date->date();
    QTime TIME_E=ui->Event_time_Heure->time();
    int PRIX_F=ui->Event_line_PrixFournisseur->text().toInt();
    int PRIX_L=ui->Event_line_PrixLocal->text().toInt();
    evenement E(ID,NOM,TYPE,LIEU,NOMBRE_PERSONNES,DATE_E,TIME_E,PRIX_F,PRIX_L);
    bool test=E.AjouterE();
    if(test)
    {
        ui->Event_Label_GestionInfo->setText("Ajout Effectué");
        ui->Event_combo_ID->setModel(E.afficher_id());
        ui->Event_TableView->setModel(E.afficher());
        E.write(E.time(),"EVENEMENT: Ajout effectué");
        ui->Event_textbrowser->setText(E.read());
    }
    else
    {
        ui->Event_Label_GestionInfo->setText("Ajout non effectué");
    }
}
void MainWindow::on_Event_push_Modifier_clicked(){
    int ID=ui->Event_line_ID->text().toInt();
    QString NOM=ui->Event_line_Nom->text();
    QString TYPE=ui->Event_line_Type->text();
    QString LIEU=ui->Event_line_Lieu->text();
    int NOMBRE_PERSONNES=ui->Event_line_NbrPerso->text().toInt();
    QDate DATE_E=ui->Event_date_Date->date();
    QTime TIME_E=ui->Event_time_Heure->time();
    int PRIX_F=ui->Event_line_PrixFournisseur->text().toInt();
    int PRIX_L=ui->Event_line_PrixLocal->text().toInt();
    evenement E(ID,NOM,TYPE,LIEU,NOMBRE_PERSONNES,DATE_E,TIME_E,PRIX_F,PRIX_L);
    bool test=E.ModifierE();
    if(test)
    {
        ui->Event_Label_GestionInfo->setText("Modification effectué");
        ui->Event_combo_ID->setModel(E.afficher());
        ui->Event_TableView->setModel(E.afficher_id());
        E.write(E.time(),"EVENEMENT: Modification Effectuée");
        ui->Event_textbrowser->setText(E.read());
    }
    else
    {
        ui->Event_Label_GestionInfo->setText("Modification non effectué");
    }
}
void MainWindow::on_Event_push_Supprimer_clicked(){
    evenement E;
    E.setid(ui->Event_combo_ID->currentText().toInt());
    bool test=E.SupprimerE(E.getid());
    if(test)
    {
        ui->Event_Label_GestionInfo->setText("Suppression effectué");
        ui->Event_TableView->setModel(E.afficher());
        ui->Event_combo_ID->setModel(E.afficher_id());
        E.write(E.time(),"EVENEMENT: Supression effectuée");
        ui->Event_textbrowser->setText(E.read());
    }
    else
    {
        ui->Event_Label_GestionInfo->setText("Suppression non effectué");
    }
}
void MainWindow::on_Event_push_TriID_clicked(){
    ui->Event_label_ListeInfo->setText("Tri par ID effectué");
    ui->Event_TableView->setModel(E.tri_id());
}
void MainWindow::on_Event_push_TriNbrPerso_clicked(){
    ui->Event_label_ListeInfo->setText("Tri par Nbr Perso effectué");
    ui->Event_TableView->setModel(E.tri_nbrpersonnes());
}
void MainWindow::on_Event_push_TriType_clicked(){
    ui->Event_label_ListeInfo->setText("Tri par Type effectué");
    ui->Event_TableView->setModel(E.tri_type());
}
void MainWindow::on_Event_push_SupprimerTextBrowser_clicked(){
    E.clearh();
    ui->Event_textbrowser->setText(E.read());
}
void MainWindow::on_Event_line_Recherche_textChanged(const QString &arg1){
    if (ui->Event_radio_ID->isChecked()==true)
    {
        E.clearTable(ui->Sponso_TableView);
        E.chercheID(ui->Sponso_TableView,arg1);
    }
    if (ui->Event_radio_Nom->isChecked()==true)
    {
        E.clearTable(ui->Sponso_TableView);
        E.chercheNom(ui->Sponso_TableView,arg1);
    }
}
void MainWindow::on_Event_combo_ID_currentIndexChanged(int){
    int id=ui->Event_combo_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM EVENEMENT where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Event_line_ID->setText(query.value(0).toString());
            ui->Event_line_Nom->setText(query.value(1).toString());
            ui->Event_line_Type->setText(query.value(2).toString());
            ui->Event_line_Lieu->setText(query.value(3).toString());
            ui->Event_line_NbrPerso->setText(query.value(4).toString()) ;
            ui->Event_date_Date->setDate(query.value(5).toDate()) ;
            ui->Event_time_Heure->setTime(query.value(6).toTime()) ;
            ui->Event_Calander_2->setSelectedDate(query.value(5).toDate());
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::Event_statistiques(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery qry;
    int i=0;
    qry.exec("SELECT ID FROM EVENTMENT");
    while (qry.next())
    {
        QString ID = qry.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<ID;
    }
}
void MainWindow::on_Event_push_UpdateStats_clicked()
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(255, 255, 255));
    ui->Event_Plot->setBackground(QBrush(gradient));
    QCPBars *A = new QCPBars(ui->Event_Plot->xAxis, ui->Event_Plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);
    A->setName("Les Nbr.Personnes selon les ID");
    A->setPen(QPen(QColor(255, 0, 0).lighter(120)));
    A->setBrush(QColor(39, 39, 39));
    QVector<double> ticks;
    QVector<QString> labels;
    Event_statistiques(&ticks,&labels);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->Event_Plot->xAxis->setTicker(textTicker);
    ui->Event_Plot->xAxis->setTickLabelRotation(60);
    ui->Event_Plot->xAxis->setSubTicks(false);
    ui->Event_Plot->xAxis->setLabel("ID");
    ui->Event_Plot->xAxis->setTickLength(0, 4);
    ui->Event_Plot->xAxis->setRange(0, 8);
    ui->Event_Plot->xAxis->setBasePen(QPen(Qt::black));
    ui->Event_Plot->xAxis->setTickPen(QPen(Qt::black));
    ui->Event_Plot->xAxis->grid()->setVisible(true);
    ui->Event_Plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->Event_Plot->xAxis->setTickLabelColor(Qt::black);
    ui->Event_Plot->xAxis->setLabelColor(Qt::black);
    ui->Event_Plot->yAxis->setRange(0,10);
    ui->Event_Plot->yAxis->setPadding(5);
    ui->Event_Plot->yAxis->setLabel("NOMBRE_PERSONNES");
    ui->Event_Plot->yAxis->setBasePen(QPen(Qt::black));
    ui->Event_Plot->yAxis->setTickPen(QPen(Qt::black));
    ui->Event_Plot->yAxis->setSubTickPen(QPen(Qt::black));
    ui->Event_Plot->yAxis->grid()->setSubGridVisible(true);
    ui->Event_Plot->yAxis->setTickLabelColor(Qt::black);
    ui->Event_Plot->yAxis->setLabelColor(Qt::black);
    ui->Event_Plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->Event_Plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> PlaceData;
    QSqlQuery q1("SELECT NOMBRE_PERSONNES FROM EVENTMENT");
    while (q1.next())
    {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    A->setData(ticks, PlaceData);
    ui->Event_Plot->legend->setVisible(true);
    ui->Event_Plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->Event_Plot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->Event_Plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    ui->Event_Plot->legend->setFont(legendFont);
    ui->Event_Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void MainWindow::on_Event_push_Excel_clicked(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (), tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;
    ExportExcelObject obj(fileName, "EVENEMENT", ui->Event_TableView);
    obj.addField(7, "PRIX_F", "char(20)");
    obj.addField(8, "PRIX_L", "char(20)");
    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"), QString(tr("%1 records exported!")).arg(retVal));
    }
}
void MainWindow::on_Event_push_Fermer_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_Event_Calander_2_selectionChanged(){
    ui->Event_date_Date->setDate(ui->Event_Calander_2->selectedDate());
    QDate date=QDate(ui->Event_Calander_2->selectedDate());
    QSqlQuery query;
    if (query.exec("SELECT * FROM EVENEMENT")){
        if (query.next()){
            QDate date1=query.value("DATE_E").toDate();
            QString id=query.value("ID").toString();
            QString nom=query.value("NOM").toString();
            QString type=query.value("TYPE").toString();
            QString lieu=query.value("LIEU").toString();
            QString nbrp=query.value("NOMBRE_PERSONNES").toString();
            QString time=query.value("TIME_E").toString();
            if (date==date1){
                ui->Event_label_CalanderInfo->setText("Date est deja reserver");
                ui->Event_label_CalanderRes->setText("Reserver par:\nID: "+id+"\nNom: "+nom+"\nType: "+type+"\nLieu :"+lieu+"\nNbr.Personnes: "+nbrp+"\nHeure: "+time+"");
            }
            else{
                ui->Event_label_CalanderInfo->setText("Date est non reserver");
                ui->Event_label_CalanderRes->clear();
            }
        }
    }
}
void MainWindow::Event_UpdateCalender(QPainter *painter, const QRect &rect){

}
/*------------INTEGRATION LINA------------*/
void MainWindow::on_Four_push_Ajouter_clicked(){
    int ID=ui->Four_line_ID->text().toInt();
    QString NOM=ui->Four_line_Nom->text();
    QString PRENOM=ui->Four_line_Prenom->text();
    QString EMAIL=ui->Four_line_Email->text();
    QString TYPE_MATERIEL=ui->Four_line_Type->text();
    QString img=ui->Four_Label_Photoname->text();
    int PRIX=ui->Four_line_Prix->text().toInt();
    fournisseur F(ID,NOM,PRENOM,EMAIL,TYPE_MATERIEL,PRIX,img);
    bool test=F.AjouterF();
    if(test)
    {A.write_to_arduino("1");
        ui->Four_Label_GestionInfo->setText("Ajout Effectué");
        ui->Four_combo_ID->setModel(F.afficher_id());
        ui->Four_TableView->setModel(F.afficher());
        F.write(F.time(),"FOURNISSEUR: Ajout effectué");
        ui->Four_textbrowser->setText(F.read());
    }
    else
    {A.write_to_arduino("0");
        ui->Four_Label_GestionInfo->setText("Ajout non Effectué");
    }
}
void MainWindow::on_Four_push_Modifier_clicked(){
    
    int ID=ui->Four_line_ID->text().toInt();
    QString NOM=ui->Four_line_Nom->text();
    QString PRENOM=ui->Four_line_Prenom->text();
    QString EMAIL=ui->Four_line_Email->text();
    QString TYPE_MATERIEL=ui->Four_line_Type->text();
    QString img=ui->Four_label_Photo->text();
    int PRIX=ui->Four_line_Prix->text().toInt();
    fournisseur F(ID,NOM,PRENOM,EMAIL,TYPE_MATERIEL,PRIX,img);
    bool test=F.ModifierF();
    if(test)
    {
        ui->Four_Label_GestionInfo->setText("Modification effectué");
        ui->Four_TableView->setModel(F.afficher());
        ui->Four_combo_ID->setModel(F.afficher_id());
        F.write(F.time(),"FOURNISSEUR: Modification effectué");
        ui->Four_textbrowser->setText(F.read());
    }
    else
    {
        ui->Four_Label_GestionInfo->setText("Modification non effectué");
    }
}
void MainWindow::on_Four_push_Supprimer_clicked(){
    fournisseur F;
    F.setid(ui->Four_combo_ID->currentText().toInt());
    bool test=F.SupprimerF(F.getid());
    if(test)
    {
        ui->Four_Label_GestionInfo->setText("Suppression effectué");
        ui->Four_TableView->setModel(F.afficher());
        ui->Four_combo_ID->setModel(F.afficher_id());
        F.write(F.time(),"FOURNISSEUR: Supression effectué");
        ui->Four_textbrowser->setText(F.read());
    }
    else
    {
        ui->Four_Label_GestionInfo->setText("Suppression non effectué");
    }
}
void MainWindow::on_Four_push_TriType_clicked(){
    ui->Four_label_ListeInfo->setText("Tri par Type Materiel effectué");
    ui->Four_TableView->setModel(F.tri_typem());
}
void MainWindow::on_Four_push_TriNom_clicked(){
    ui->Four_label_ListeInfo->setText("Tri par Nom effectué");
    ui->Four_TableView->setModel(F.tri_nom());
}
void MainWindow::on_Four_combo_ID_currentIndexChanged(int){
    int id=ui->Four_combo_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISSEUR where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Four_line_ID->setText(query.value(0).toString()) ;
            ui->Four_line_Nom->setText(query.value(1).toString()) ;
            ui->Four_line_Prenom->setText(query.value(2).toString()) ;
            ui->Four_line_Email->setText(query.value(3).toString()) ;
            ui->Four_line_Type->setText(query.value(4).toString()) ;
            ui->Four_line_Prix->setText(query.value(5).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_Four_push_Fermer_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_Four_push_UpdateStats_clicked(){
    /***** Background *****/
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(255, 255, 255));
    ui->Four_Plot->setBackground(QBrush(gradient));
    QCPBars *A = new QCPBars(ui->Four_Plot->xAxis, ui->Four_Plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);
    /***** Couleurs*****/
    A->setName("Les prix des materiels selon les ID");
    A->setPen(QPen(QColor(255, 0, 0).lighter(120)));
    A->setBrush(QColor(39, 39, 39));
    /***** Axe des abscisses *****/
    QVector<double> ticks;
    QVector<QString> labels;
    Four_statistiques(&ticks,&labels);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->Four_Plot->xAxis->setTicker(textTicker);
    ui->Four_Plot->xAxis->setTickLabelRotation(60);
    ui->Four_Plot->xAxis->setSubTicks(false);
    ui->Four_Plot->xAxis->setLabel("ID");
    ui->Four_Plot->xAxis->setTickLength(0, 4);
    ui->Four_Plot->xAxis->setRange(0, 8);
    ui->Four_Plot->xAxis->setBasePen(QPen(Qt::black));
    ui->Four_Plot->xAxis->setTickPen(QPen(Qt::black));
    ui->Four_Plot->xAxis->grid()->setVisible(true);
    ui->Four_Plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->Four_Plot->xAxis->setTickLabelColor(Qt::black);
    ui->Four_Plot->xAxis->setLabelColor(Qt::black);
    /***** Axe des ordonnées *****/
    ui->Four_Plot->yAxis->setRange(0,200);
    ui->Four_Plot->yAxis->setPadding(5);
    ui->Four_Plot->yAxis->setLabel("PRIX");
    ui->Four_Plot->yAxis->setBasePen(QPen(Qt::black));
    ui->Four_Plot->yAxis->setTickPen(QPen(Qt::black));
    ui->Four_Plot->yAxis->setSubTickPen(QPen(Qt::black));
    ui->Four_Plot->yAxis->grid()->setSubGridVisible(true);
    ui->Four_Plot->yAxis->setTickLabelColor(Qt::black);
    ui->Four_Plot->yAxis->setLabelColor(Qt::black);
    ui->Four_Plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->Four_Plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> PlaceData;
    QSqlQuery q1("SELECT PRIX FROM FOURNISSEUR");
    while (q1.next())
    {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    A->setData(ticks, PlaceData);
    ui->Four_Plot->legend->setVisible(true);
    ui->Four_Plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->Four_Plot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->Four_Plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    ui->Four_Plot->legend->setFont(legendFont);
    ui->Four_Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void MainWindow::on_envoyer_dialog_2_clicked(){
    QString status;
    Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd_2->text(), "smtp.gmail.com", 465); //smtp.gmail.com
    smtp->sendMail(ui->uname->text(), ui->recipient_2->text() , ui->subjectLineEdit_2->text() ,ui->message_2->toPlainText());
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
void MainWindow::Four_statistiques(QVector<double>* ticks,QVector<QString> *labels){
    QSqlQuery qry;
    int i=0;
    qry.exec("SELECT ID FROM FOURNISSEUR");
    while (qry.next())
    {
        QString ID = qry.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<ID;
    }
}
void MainWindow::on_Four_line_Recherche_textChanged(const QString &arg1){
    if (ui->Event_radio_ID->isChecked()==true)
    {
        F.clearTable(ui->Four_TableView);
        F.chercheID(ui->Four_TableView,arg1);
    }
    if (ui->Event_radio_Nom->isChecked()==true)
    {
        F.clearTable(ui->Four_TableView);
        F.chercheNom(ui->Four_TableView,arg1);
    }
}
void MainWindow::on_Four_push_SupprimerTextBrowser_clicked(){
    F.clearh();
    ui->Four_textbrowser->setText(L.read());
}
void MainWindow::on_Four_push_Photo_clicked(){
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr(""));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid=image.load(filename);
        if(valid)
        {
            ui->Four_Label_Photoname->setText(filename);
            image=image.scaledToWidth(ui->Four_label_Photo->width(),Qt::SmoothTransformation);
            ui->Four_label_Photo->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::information(this, tr("ERROR"), QString(tr("Not Valid!")));
        }
    }
}
void MainWindow::on_Four_TableView_pressed(const QModelIndex &index)
{
    index.data();
    QString filename = index.data().toString();
    if(QString::compare(filename,QString())!=0)
    {QImage image;
        bool valid=image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->Four_label_PhotoSelect->width(),Qt::SmoothTransformation);
            ui->Four_label_PhotoSelect->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::information(this, tr("ERROR"), QString(tr("Not Valid!")));
        }
    }
}
void MainWindow::Four_update_label()
{
    data=A.read_from_arduino();
    if(data=="1")
        ui->Four_label_Arduino->setText("ON");
    else if(data=="0")
        ui->Four_label_Arduino->setText("OFF");
    
}
/*------------INTEGRATION FARAH------------*/
void MainWindow::on_Loc_push_Ajouter_clicked(){
    QString NOM=ui->Loc_line_Nom->text();
    QString ADRESSE=ui->Loc_line_Adresse->text();
    QString SUPERFICIE=ui->Loc_line_Superficie->text();
    int NPLACES=ui->Loc_line_NbrPerso->text().toInt();
    int PRIX=ui->Loc_line_Prix->text().toInt();
    QString DESCRIPTION=ui->Loc_text_Description->toPlainText();
    locaux L(NOM,ADRESSE,SUPERFICIE,NPLACES,PRIX,DESCRIPTION);
    bool test=L.AjouterL();
    if(test)
    {
        ui->Loc_Label_GestionInfo->setText("Ajout effectué");
        ui->Loc_combo_Adresse->setModel(L.afficher_adresse());
        ui->Loc_TableView->setModel(L.afficher());
        L.write(L.time(),"LOCAUX: ajout effectué");
        ui->Loc_textbrowser->setText(L.read());
    }
    else
    {
        ui->Loc_Label_GestionInfo->setText("Ajout non effectué");
    }
}
void MainWindow::on_Loc_push_Modifier_clicked(){
    QString NOM=ui->Loc_line_Nom->text();
    QString ADRESSE=ui->Loc_line_Adresse->text();
    QString SUPERFICIE=ui->Loc_line_Superficie->text();
    int NPLACES=ui->Loc_line_NbrPerso->text().toInt();
    int PRIX=ui->Loc_line_Prix->text().toInt();
    QString DESCRIPTION=ui->Loc_text_Description->toPlainText();
    locaux L(NOM,ADRESSE,SUPERFICIE,NPLACES,PRIX,DESCRIPTION);
    bool test=L.ModifierL();
    if(test)
    {
        ui->Loc_Label_GestionInfo->setText("Modification effectué");
        ui->Loc_TableView->setModel(L.afficher());
        ui->Loc_combo_Adresse->setModel(L.afficher_adresse());
        L.write(L.time(),"LOCAUX: Modification effectuée");
        ui->Loc_textbrowser->setText(L.read());
    }
    else
    {
        ui->Loc_Label_GestionInfo->setText("Modification non effectué");
    }
}
void MainWindow::on_Loc_push_Supprimer_clicked(){
    locaux PL;
    L.setnom(ui->Loc_combo_Adresse->currentText());
    bool test=L.SupprimerL(L.getnom());
    if(test)
    {
        ui->Loc_Label_GestionInfo->setText("Suppression effectué");
        ui->Loc_TableView->setModel(L.afficher());
        ui->Loc_combo_Adresse->setModel(L.afficher_adresse());
        L.write(L.time(),"LOCAUX: Supression effectuée");
        ui->Loc_textbrowser->setText(L.read());
    }
    else
    {
        ui->Loc_Label_GestionInfo->setText("Suppression non effectué");
    }
}
void MainWindow::on_Loc_push_TriPrix_clicked(){
    ui->Loc_label_ListeInfo->setText("Tri par Prix effectué");
    ui->Loc_TableView->setModel(L.tri_Prix());
}
void MainWindow::on_Loc_push_TriNom_clicked(){
    ui->Loc_label_ListeInfo->setText("Tri par Nom effectué");
    ui->Loc_TableView->setModel(L.tri_Nom());
}
void MainWindow::on_Loc_push_TriNbrPerso_clicked(){
    ui->Loc_label_ListeInfo->setText("Tri par Nbr Places effectué");
    ui->Loc_TableView->setModel(L.tri_NbPlace());
}
void MainWindow::on_Loc_combo_Adresse_currentIndexChanged(int){
    QString adresse=ui->Loc_combo_Adresse->currentText();
    QString adresse_1=QString::const_reference(adresse);
    QSqlQuery query;
    query.prepare("SELECT * FROM LOCAUX where ADRESSE='"+adresse_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Loc_line_Nom->setText(query.value(0).toString()) ;
            ui->Loc_line_Adresse->setText(query.value(1).toString()) ;
            ui->Loc_line_Superficie->setText(query.value(2).toString()) ;
            ui->Loc_line_NbrPerso->setText(query.value(3).toString()) ;
            ui->Loc_line_Prix->setText(query.value(4).toString()) ;
            ui->Loc_text_Description->setText(query.value(5).toString()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_Loc_push_Fermer_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_Loc_push_UpdateStats_clicked(){
    /***** Background *****/
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(255, 255, 255));
    ui->Loc_Plot->setBackground(QBrush(gradient));
    QCPBars *A = new QCPBars(ui->Loc_Plot->xAxis, ui->Loc_Plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);
    /***** Couleurs*****/
    A->setName("Les Prix des Locaux selon les NOM");
    A->setPen(QPen(QColor(255, 0, 0).lighter(120)));
    A->setBrush(QColor(39, 39, 39));
    /***** Axe des abscisses *****/
    QVector<double> ticks;
    QVector<QString> labels;
    Loc_statistiques(&ticks,&labels);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->Loc_Plot->xAxis->setTicker(textTicker);
    ui->Loc_Plot->xAxis->setTickLabelRotation(60);
    ui->Loc_Plot->xAxis->setSubTicks(false);
    ui->Loc_Plot->xAxis->setLabel("NOM");
    ui->Loc_Plot->xAxis->setTickLength(0, 4);
    ui->Loc_Plot->xAxis->setRange(0, 8);
    ui->Loc_Plot->xAxis->setBasePen(QPen(Qt::black));
    ui->Loc_Plot->xAxis->setTickPen(QPen(Qt::black));
    ui->Loc_Plot->xAxis->grid()->setVisible(true);
    ui->Loc_Plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->Loc_Plot->xAxis->setTickLabelColor(Qt::black);
    ui->Loc_Plot->xAxis->setLabelColor(Qt::black);
    /***** Axe des ordonnĂ©es *****/
    ui->Loc_Plot->yAxis->setRange(0,200);
    ui->Loc_Plot->yAxis->setPadding(5);
    ui->Loc_Plot->yAxis->setLabel("PRIX");
    ui->Loc_Plot->yAxis->setBasePen(QPen(Qt::black));
    ui->Loc_Plot->yAxis->setTickPen(QPen(Qt::black));
    ui->Loc_Plot->yAxis->setSubTickPen(QPen(Qt::black));
    ui->Loc_Plot->yAxis->grid()->setSubGridVisible(true);
    ui->Loc_Plot->yAxis->setTickLabelColor(Qt::black);
    ui->Loc_Plot->yAxis->setLabelColor(Qt::black);
    ui->Loc_Plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->Loc_Plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> PlaceData;
    QSqlQuery q1("SELECT PRIX FROM LOCAUX");
    while (q1.next())
    {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    A->setData(ticks, PlaceData);
    ui->Loc_Plot->legend->setVisible(true);
    ui->Loc_Plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->Loc_Plot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->Loc_Plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    ui->Loc_Plot->legend->setFont(legendFont);
    ui->Loc_Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void MainWindow::Loc_statistiques(QVector<double>* ticks,QVector<QString> *labels){
    QSqlQuery qry;
    int i=0;
    qry.exec("SELECT NOM FROM LOCAUX");
    while (qry.next())
    {
        QString NOM = qry.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<NOM;
    }
}
void MainWindow::on_Loc_line_Recherche_textChanged(const QString &arg1){
    if (ui->Loc_radio_Adresse->isChecked()==true)
    {
        L.clearTable(ui->Loc_TableView);
        L.chercheAdresse(ui->Loc_TableView,arg1);
    }
    if (ui->Event_radio_Nom->isChecked()==true)
    {
        L.clearTable(ui->Loc_TableView);
        L.chercheNom(ui->Loc_TableView,arg1);
    }
}
void MainWindow::on_Loc_push_ExportPDF_clicked(){
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
void MainWindow::on_Loc_push_SupprimerTextBrowser_clicked(){
    L.clearh();
    ui->Loc_textbrowser->setText(L.read());
}
