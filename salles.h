#ifndef SALLES_H
#define SALLES_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class salles
{

public:

    salles();
    salles(int,QString,int);
    QString get_type();
    int get_nbrPlace();
    int get_numS();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int ,QString,int );
    QSqlQueryModel * rechercher (const QString &aux);
    QSqlQuery rechercher_num(int num);

private:
    QString type;
    int numS,nbrPlace;


};
#endif // SALLES_H
