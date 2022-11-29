#ifndef DIALOG_PERSO_H
#define DIALOG_PERSO_H

#include <QDoubleValidator>
#include <QDialog>
#include "dialog_stats.h"
#include "dialog_chat.h"
#include "personnel.h"
#include "dialog_employe_du_mois.h"

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

    void on_pushButton_recherche_clicked();

    void on_pushButton_employe_de_mois_clicked();

    void on_pushButton_PorteP_4_clicked();

    void on_pushButton_chatbox_clicked();

    void on_pushButton_employe_de_mois1_clicked();

    void on_pB_pdf_clicked();

private:
    Ui::Dialog_perso *ui;
    Dialog_stats *DS;
    Dialog_chat *DC;

    personnel P;
};

#endif // DIALOG_PERSO_H
