#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "personnel.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_LoginL_clicked()
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
            ui->label_2->setText("Username et Password sont correct");
            if (count>1)
            ui->label_2->setText("Meme Username et Password");
            if (count<1)
            ui->label_2->setText("Username et Password sont incorrect");
        }
}
