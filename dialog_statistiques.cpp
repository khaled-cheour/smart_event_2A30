#include "dialog_statistiques.h"
#include "ui_dialog_statistiques.h"
#include "sponsoring.h"
#include "qcustomplot.h"
#include "mainwindow.h"

Dialog_Statistiques::Dialog_Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Statistiques)
{
    ui->setupUi(this);
    Dialog_Statistiques::MakeStat();
}

Dialog_Statistiques::~Dialog_Statistiques()
{
    delete ui;
}

void Dialog_Statistiques::statistiques(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery qry;
    int i=0;
    qry.exec("SELECT ID FROM SPONSORING");
    while (qry.next())
    {
        QString ID = qry.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<ID;
    }
}
void Dialog_Statistiques::MakeStat()
{
    // Background
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(182, 182, 182));
    ui->plot->setBackground(QBrush(gradient));
    QCPBars *A = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);

    // Couleurs
    A->setName("Repartition des sponsors selon l'ID");
    A->setPen(QPen(QColor(255, 0, 0).lighter(120)));
    A->setBrush(QColor(39, 39, 39));

    // Axe des abscisses
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

    // Axe des ordonnées
    ui->plot->yAxis->setRange(0,200);
    ui->plot->yAxis->setPadding(5);
    ui->plot->yAxis->setLabel("NUM_TEL");
    ui->plot->yAxis->setBasePen(QPen(Qt::black));
    ui->plot->yAxis->setTickPen(QPen(Qt::black));
    ui->plot->yAxis->setSubTickPen(QPen(Qt::black));
    ui->plot->yAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->setTickLabelColor(Qt::black);
    ui->plot->yAxis->setLabelColor(Qt::black);
    ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Ajout des données (statistiques de la quantite)
    QVector<double> PlaceData;
    QSqlQuery q1("SELECT NUM_TEL FROM SPONSORING");
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

void Dialog_Statistiques::on_pushButton_Fermer_clicked()
{
    close();
}
