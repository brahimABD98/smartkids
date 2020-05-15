#ifndef DEPONSE_H
#define DEPONSE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
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
    void rechercher_id(QString id);
    void setType(QString type);
    void setDate(QString date);
    void setMontant(double montant);
    void setId(int id);

QDate datearbi;


private:
    QString type,date;
    int id;
    double montant;
   // QDate datearbi;
};

#endif // DEPONSE_H
