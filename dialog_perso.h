#ifndef DIALOG_PERSO_H
#define DIALOG_PERSO_H

#include <QDoubleValidator>
#include <QDialog>
#include "personnel.h"

namespace Ui {
class Dialog_perso;
}

class Dialog_perso : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_perso(QWidget *parent = nullptr);
    ~Dialog_perso();

private slots:
    void on_pB_AjouterP_clicked();

    void on_pB_SupprimerP_clicked();

    void on_pB_ModifierP_clicked();

    void on_pushButton_InsererPhotoPerso_clicked();

    void on_pB_TireParCIN_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TirerParEmail_clicked();

    void on_pushButton_SupprimerP_clicked();

    void on_pushButton_Fermer_clicked();

    void on_comboBox_CIN_currentIndexChanged(int index);

private:
    Ui::Dialog_perso *ui;
    personnel P;
};

#endif // DIALOG_PERSO_H
