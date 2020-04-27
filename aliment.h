#ifndef ALIMENT_H
#define ALIMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
class aliments
{
public:
    aliments();
     aliments(int,QString,QString,QDate,double,double,int);

     bool ajouter();
     bool modifier_aliments(int ,QString ,QString ,QDate ,int ,double ,double);
     QSqlQuery rechercher_id(int id);

     QSqlQueryModel * recherche (const QString &aux);
     QSqlQueryModel *  trier(const QString &critere, const QString &mode );

     bool supprimer(int idd);

     QSqlQueryModel * afficher();

     virtual ~aliments();

    QString Getnom_produit() { return nom_produit; }
    void Setnom_produit(QString val) { nom_produit = val; }
    QString Gettype() { return type; }
    void Settype(QString val) { type = val; }
    double Getprix_unitaire() {
    return prix_unitaire; }
    void Setprix_unitaire(double val) { prix_unitaire = val; }
    double Getprix_totale() { return prix_totale; }
    void Setprix_totale(double val) { prix_totale = val; }
    int Getid_aliment() { return id_aliment; }
    void Setid_aliment(int val) { id_aliment = val; }
    QDate Getdlc() { return dlc; }
    void Setdlc(QDate val) { dlc = val; }
    int Getquantite() { return quantite; }
        void Setquantite(int val) { quantite = val; }

    protected:

    private:
        QString nom_produit;
        QString type;
        double prix_unitaire;
        double prix_totale;
        int id_aliment;
        QDate dlc;
        int quantite;
};

#endif // ALIMENT_H
