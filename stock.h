#ifndef STOCK_H
#define STOCK_H
#include"equipement.h"
#include "aliment.h"
#include <QDialog>

namespace Ui {
class stock;
}

class stock : public QDialog
{
    Q_OBJECT

public:
    explicit stock(QWidget *parent = nullptr);
    ~stock();

private slots:
    void on_pushButton_ajouter_aliment_clicked();

    void on_pushButton_modifier_aliment_clicked();

    void on_pushButton_supprimer_aliment_clicked();

    void on_pushButton_ok_a_a_clicked();

    void on_pushButton_ok_m_a_clicked();

    void on_pushButton_ok_s_a_clicked();

    void on_pushButton_annuler_ajouter_aliment_clicked();

    void on_pushButton_annuler_modif_aliment_clicked();

    void on_pushButton_supp_aliment_clicked();

    void on_pushButton_exporter_aliment_clicked();

    void on_lineEdit_id_modif_aliment_textChanged();

    void on_lineEdit_id_supp_aliment_textChanged();


    void on_pushButton_tri_aliment_clicked();

    void on_pushButton_ok_tri_aliment_clicked();

    void on_lineEdit_rechercher_aliment_textChanged();



    void on_pushButton_print_aliment_clicked();

    void on_pushButton_pdf_aliment_clicked();

    void on_pushButton_aliment_clicked();

    void on_pushButton_equipement_clicked();

    void on_pushButton_ajouter_equipement_clicked();

    void on_pushButton_modifier_equip_clicked();

    void on_pushButton_supp_equip_clicked();

    void on_pushButton_exporter_equip_clicked();

    void on_pushButton_tri_equipement_clicked();

    void on_pushButton_a_e_clicked();

    void on_pushButton_ok_m_e_clicked();

    void on_lineEdit_id_modif_equip_textChanged();

    void on_lineEdit_id_supp_equip_textChanged();

    void on_pushButton_s_e_clicked();



    void on_lineEdit_recherche_equip_textChanged();

    void on_pushButton_ok_tri_equipement_clicked();

    void on_pushButton_pdf_equipement_clicked();

    void on_pushButton_print_equipement_clicked();

    void on_pushButton_eleves_2_clicked();

    void on_pushButton_activite_clicked();

    void on_pushButton_employer_clicked();



    void on_pushButton_comp_clicked();

private:
    Ui::stock *ui;
    aliments tmpaliment;
    equipement tmpequipement;

};

#endif // STOCK_H
