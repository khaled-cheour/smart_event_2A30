#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sponsoring.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pB_Ajouter_clicked();

    void on_pB_Modifier_clicked();

    void on_pB_Supprimer_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TirerParID_clicked();

    void on_pushButton_SupprimerS_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

    void on_pB_ExPDF_clicked();

    void on_pB_Recherche_clicked();

    void on_pB_Stats_clicked();

private:
    Ui::MainWindow *ui;
    sponsoring S;
};
#endif // MAINWINDOW_H
