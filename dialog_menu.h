#ifndef DIALOG_MENU_H
#define DIALOG_MENU_H

#include <QDialog>
#include "dialog_event.h"
#include "dialog_sponso.h"
#include "dialog_perso.h"
#include "dialog_locaux.h"
#include "dialog_fourni.h"
#include "mainwindow.h"

namespace Ui {
class Dialog_menu;
}

class Dialog_menu : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_menu(QWidget *parent = nullptr);
    ~Dialog_menu();

private slots:
    void on_pushButton_GestionPersonnelsMain_clicked();

    void on_pushButton_GestionEvenementsMain_clicked();

    void on_pushButton_GestionFournisseurMain_clicked();

    void on_pushButton_GestionLocauxMain_clicked();

    void on_pushButton_GestionSponsorsMain_clicked();

    void on_pushButton_QuitterMain_clicked();

private:
    Ui::Dialog_menu *ui;
};

#endif // DIALOG_MENU_H
