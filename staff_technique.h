#ifndef STAFF_TECHNIQUE_H
#define STAFF_TECHNIQUE_H
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>
#include <QSqlQuery>
#include "QFileDialog"
#include "QTextBrowser"
#include <QSqlQueryModel>
class staff_technique
{

public:
    staff_technique();
    staff_technique(int, QString, QString ,float,QString);
   int get_id();
    QString get_nom();
    QString get_prenom();
    float get_salaire();
    QString get_spcialite();
   bool ajouter();


    QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier(int,QString,QString,float,QString);
 QSqlQueryModel * rechercher (const QString &aux);
QSqlQueryModel* trie(int index);
QSqlQuery rechercher_id(int id);

private:

    QString nom,prenom,spcialite;
    int id;
    float salaire;

};


#endif // STAFF_TECHNIQUE_H
