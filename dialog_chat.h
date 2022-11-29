#ifndef DIALOG_CHAT_H
#define DIALOG_CHAT_H

#include <QDialog>


namespace Ui {
class Dialog_chat;
}

class Dialog_chat : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_chat(QWidget *parent = nullptr);
    ~Dialog_chat();
    void choix_chat();


private slots:
    void on_pushButton_envoyer_clicked();

private:
    Ui::Dialog_chat *ui;
};

#endif // DIALOG_CHAT_H
