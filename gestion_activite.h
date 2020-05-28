#ifndef GESTION_ACTIVITE_H
#define GESTION_ACTIVITE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "excursion.h"
#include "club.h"
#include "salles.h"
#include "bibliotheque.h"
#include "eleves.h"
#include "instituteur.h"

#include <QDialog>

namespace Ui {
class gestion_activite;
}

class gestion_activite : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_activite(QWidget *parent = nullptr);
    ~gestion_activite();

private slots:
    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_eleves_3_clicked();

    void on_pushButton_ajout_club_clicked();

    void on_pushButton_ajout_exc_clicked();

    void on_lineEdit_modif_id_c_textChanged();

    void on_pushButton_modif_club_clicked();

    void on_lineEdit_modif_id_exc_textChanged();

    void on_pushButton_modif_exc_clicked();

    void on_pushButton_supp_club_clicked();

    void on_pushButton_supp_exc_clicked();

    void on_lineEdit_recherche_club_textChanged();

    void on_lineEdit_recherche_excursion_textChanged();

    void on_pushButton_PDF_club_clicked();

    void on_pushButton_PDF_exc_clicked();

    void on_pushButton_eleves_2_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_table_club_doubleClicked(const QModelIndex &index);

    void on_pushButton_eleves_4_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_ajout_livre_clicked();

    void on_lineEdit_modif_id_livre_textChanged();

    void on_pushButton_modif_livre_clicked();

    void on_pushButton_supp_livre_clicked();

    void on_pushButton_PDF_livre_clicked();

    void on_lineEdit_recherche_livre_textChanged();

    void on_table_livre_doubleClicked(const QModelIndex &index);

    void on_pushButton_tri_asc_clicked();

    void on_pushButton_tri_desc_clicked();

    void on_table_excursion_doubleClicked(const QModelIndex &index);

private:
    Ui::gestion_activite *ui;
    Excursion tmpexcursion;
    Club tmpclub;
    salles tmpsalles;
    Bibliotheque tmplivre;
    eleves tmpeleves;
    instituteur tmpinstituteur;
};

#endif // GESTION_H
