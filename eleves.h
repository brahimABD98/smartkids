#ifndef ELEVES_H
#define ELEVES_H


#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



class eleves
{

public:

    eleves();
    eleves(int,QString,QDate,int,QString,int);
    QString get_nomprenom();
    QDate get_date();
    int get_niv();
    QString get_parent();
    int get_num();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int ,QString ,QDate ,int,QString,int );
    QSqlQueryModel * rechercher (const QString &aux);
    QSqlQuery rechercher_id(int id);
private:
    QString nomprenom,parent;
    int id,niveau;
    int numParent;
    QDate dateNaissance;

};

#endif // ELEVES_H
