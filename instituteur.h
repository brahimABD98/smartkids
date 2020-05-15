#ifndef INSTITUTEUR_H
#define INSTITUTEUR_H
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>
#include <QSqlQuery>
#include "QFileDialog"
#include "QTextBrowser"
#include <QSqlQueryModel>

class instituteur
{
public:
    instituteur();
    instituteur(int ,QString,QString,QString,float,int,QString);
    int get_id();
     QString get_nom();
     QString get_prenom();
     QString get_diplome();
     float get_salaire();
     int get_exprience();
     QString get_niveau();
    bool ajouter();
QSqlQueryModel * afficherinstituteur ();

     QSqlQueryModel * afficher();
 bool supprimer(int);
 bool modifier(int,QString,QString,QString,float,int,QString);
  QSqlQueryModel * rechercher (const QString &aux);

 QSqlQueryModel* trie(int index);
 QSqlQuery rechercher_id(int id);
 private:
 int id,exprience;
     QString nom,prenom,diplome,niveau;
     float salaire;
};

#endif // INSTITUTEUR_H
