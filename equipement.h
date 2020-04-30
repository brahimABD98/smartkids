#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlQuery>

class equipement
{
    public:
        equipement();
         equipement(int,QString,int,QString,QString,double,double);

         QSqlQueryModel *  trier(const QString &critere, const QString &mode );
         bool ajouter();
         bool modifier_equipement(int,QString,int,QString,QString,double,double );
         bool supprimer(int idd);
         QSqlQueryModel * recherche (const QString &aux);
         QSqlQueryModel * afficher();
        QSqlQuery rechercher_id(int id);
        QSqlQuery rechercher_salle(int salle);
        QSqlQueryModel * affichersalle ();
        //  virtual ~equipement();

        int Getid_equipement() { return id_equipement; }
        void Setid_equipement(int val) { id_equipement = val; }
        QString Getnom_produit() { return nom_produit; }
        void Setnom_produit(QString val) { nom_produit = val; }
        int Getquantite() { return quantite; }
        void Setquantite(int val) { quantite = val; }
        QString Gettype() { return type; }
        void Settype(QString val) { type = val; }
        QString Getsalle_affecter() { return salle_affecter; }
        void Setsalle_affecter(QString val) { salle_affecter = val; }
        double Getprix_unitaire() { return prix_unitaire; }
        void Setprix_unitaire(double val) { prix_unitaire = val; }
        double Getprix_totale() { return prix_totale; }
        void Setprix_totale(double val) { prix_totale = val; }

    protected:

    private:
        int id_equipement;
        QString nom_produit;
        int quantite;
        QString type;
        QString salle_affecter;
        double prix_unitaire;
        double prix_totale;
};

#endif // EQUIPEMENT_H
