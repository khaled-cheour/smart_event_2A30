#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include "connexion.h"
#include "personnel.h"
#include "locaux.h"
#include "fournisseur.h"
#include "sponsoring.h"
#include "arduino.h"
#include "evenement.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDialog>
#include <QSettings>
#include <QDataStream>
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QTcpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QString,QString,QString,QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_Login_push_Login_clicked();
    void on_Main_push_Personnel_clicked();
    void on_Main_push_Evenement_clicked();
    void on_Main_push_Fournisseur_clicked();
    void on_Main_push_Locaux_clicked();
    void on_Main_push_Sponsoring_clicked();
    void on_Main_push_Quitter_clicked();
    /*INTEGRATION KHALED*/
    void on_Perso_push_Ajouter_clicked();
    void on_Perso_push_Modifier_clicked();
    void on_Perso_push_Supprimer_clicked();
    void on_Perso_push_Photo_clicked();
    void on_Perso_push_TriCIN_clicked();
    void on_Perso_push_TriNom_clicked();
    void on_Perso_push_TriEmail_clicked();
    void on_Perso_push_SupprimerTextBrowser_clicked();
    void on_Perso_push_UpdateStats_clicked();
    void on_Perso_push_Fermer_clicked();
    void on_Perso_push_Send_clicked();
    void on_Perso_push_Bind_clicked();
    void on_Perso_combo_CIN_currentIndexChanged(int index);
    void on_Perso_line_Recherche_textChanged(const QString &arg1);
    void Perso_choix_pie();
    void updateMDM();
    void on_Perso_TableView_pressed(const QModelIndex &index);
    void update_RFID();
    void on_Perso_push_Arduino_clicked();
    /*INTEGRATION ALA*/
    void on_Sponso_push_Ajouter_clicked();
    void on_Sponso_push_Modifier_clicked();
    void on_Sponso_push_Supprimer_clicked();
    void on_Sponso_push_TriID_clicked();
    void on_Sponso_push_TriNumTel_clicked();
    void on_Sponso_push_SupprimerTextBrowser_clicked();
    void on_Sponso_combo_ID_currentIndexChanged(int index);
    void on_Sponso_combo_IDSMS_currentIndexChanged(int index);
    void on_Sponso_line_Recherche_textChanged(const QString &arg1);
    void on_Sponso_push_Play_clicked();
    void on_Sponso_push_Stop_clicked();
    void on_Sponso_push_EnvoyerSMS_clicked();
    void on_Sponso_push_UpdateStats_clicked();
    void on_Sponso_push_ExportPDF_clicked();
    void on_Sponso_push_Fermer_clicked();
    void Sponso_choix_pie();
    /*INTEGRATION AZIZ*/
    void on_Event_push_Ajouter_clicked();
    void on_Event_push_Modifier_clicked();
    void on_Event_push_Supprimer_clicked();
    void on_Event_push_TriID_clicked();
    void on_Event_push_TriNbrPerso_clicked();
    void on_Event_push_TriType_clicked();
    void on_Event_push_SupprimerTextBrowser_clicked();
    void on_Event_line_Recherche_textChanged(const QString &arg1);
    void on_Event_combo_ID_currentIndexChanged(int index);
    void on_Event_combo_IDCalander_currentIndexChanged(int index);
    void on_Event_push_Excel_clicked();
    void on_Event_push_Fermer_clicked();
    void on_Event_Calander_selectionChanged();
    void on_Event_radio_ASC_clicked();
    void on_Event_radio_DESC_clicked();
    void Event_MakeStat();
    void Event_statistiques(QVector<double>* ticks,QVector<QString> *labels);
    /*INTEGRATION LINA*/
    void on_Four_push_Ajouter_clicked();
    void on_Four_push_Modifier_clicked();
    void on_Four_push_Supprimer_clicked();
    void on_Four_push_TriType_clicked();
    void on_Four_push_TriNom_clicked();
    void on_Four_combo_ID_currentIndexChanged(int index);
    void on_Four_push_Fermer_clicked();
    void on_Four_push_SupprimerTextBrowser_clicked();
    void Four_MakeStat();
    void on_Four_TableView_pressed(const QModelIndex &index);
    void Four_statistiques(QVector<double>* ticks,QVector<QString> *labels);
    void on_Four_line_Recherche_textChanged(const QString &arg1);
    void on_Four_push_Photo_clicked();
    void set_tmpemail(QString e){tmpemail=e;}
    void on_envoyer_dialog_2_clicked();
    /*INTEGRATION FARAH*/
    void on_Loc_push_Ajouter_clicked();
    void on_Loc_push_Modifier_clicked();
    void on_Loc_push_Supprimer_clicked();
    void on_Loc_push_TriPrix_clicked();
    void on_Loc_push_TriNom_clicked();
    void on_Loc_push_TriNbrPerso_clicked();
    void on_Loc_combo_ID_currentIndexChanged(int index);
    void on_Loc_push_Fermer_clicked();
    void on_Loc_push_SupprimerTextBrowser_clicked();
    void Loc_MakeStat();
    void Loc_statistiques(QVector<double>* ticks,QVector<QString> *labels);
    void on_Loc_line_Recherche_textChanged(const QString &arg1);
    void on_Loc_push_ExportPDF_clicked();
private:
    Ui::MainWindow *ui;
    personnel P;
    QString RFID="";
    int selected=0;
    QByteArray data;
    Arduino A;
    locaux L;
    sponsoring S;
    evenement E;
    fournisseur F;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QTcpSocket *nSocket;
    QString tmpemail;
};
#endif // MAINWINDOW_H
