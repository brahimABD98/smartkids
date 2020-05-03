#ifndef GESTION_H
#define GESTION_H
#include "eleves.h"
#include "salles.h"
#include "bus.h"
#include "equipement.h"
#include "bibliotheque.h"
#include <QDialog>

namespace Ui {
class Gestion;
}

class Gestion : public QDialog
{
    Q_OBJECT

public:
    explicit Gestion(QWidget *parent = nullptr);
    ~Gestion();

private slots:
    void on_pushButton_AjouterE_clicked();

    void on_pushButton_ModifierE_clicked();

    void on_pushButton_SupprimerE_clicked();

    void on_pushButton_AjouterS_clicked();

    void on_pushButton_ModifierS_clicked();

    void on_pushButton_SupprimerS_clicked();

    void on_pushButton_gest_eleve_clicked();

    void on_pushButton_gest_salle_clicked();

    void on_pushButton_AjoutEleve_clicked();

    void on_lineEdit_Mo_id_E_textChanged();

    void on_pushButton_ModifierEleve_clicked();

    void on_pushButton_SupprimerEleve_clicked();

    void on_lineEdit_RechercheE_textChanged();

    void on_pushButton_PDFE_clicked();

    void on_pushButton_resetE_clicked();

    void on_pushButton_resetME_clicked();

    void on_pushButton_resetSE_clicked();

    void on_pushButton_AjouterSalle_clicked();

    void on_lineEdit_Mo_num_S_textChanged();

    void on_pushButton_ModifierSalle_clicked();



    void on_pushButton_SupprimerSalle_clicked();



    void on_lineEdit_rechercherS_textChanged();

    void on_pushButton_PDFS_clicked();

    void on_pushButton_RESETAMS_clicked();

    void on_pushButton_ResetMS_clicked();

    void on_pushButton_RESETSS_clicked();




    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();


    void on_pushButton_gest_trans_clicked();

        void on_pushButton_AjouterT_clicked();

        void on_pushButton_ModifierT_clicked();

        void on_pushButton_SupprimerT_clicked();

        void on_pushButton_AjoutTrans_clicked();

        void on_lineEdit_Mo_id_T_textChanged();

        void on_pushButton_ModifTrans_clicked();

        void on_pushButton_SupprimerTrans_clicked();

        void on_lineEdit_RechercheT_textChanged();

        void on_pushButton_PDFT_clicked();

        void on_pushButton_resetT_clicked();

        void on_pushButton_resetTm_clicked();

        void on_pushButton_resetTs_clicked();

        void on_tableView_S_doubleClicked(const QModelIndex &index);




        void on_pushButton_stock_clicked();

        void on_tableView_E_doubleClicked(const QModelIndex &index);

private:
    Ui::Gestion *ui;
    eleves tmpeleve;
    salles tmpsalle;
    bus tmpbus;
    equipement tmpequipement;
    Bibliotheque tmpbibliotheque;
};

#endif // GESTION_H
