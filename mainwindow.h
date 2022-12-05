#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include "fournisseur.h"
#include "arduino.h"


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
    void on_pB_AjouterF_clicked();

    void on_pB_SupprimerF_clicked();

    void on_pB_ModifierF_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TirerParTypeM_clicked();

    void on_pushButton_SupprimerF_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

    void on_pB_TirerParTypeM_2_clicked();

    void on_pB_sts_clicked();

    //void on_insertimg_clicked();

    //void on_label_linkActivated(const QString &link);

    void on_pB_sts_2_clicked();
void update_label();


void on_image_2_clicked();

void on_tab_Fournisseur_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QByteArray data;
    fournisseur F;
    Arduino A;
};



//void on_insertimg_clicked();


#endif // MAINWINDOW_H
