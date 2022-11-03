#ifndef DIALOG_STATISTIQUES_H
#define DIALOG_STATISTIQUES_H

#include <QDialog>
#include "QtPrintSupport"

namespace Ui {
class Dialog_Statistiques;
}

class Dialog_Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Statistiques(QWidget *parent = nullptr);
    ~Dialog_Statistiques();

private slots:
    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_Statistiques *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // DIALOG_STATISTIQUES_H
