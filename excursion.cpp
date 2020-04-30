#include "excursion.h"
#include <QDebug>

Excursion::Excursion()
{
    id=0;
    destination="";
    responsable="";
    date="";
    prix=0;
}


Excursion::Excursion(int id,QString destination,QString responsable,QString date,int prix)
{
  this->id=id;
  this->destination=destination;
  this->responsable=responsable;
  this->date=date;
  this->prix=prix;
}


QString Excursion::get_destination(){return  destination;}
QString Excursion::get_responsable(){return responsable;}
QString Excursion::get_date(){return  date;}
int Excursion::get_id(){return  id;}
int Excursion::get_prix(){return  prix;}

bool Excursion::ajouter_excursion()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO excursion (ID, DESTINATION, RESPONSABLE, DATES, PRIX) "
                    "VALUES (:id, :destination, :responsable, :date, :prix)");
query.bindValue(":id", res);
query.bindValue(":destination", destination);
query.bindValue(":responsable", responsable);
query.bindValue(":date", date);
query.bindValue(":prix", prix);

return    query.exec();
}


QSqlQueryModel * Excursion::afficher_excursion()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from excursion");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Destination "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Responsable"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}


bool Excursion::supprimer_excursion(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from excursion where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}


bool Excursion::modifier_excursion(int id,QString destination,QString responsable,QString date,int prix)
{

    QSqlQuery qry;
        qry.prepare("UPDATE excursion set DESTINATION=(?),RESPONSABLE=(?),DATES=(?),PRIX=(?) where ID=(?) ");


        qry.addBindValue(destination);
        qry.addBindValue(responsable);
        qry.addBindValue(date);
        qry.addBindValue(prix);

        qry.addBindValue(id);


   return  qry.exec();
}

QSqlQuery Excursion::rechercher_id_excursion(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from excursion where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}



QSqlQueryModel * Excursion::rechercher_excursion (const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from excursion where ( LOWER (ID || DESTINATION || RESPONSABLE || PRIX  ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Destination "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Responsable"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}


QSqlQueryModel* Excursion::trie(int index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select *FROM excursion ORDER BY PRIX ASC");
    }
    else
    {
        model->setQuery("select *FROM excursion ORDER BY PRIX DESC ");
    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Destination "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Responsable"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}
