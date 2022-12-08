#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSerialPort>
#include <QSerialPortInfo>
QT_CHARTS_USE_NAMESPACE
class personnel
{
public:
    personnel();
    personnel(int,QString,QString,QString,QDate,QString,QString,QString,int,QString,QString,QString);

    int getcin();
    QString getnom();
    QString getprenom();
    QString getgender();
    QDate getdate();
    QString getemail();
    QString getadresse();
    QString getgestion();
    int getabsance();
    QString getrfid();
    QString getphoto();

    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setgender(QString);
    void setdate(QDate);
    void setemail(QString);
    void setadresse(QString);
    void setgestion(QString);
    void setabsance(int);
    void setrfid(QString);
    void setphoto(QString);

    bool ajouter();
    bool modifierP();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* tri_cin();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_email();
    QSqlQueryModel* triMDM();
    QSqlQueryModel* afficher_MDM();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void chercheCIN(QTableView *table, QString x);
    void chercheNom(QTableView *table, QString x);
    void choix_pie();
    QString PASSWORD;

private:
    int CIN;
    QString NOM;
    QString PRENOM;
    QString GENDER;
    QDate DATE_DE_NAISSANCE;
    QString EMAIL;
    QString ADRESSE;
    QString GESTION;
    int ABSANCE;
    QString RFID;
    QString PHOTO;
};

#endif // PERSONNEL_H
