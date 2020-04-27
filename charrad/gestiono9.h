#ifndef GESTIONO9_H
#define GESTIONO9_H

#include <QDialog>
#include "deponse.h"
#include "revenu.h"
#include <QMessageBox>
#include "QSystemTrayIcon"

namespace Ui {
class gestiono9;
}

class gestiono9 : public QDialog
{
    Q_OBJECT

public:
    explicit gestiono9(QWidget *parent = nullptr);
    ~gestiono9();

private slots:
    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_8_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_28_textChanged(const QString &arg1);

    void on_pushButton_21_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();


    void on_pushButton_15_clicked();



    void on_pushButton_16_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_eleves_3_clicked();


    void on_pushButton_12_clicked();

private:
    Ui::gestiono9 *ui;
    deponse d0;
    revenu r0;
    QSystemTrayIcon *notifyicon;
};

#endif // GESTIONO9_H
