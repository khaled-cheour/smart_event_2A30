#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_perso.h"
#include "connexion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_GestionPersonnelsMain_clicked();

    void on_pushButton_QuitterMain_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
