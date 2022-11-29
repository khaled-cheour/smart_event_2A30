#ifndef EMPLOYE_DU_MOI_H
#define EMPLOYE_DU_MOI_H

#include <QDialog>

namespace Ui {
class employe_du_moi;
}

class employe_du_moi : public QDialog
{
    Q_OBJECT

public:
    explicit employe_du_moi(QWidget *parent = nullptr);
    ~employe_du_moi();
    void employe_moi();

private:
    Ui::employe_du_moi *ui;
};

#endif // EMPLOYE_DU_MOI_H
