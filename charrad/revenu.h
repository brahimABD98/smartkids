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

    bool supprimer(int);    QSqlQueryModel * afficherTrier();

private:
    QString type,date;
    int id;
    double montant;
};

#endif // REVENU_H
