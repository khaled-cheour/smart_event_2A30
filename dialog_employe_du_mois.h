#ifndef DIALOG_EMPLOYE_DU_MOIS_H
#define DIALOG_EMPLOYE_DU_MOIS_H

#include <QDialog>

namespace Ui {
class Dialog_employe_du_mois;
}

class Dialog_employe_du_mois : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_employe_du_mois(QWidget *parent = nullptr);
    ~Dialog_employe_du_mois();
    void employe_mois();

private:
    Ui::Dialog_employe_du_mois *ui;
};

#endif // DIALOG_EMPLOYE_DU_MOIS_H
