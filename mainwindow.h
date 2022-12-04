#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "locaux.h"
#include <QDoubleValidator>


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
    void on_pB_AjouterP_clicked();

    void on_pB_ModifierP_clicked();

    void on_pB_SupprimerP_clicked();

    void on_pB_TirerParNbPlaces_clicked();

    void on_pB_TireParPrix_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pushButton_SupprimerL_clicked();

    void on_comboBox_Nomloc_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

    void on_pushButton_Stats_clicked();

    void on_pushButton_map_clicked();

    void on_pushButton_pdf_clicked();

    void on_pB_Recherh_clicked();

private:
    Ui::MainWindow *ui;
    locaux L;
};
#endif // MAINWINDOW_H
