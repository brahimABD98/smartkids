#ifndef GESTION_EMPLOYE_H
#define GESTION_EMPLOYE_H
#include "staff_technique.h"
#include "instituteur.h"
#include <QDialog>

namespace Ui {
class gestion_employe;
}

class gestion_employe : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_employe(QWidget *parent = nullptr);
    ~gestion_employe();
private slots:
    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_26_clicked();


     void on_pushButton_ajtinst_2_clicked();
     void on_pushButton_sup_ins_clicked();
     void on_pushButton_modi_ins_clicked();
     void on_pushButton_clicked();
     void on_pushButton_sup_4_clicked();
     void on_pushButton_4_clicked();
     void on_lineEdit_textChanged();
     void on_pushButton_tric_clicked();
     void on_pushButton_7_clicked();
     void on_lineEdit_2_textChanged();
      void on_pushButton_6_clicked();
      void on_pushButton_dec_clicked();
      void on_lineEdit_44_textChanged();
      void on_lineEdit_35_textChanged();
      void on_pushButton_27_clicked();

      void on_pushButton_17_clicked();

      void on_pushButton_eleves_2_clicked();

private:
    Ui::gestion_employe *ui;
    staff_technique tmpstaff_technique;
    instituteur tmpinstituteur;
};

#endif // GESTION_EMPLOYE_H
