#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "sponsoring.h"
#include "dialog_statistiques.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

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
    void on_pB_Ajouter_clicked();

    void on_pB_Modifier_clicked();

    void on_pB_Supprimer_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TirerParID_clicked();

    void on_pushButton_SupprimerS_clicked();

    void on_comboBox_ID_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

    void on_pB_ExPDF_clicked();

    void on_pB_Stats_clicked();

    void on_pushPlay_clicked();

    void on_pushStop_clicked();

    void on_pB_EnvoyerSMS_clicked(); void postrequest(QString smsmsg,QString phonenumber);

    void on_lineEdit_IDRecherche_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    sponsoring S;
    Dialog_Statistiques *DS;

    QMediaPlayer* player;
    QVideoWidget* vw;

    int selected=0;
};
#endif // MAINWINDOW_H
