#include "dialog_stats.h"
#include "ui_dialog_stats.h"
#include "qcustomplot.h"
#include "mainwindow.h"
#include "evenement.h"
#include <QtCharts>



Dialog_Stats::Dialog_Stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Stats)
{
    ui->setupUi(this);
    //Dialog_Stats::MakeStat();
}

Dialog_Stats::~Dialog_Stats()
{
    delete ui;
}
/*void Dialog_Stats::statistiques(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery qry;
    int i=0;
    qry.exec("SELECT COUNT(*) FROM EVENTMENT");
    while (qry.next())
    {
        QString ID = qry.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<ID;
    }
}*/
/*
void Dialog_Stats::MakeStat()
{

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(255, 255, 255));
    ui->plot->setBackground(QBrush(gradient));
    QCPBars *A = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);

    A->setName("Les Montants des reservations selon les ID");
    A->setPen(QPen(QColor(255, 0, 0).lighter(120)));
    A->setBrush(QColor(39, 39, 39));

    QVector<double> ticks;
    QVector<QString> labels;
    statistiques(&ticks,&labels);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->plot->xAxis->setTicker(textTicker);
    ui->plot->xAxis->setTickLabelRotation(60);
    ui->plot->xAxis->setSubTicks(false);
    ui->plot->xAxis->setLabel("ID");
    ui->plot->xAxis->setTickLength(0, 4);
    ui->plot->xAxis->setRange(0, 8);
    ui->plot->xAxis->setBasePen(QPen(Qt::black));
    ui->plot->xAxis->setTickPen(QPen(Qt::black));
    ui->plot->xAxis->grid()->setVisible(true);
    ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->plot->xAxis->setTickLabelColor(Qt::black);
    ui->plot->xAxis->setLabelColor(Qt::black);

    ui->plot->yAxis->setRange(0,10);
    ui->plot->yAxis->setPadding(5);
    ui->plot->yAxis->setLabel("MONTANT");
    ui->plot->yAxis->setBasePen(QPen(Qt::black));
    ui->plot->yAxis->setTickPen(QPen(Qt::black));
    ui->plot->yAxis->setSubTickPen(QPen(Qt::black));
    ui->plot->yAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->setTickLabelColor(Qt::black);
    ui->plot->yAxis->setLabelColor(Qt::black);
    ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> PlaceData;
    QSqlQuery q1("SELECT TYPE FROM EVENTMENT");
    while (q1.next())
    {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    A->setData(ticks, PlaceData);
    ui->plot->legend->setVisible(true);
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    ui->plot->legend->setFont(legendFont);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
*/
void Dialog_Stats::on_tabWidget_currentChanged(int index)
{
 //   QChartView* piechart();
    qDeleteAll(ui->tabWidget->widget(1)->children());
        QWidget* piestats = new QWidget(this);
       piestats = piechart();
        QGridLayout* layout1 = new QGridLayout(this);
        layout1->addWidget(piestats, 0, 0); // Top-Left
        layout1->addWidget(NULL, 0, 1); // Top-Right
        layout1->addWidget(NULL, 1, 0); // Bottom-Left
        layout1->addWidget(NULL, 1, 1); // Bottom-Right
        ui->tab->setLayout(layout1);
}
