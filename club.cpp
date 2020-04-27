#include "club.h"
#include <QDebug>

Club::Club()
{
    id=0;
    nom="";
    responsable="";
    jour="";
    salle=0;
}


Club::Club(int id,QString nom,QString responsable,QString jour,int salle)
{
  this->id=id;
  this->nom=nom;
  this->responsable=responsable;
  this->jour=jour;
  this->salle=salle;
}


QString Club::get_nom(){return  nom;}
QString Club::get_responsable(){return responsable;}
QString Club::get_jour(){return  jour;}
int Club::get_id(){return  id;}
int Club::get_salle(){return  salle;}

bool Club::ajouter_club()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO club (ID, NOM, RESPONSABLE, JOUR, SALLE) "
                    "VALUES (:id, :nom, :responsable, :jour, :salle)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":responsable", responsable);
query.bindValue(":jour", jour);
query.bindValue(":salle", salle);

return    query.exec();
}


QSqlQueryModel * Club::afficher_club()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from club");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Responsable"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salle"));
    return model;
}


bool Club::supprimer_club(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from club where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Club::modifier_club(int id,QString nom,QString responsable,QString jour,int salle)
{

    QSqlQuery qry;
        qry.prepare("UPDATE club set NOM=(?),RESPONSABLE=(?),JOUR=(?),SALLE=(?) where ID=(?) ");


        qry.addBindValue(nom);
        qry.addBindValue(responsable);
        qry.addBindValue(jour);
        qry.addBindValue(salle);

        qry.addBindValue(id);


   return  qry.exec();
}

QSqlQuery Club::rechercher_id_club(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from club where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}


QSqlQueryModel * Club::rechercher_club (const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from club where ( LOWER (ID || NOM || RESPONSABLE || JOUR  ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Responsable"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salle"));

    return model;
}
