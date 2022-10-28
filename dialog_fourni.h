#ifndef DIALOG_FOURNI_H
#define DIALOG_FOURNI_H

#include <QDialog>
#include <QDoubleValidator>
#include "fournisseur.h"

namespace Ui {
class Dialog_Fourni;
}

class Dialog_Fourni : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Fourni(QWidget *parent = nullptr);
    ~Dialog_Fourni();

private slots:
    void on_pB_AjouterF_clicked();

    void on_pB_SupprimerF_clicked();

    void on_pB_ModifierF_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TirerParTypeM_clicked();

    void on_pushButton_SupprimerF_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_Fourni *ui;
    fournisseur F;
};

#endif // DIALOG_FOURNI_H
