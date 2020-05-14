#ifndef CLUB_H
#define CLUB_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Club
{public:
    Club();
    Club(int,QString,int,QString,int);
    QString get_nom();
    int get_responsable();
    QString get_jour();
    int get_id();
    int get_salle();
    bool ajouter_club();
    QSqlQueryModel * afficher_club();
    bool supprimer_club(int);
    bool modifier_club(int ,QString ,int,QString ,int);
    QSqlQuery rechercher_id_club(int id);
    QSqlQueryModel * rechercher_club (const QString &aux);
    QSqlQueryModel * afficher_salle ();
    QSqlQueryModel * afficher_responsable ();
private:
    QString nom,jour;
    int id,responsable,salle;
};

#endif // CLUB_H
