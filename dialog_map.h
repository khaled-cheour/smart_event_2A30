#ifndef DIALOG_MAP_H
#define DIALOG_MAP_H

#include <QDialog>
#include <QSettings>
#include <QDataStream>
namespace Ui {
class Dialog_map;
}

class Dialog_map : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_map(QWidget *parent = nullptr);
    ~Dialog_map();
private slots:
    void on_pushButton_Fermer_clicked();
private:
    Ui::Dialog_map *ui;
};

#endif // DIALOG_MAP_H
