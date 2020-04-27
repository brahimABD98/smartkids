#include "salles.h"

#include <QDebug>

salles::salles()
{
 numS=0;
 type="";
 nbrPlace=0;
}

salles::salles(int n,QString t,int nbrP)
{
  this->numS=n;
  this->type=t;
  this->nbrPlace=nbrP;

}

int salles::get_numS(){return  numS;}
int salles::get_nbrPlace(){return  nbrPlace;}
QString salles::get_type(){return type;}


bool salles::ajouter()
{
QSqlQuery query;
QString res= QString::number(numS);
query.prepare("INSERT INTO salles (NUMS,TYPE,NBRPLACE) "
                    "VALUES (:numS,:type,:nbrPlace)");
query.bindValue(":numS", res);
query.bindValue(":type", type);
query.bindValue(":nbrPlace", nbrPlace);
return    query.exec();
}


QSqlQueryModel * salles::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from salles");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num Salle"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr Place"));

    return model;
}

bool salles::supprimer(int n)
{
QSqlQuery query;
QString res= QString::number(n);
query.prepare("Delete from salles where NUMS = :numS ");
query.bindValue(":numS", res);
return    query.exec();
}


bool salles:: modifier(int n,QString t,int nbr)
{

    QSqlQuery qry;
        qry.prepare("UPDATE salles set TYPE=(?),NBRPLACE=(?) where NUMS=(?) ");
        qry.addBindValue(t);
        qry.addBindValue(nbr);
        qry.addBindValue(n);

   return  qry.exec();
}

QSqlQueryModel * salles::rechercher (const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from salles where ((NUMS) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num Salle"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbr Place"));


    return model;
}

QSqlQuery salles::rechercher_num(int num)
{
    QSqlQuery query;
    query.prepare("SELECT * from salles where NUMS = :num");
    query.bindValue(":num", num);
    query.exec();

    return query;
}



