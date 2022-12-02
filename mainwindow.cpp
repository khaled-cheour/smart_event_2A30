#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_perso.h"
#include "connexion.h"
#include "arduino.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_GestionPersonnelsMain_clicked()
{
    this->hide();
    Dialog_perso personnel;
    personnel.setModal(true);
    personnel.exec();
}

void MainWindow::on_pushButton_QuitterMain_clicked()
{
    close();
}

