#ifndef DEPONSE_H
#define DEPONSE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class deponse
{
public:
    deponse();
    deponse(int,QString,QString,double);
    QString get_type();
    QString get_date();
    int get_id();
    double get_montant();
    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString);
    bool ajouter();
    bool supprimer(int);
    void modifier(int);
    QSqlQueryModel * afficherTrier();
    QSqlQuery rechercher_id(int id);

private:
    QString type,date;
    int id;
    double montant;
};

#endif // DEPONSE_H
