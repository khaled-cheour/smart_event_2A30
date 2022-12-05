#include "mainwindow.h"
#include "dialog_stats.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <string>
#include <QMessageBox>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QtCharts>
#include "evenement.h"

QChartView* Dialog_Stats::piechart()
{

    QPieSeries *series = new QPieSeries();
    series->append("mariage ", 1);
    series->append("anniversaire", 2);
    series->append("conferance", 3);
    series->append("lancement de produit", 4);
    series->append("soirée ", 5);
    series->append("festival ", 6);
    series->append("concert ", 7);
    series->append(" congres", 8);
    series->append("seminaire ", 9);
    series->append("autres", 10);



    // Add label to 1st slice

    QPieSlice *slice0 = series->slices().at(0);
    slice0->setExploded();
    slice0->setLabelVisible();
    slice0->setPen(QPen(Qt::blue, 2));
    slice0->setBrush(Qt::blue);

    // Add label, explode and define brush for 2nd slice
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setExploded();
    slice1->setLabelVisible();
    slice1->setPen(QPen(Qt::green, 2));
    slice1->setBrush(Qt::green);

    // Add labels to rest of slices
    QPieSlice *slice2 = series->slices().at(2);
    slice2->setExploded();
    slice2->setLabelVisible();
    slice2->setPen(QPen(Qt::red, 2));
    slice2->setBrush(Qt::red);

    QPieSlice *slice3 = series->slices().at(3);
    slice3->setExploded();
    slice3->setLabelVisible();
    slice3->setPen(QPen(Qt::yellow, 2));
    slice3->setBrush(Qt::yellow);


    QPieSlice *slice4 = series->slices().at(4);
    slice4->setExploded();
    slice4->setLabelVisible();
    slice4->setPen(QPen(Qt::black, 2));
    slice4->setBrush(Qt::black);


    QPieSlice *slice5 = series->slices().at(5);
    slice5->setExploded();
    slice5->setLabelVisible();
    slice5->setPen(QPen(Qt::gray, 2));
    slice5->setBrush(Qt::gray);

    QPieSlice *slice6 = series->slices().at(6);
    slice6->setExploded();
    slice6->setLabelVisible();
    slice6->setPen(QPen(Qt::white, 2));
    slice6->setBrush(Qt::white);

    QPieSlice *slice7 = series->slices().at(7);
    slice7->setExploded();
    slice7->setLabelVisible();
    slice7->setPen(QPen(Qt::darkBlue, 2));
    slice7->setBrush(Qt::darkBlue);

    QPieSlice *slice8 = series->slices().at(8);
    slice8->setExploded();
    slice8->setLabelVisible();
    slice8->setPen(QPen(Qt::darkRed, 2));
    slice8->setBrush(Qt::darkRed);

    QPieSlice *slice9 = series->slices().at(9);
    slice9->setExploded();
    slice9->setLabelVisible();
    slice9->setPen(QPen(Qt::darkYellow, 2));
    slice9->setBrush(Qt::darkYellow);




    series->slices().at(0)->setValue(G_PVS1());
    series->slices().at(1)->setValue(G_PVS2());
    series->slices().at(2)->setValue(G_PVS3());
    series->slices().at(3)->setValue(G_PVS4());
    series->slices().at(4)->setValue(G_PVS5());
    series->slices().at(5)->setValue(G_PVS6());
    series->slices().at(6)->setValue(G_PVS7());
    series->slices().at(7)->setValue(G_PVS8());
    series->slices().at(8)->setValue(G_PVS9());
    series->slices().at(9)->setValue(G_PVS10());



/*
    series->slices().at(0)->setBrush(Qt::blue);
    series->slices().at(1)->setBrush(Qt::green);
    series->slices().at(2)->setBrush(Qt::red);
    series->slices().at(3)->setBrush(Qt::yellow);
    series->slices().at(4)->setBrush(Qt::black);
    series->slices().at(5)->setBrush(Qt::gray);
    series->slices().at(6)->setBrush(Qt::white);
    series->slices().at(7)->setBrush(Qt::darkBlue);
    series->slices().at(8)->setBrush(Qt::darkRed);
    series->slices().at(9)->setBrush(Qt::darkYellow);
    series->slices().at(10)->setBrush(Qt::darkMagenta);
    series->slices().at(11)->setBrush(Qt::darkGreen);
    series->slices().at(12)->setBrush(Qt::darkGray);
*/
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(" type des evenements ");


    QChartView *chartView1 = new QChartView(chart);
    chartView1->setRenderHint(QPainter::Antialiasing);
    return chartView1;
}

int Dialog_Stats::G_PVS1()
{
    int c22=0;
    QSqlQuery qry22;
    qry22.prepare("SELECT *  FROM EVENEMENT WHERE type ='mariage' ");
    qry22.exec();
    while(qry22.next())
    {
        c22++;
    }
    return c22;
}

int Dialog_Stats::G_PVS2()
{
    int c21=0;
    QSqlQuery qry21;
    qry21.prepare("SELECT COUNT(*)  FROM EVENEMENT WHERE type='anniversaire' ");
    qry21.exec();
    while(qry21.next())
    {
        c21++;
    }
    return c21;
}

int Dialog_Stats::G_PVS3()
{
    int c20=0;
    QSqlQuery qry20;
    qry20.prepare("SELECT *  FROM EVENEMENT WHERE type='conferance'  ");
    qry20.exec();
    while(qry20.next())
    {
        c20++;
    }
    return c20;
}

int Dialog_Stats::G_PVS4()
{
    int c19=0;
    QSqlQuery qry19;
    qry19.prepare("SELECT *   FROM EVENEMENT WHERE type='lancement de produit' ");
    qry19.exec();
    while(qry19.next())
    {
        c19++;
    }
    return c19;
}

int Dialog_Stats::G_PVS5()
{
    int c18=0;
    QSqlQuery qry18;
    qry18.prepare("SELECT *  FROM EVENEMENT WHERE type='soirée' ");
    qry18.exec();
    while(qry18.next())
    {
        c18++;
    }
    return c18;
}

int Dialog_Stats::G_PVS6()
{
    int c17=0;
    QSqlQuery qry17;
    qry17.prepare("SELECT  * FROM EVENEMENT WHERE type='festival' ");
    qry17.exec();
    while(qry17.next())
    {
        c17++;
    }
    return c17;
}

int Dialog_Stats::G_PVS7()
{
    int c16=0;
    QSqlQuery qry16;
    qry16.prepare("SELECT *FROM EVENEMENT WHERE type='concert' ");
    qry16.exec();
    while(qry16.next())
    {
        c16++;
    }
    return c16;
}

int Dialog_Stats::G_PVS8()
{
    int c15=0;
    QSqlQuery qry15;
    qry15.prepare("SELECT *  FROM EVENEMENT WHERE type='congres' ");
    qry15.exec();
    while(qry15.next())
    {
        c15++;
    }
    return c15;
}

int Dialog_Stats::G_PVS9()
{
    int c14=0;
    QSqlQuery qry14;
    qry14.prepare("SELECT *  FROM EVENEMENT WHERE type='seminaire' ");
    qry14.exec();
    while(qry14.next())
    {
        c14++;
    }
    return c14;
}

int Dialog_Stats::G_PVS10()
{
    int c13=0;
    QSqlQuery qry13;
    qry13.prepare("SELECT *  FROM EVENEMENT WHERE type='autres' ");
    qry13.exec();
    while(qry13.next())
    {
        c13++;
    }
    return c13;
}


