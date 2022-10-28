#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_menu.h"
#include "login_bd.h"
#include "connexion.h"
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connexion c;
    bool test=c.CreateConnexion();
    if(test)
    ui->label_DataBase->setText("Datebase: Open.\nConnection: Successful.");
    else
    ui->label_DataBase->setText("Datebase: Closed.\nConnection: Failed.");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_LoginL_clicked()
{
    QString USERNAME = ui->lineEdit_UsernameL->text();
    QString PASSWORD = ui->lineEdit_PasswordL->text();
    QSqlQuery query;
    if(query.exec("SELECT* from LOGIN where USERNAME ='" + USERNAME + "' and PASSWORD ='" + PASSWORD + "' " ))
    {
        int count=0;
        while (query.next())
        {
            count++;
        }
        if (count==1)
            ui->label_LoginInfo->setText("Username et Password sont correct");
        this->hide();
        Dialog_menu menu;
        menu.setModal(true);
        menu.exec();
        if (count!=1)
            ui->label_LoginInfo->setText("Username et Password sont incorrect");
    }
}
