#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
//cv
class Bibliotheque
{public:
    Bibliotheque();
    Bibliotheque(int,QString,QString,QString,int);
    QString get_nom();
    QString get_auteur();
    QString get_langue();
    int get_id();
    int get_eleve();
    bool ajouter_livre();
    QSqlQueryModel * afficher_livre();
    bool supprimer_livre(int);
    bool modifier_livre(int ,QString ,QString,QString ,int);
    QSqlQuery rechercher_id_livre(int id);
    QSqlQueryModel * rechercher_livre (const QString &aux);
    QSqlQueryModel * afficher_eleve ();
    QSqlQuery rechercher_eleve(int id);
private:
    QString nom,auteur,langue;
    int id,eleve;
};

#endif // BIBLIOTHEQUE_H
