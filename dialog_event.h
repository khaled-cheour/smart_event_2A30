#ifndef DIALOG_EVENT_H
#define DIALOG_EVENT_H

#include <QDialog>
#include "evenement.h"

namespace Ui {
class Dialog_event;
}

class Dialog_event : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_event(QWidget *parent = nullptr);
    ~Dialog_event();

private slots:
    void on_pB_AjouterP_clicked();

    void on_pB_SupprimerP_clicked();

    void on_pB_ModifierP_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TireParType_clicked();

    void on_pB_TirerParNbPersonnes_clicked();

    void on_pushButton_SupprimerE_clicked();

    void on_comboBox_Nomloc_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_event *ui;
    evenement E;

};

#endif // DIALOG_EVENT_H
