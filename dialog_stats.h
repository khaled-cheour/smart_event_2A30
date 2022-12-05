#ifndef DIALOG_STATS_H
#define DIALOG_STATS_H

#include <QDialog>
#include "QtPrintSupport"


namespace Ui {
class Dialog_stats;
}

class Dialog_stats : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_stats(QWidget *parent = nullptr);
    ~Dialog_stats();

private:
    Ui::Dialog_stats *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // DIALOG_STATS_H
