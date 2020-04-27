#ifndef BUS_H
#define BUS_H


#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class bus
{
public:
    bus();
    bus(int,QString,QString,QString,int);
        QString get_model();
        QString get_chauffeur();
        QString get_zone();
        int get_nPlace();
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int,QString,QString,QString,int);
        QSqlQueryModel * rechercher (const QString &aux);
        QSqlQuery rechercher_id(int id);





private:
    QString model,chauffeur,zone;
    int id,nPlace;

};


#endif // BUS_H
