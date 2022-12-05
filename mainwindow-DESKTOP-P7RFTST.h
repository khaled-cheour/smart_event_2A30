#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "evenement.h"
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>

#include <QMainWindow>
#include "evenement.h"

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

    void on_pB_SupprimerP_clicked();

    void on_pB_ModifierP_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TireParType_clicked();

    void on_pB_TirerParNbPersonnes_clicked();

    void on_pushButton_SupprimerE_clicked();

    void on_comboBox_EventID_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

    void on_pB_TirerParNbPersonnes_2_clicked();

    void on_pB_TirerParNbPersonnes_3_clicked();

    void on_pb_TirerParRechreche_clicked();

    void on_pb_TirerParRechrecheNUM__clicked();

    void on_pB_Recherche_clicked();

    void on_pB_Recherche_2_clicked();

    void on_facture_clicked();

    void on_pb_excel_clicked();

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    evenement E;
    QProgressBar* bar;
    QSlider* slider;
};
#endif // MAINWINDOW_H
