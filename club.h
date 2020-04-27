#ifndef CLUB_H
#define CLUB_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Club
{public:
    Club();
    Club(int,QString,QString,QString,int);
    QString get_nom();
    QString get_responsable();
    QString get_jour();
    int get_id();
    int get_salle();
    bool ajouter_club();
    QSqlQueryModel * afficher_club();
    bool supprimer_club(int);
    bool modifier_club(int ,QString ,QString,QString ,int);
    QSqlQuery rechercher_id_club(int id);
    QSqlQueryModel * rechercher_club (const QString &aux);
private:
    QString nom,responsable,jour;
    int id,salle;
};

#endif // CLUB_H
