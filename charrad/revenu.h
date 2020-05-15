#ifndef REVENU_H
#define REVENU_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class revenu
{
public:
    revenu();
    revenu(int,QString,QString,double);
    QString get_type();
    QString get_date();
    int get_id();
    double get_montant();
    QSqlQueryModel * afficher();
    QSqlQueryModel * recherche(QString);
    bool ajouter();    void modifier(int);
    void rechercher_id(QString id);
    bool supprimer(int);    QSqlQueryModel * afficherTrier();
    void setType(QString type);
    void setDate(QString date);
    void setMontant(double montant);
    void setId(int id);

private:
    QString type,date;
    int id;
    double montant;
};

#endif // REVENU_H
