#ifndef SPONSORING_H
#define SPONSORING_H
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
QT_CHARTS_USE_NAMESPACE
class sponsoring
{
public:
    sponsoring();
    sponsoring(int,int,QString,QString);

    int getid();
    int getnumtel();
    QString getdescription();
    QString getpack();
    void setid(int);
    void setnumtel(int);
    void setdescription(QString);
    void setpack(QString);
    bool ajouterS();
    bool modifierS();
    bool supprimerS(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_numtel();
    void postrequest(QString smsmsg,QString phonenumber);
    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void chercheID(QTableView *table, QString x);
    void chercheNumTel(QTableView *table, QString x);
private:
    int ID;
    int NUM_TEL;
    QString DESCRIPTION;
    QString PACK;
};

#endif // SPONSORING_H
