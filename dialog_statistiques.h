#ifndef DIALOG_STATISTIQUES_H
#define DIALOG_STATISTIQUES_H

#include <QDialog>

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

namespace Ui {
class Dialog_Statistiques;
}

class Dialog_Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Statistiques(QWidget *parent = nullptr);
    ~Dialog_Statistiques();

    QChartView *chartView ;
    void choix_bar();
    void choix_pie();

private slots:
    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_Statistiques *ui;
};

#endif // DIALOG_STATISTIQUES_H
