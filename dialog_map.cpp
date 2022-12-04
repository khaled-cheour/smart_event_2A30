#include "dialog_map.h"
#include "ui_dialog_map.h"

Dialog_map::Dialog_map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_map)
{
    ui->setupUi(this);
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
}

Dialog_map::~Dialog_map()
{
    delete ui;
}
void Dialog_map::on_pushButton_Fermer_clicked()
{
    close();
}
