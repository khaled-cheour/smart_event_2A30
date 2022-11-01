# #ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDoubleValidator>
#include <QMainWindow>
#include "personnel.h"

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
    void on_pB_AjouterP_clicked();

    void on_pB_ModifierP_clicked();

    void on_pB_SupprimerP_clicked();

    void on_pB_TirerParEmail_clicked();

    void on_pB_TirerParNom_clicked();

    void on_pB_TireParCIN_clicked();

    void on_comboBox_CIN_currentIndexChanged(int index);

    void on_pushButton_Fermer_clicked();

    void on_pushButton_SupprimerP_clicked();

    void on_pushButton_InsererPhotoPerso_clicked();

private:
    Ui::MainWindow *ui;
    personnel P;
};
#endif // MAINWINDOW_H
