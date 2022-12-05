#ifndef DIALOG_STATS_H
#define DIALOG_STATS_H
#include <QtCharts>

#include <QDialog>
#include "QtPrintSupport"

namespace Ui {
class Dialog_Stats;
}

class Dialog_Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Stats(QWidget *parent = nullptr);

        int G_PVS1();
            int G_PVS2();
            int G_PVS3();
            int G_PVS4();
            int G_PVS5();
            int G_PVS6();
            int G_PVS7();
            int G_PVS8();
            int G_PVS9();
            int G_PVS10();


            QChartView* piechart();
    ~Dialog_Stats();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::Dialog_Stats *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // DIALOG_STATS_H
