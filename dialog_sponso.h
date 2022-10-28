#ifndef DIALOG_SPONSO_H
#define DIALOG_SPONSO_H

#include <QDialog>
#include <QDoubleValidator>
#include "sponsoring.h"
#
namespace Ui {
class Dialog_sponso;
}

class Dialog_sponso : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_sponso(QWidget *parent = nullptr);
    ~Dialog_sponso();

private slots:
    void on_pB_Ajouter_clicked();

    void on_pB_Supprimer_clicked();

    void on_pB_Modifier_clicked();

    void on_pB_TirerParID_clicked();

    void on_pB_TirerParNumtel_clicked();

    void on_pushButton_SupprimerS_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_sponso *ui;
    sponsoring S;
};

#endif // DIALOG_SPONSO_H
