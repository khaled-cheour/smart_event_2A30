#ifndef DIALOG_LOCAUX_H
#define DIALOG_LOCAUX_H

#include <QDoubleValidator>
#include <QDialog>
#include "local.h"

namespace Ui {
class Dialog_Locaux;
}

class Dialog_Locaux : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Locaux(QWidget *parent = nullptr);
    ~Dialog_Locaux();

private slots:
    void on_pB_AjouterP_clicked();

    void on_pB_SupprimerP_clicked();

    void on_pB_ModifierP_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TireParPrix_clicked();

    void on_pB_TirerParNbPlaces_clicked();

    void on_pushButton_SupprimerL_clicked();

    void on_comboBox_Nomloc_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_Locaux *ui;
    local L;
};

#endif // DIALOG_LOCAUX_H
