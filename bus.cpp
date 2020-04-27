#include "bus.h"
#include <QDebug>
bus::bus()
{
id=0;
model="";
chauffeur="";
zone="";
nPlace=0;
}

bus::bus(int id,QString m,QString c,QString z,int n)
{
  this->id=id;
  this->model=m;
  this->chauffeur=c;
  this->zone=z;
  this->nPlace=n;
}

QString bus::get_model(){return  model;}
QString bus::get_chauffeur(){return chauffeur;}
int bus::get_nPlace(){return  nPlace;}
QString bus::get_zone(){return zone;}

bool bus::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO bus (ID,MODEL,CHAUFFEUR,ZONE,NPLACE) "
                    "VALUES (:id,:model,:chauffeur,:zone,:nPlace)");
query.bindValue(":id", res);
query.bindValue(":model", model);
query.bindValue(":chauffeur", chauffeur);
query.bindValue(":zone", zone);
query.bindValue(":nPlace", nPlace);
return    query.exec();
}


QSqlQueryModel * bus::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from bus");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Model "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Chauffeur"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Zone"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("nPlace"));

    return model;
}



bool bus::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from bus where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}


bool bus:: modifier(int id,QString m,QString c,QString z,int n)
{

    QSqlQuery qry;
        qry.prepare("UPDATE bus set MODEL=(?),CHAUFFEUR=(?),ZONE=(?),NPLACE=(?) where ID=(?) ");
        qry.addBindValue(m);
        qry.addBindValue(c);
        qry.addBindValue(z);
        qry.addBindValue(n);

        qry.addBindValue(id);

   return  qry.exec();
}




QSqlQueryModel * bus::rechercher (const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from bus where ((ID || MODEL ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Model "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Chauffeur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Zone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nPlace"));

    return model;
}

QSqlQuery bus::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from bus where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}


