#ifndef EXCURSION_H
#define EXCURSION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Excursion
{public:
    Excursion();
    Excursion(int,QString,QString,QString,int);
    QString get_destination();
    QString get_responsable();
    QString get_date();
    int get_id();
    int get_prix();
    bool ajouter_excursion();
    QSqlQueryModel * afficher_excursion();
    bool supprimer_excursion(int);
    bool modifier_excursion(int ,QString ,QString,QString ,int);
    QSqlQuery rechercher_id_excursion(int id);
    QSqlQueryModel * rechercher_excursion (const QString &aux);
private:
    QString destination,responsable,date;
    int id,prix;
};

#endif // EXCURSION_H
