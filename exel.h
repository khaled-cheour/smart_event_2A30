#ifndef EXEL_H
#define EXEL_H

#include <QDialog>

namespace Ui {
class exel;
}

class exel : public QDialog
{
    Q_OBJECT

public:
    explicit exel(QWidget *parent = nullptr);
    ~exel();

private:
    Ui::exel *ui;
};

#endif // EXEL_H
