#include "eleves.h"
#include <QDebug>

eleves::eleves()
{
id=0;
nomprenom="";
QDate dateNaissance(1995, 5, 17);
parent="";
numParent=0;
niveau=0;
}

eleves::eleves(int id,QString nomp,QDate dN,int n,QString p,int nP)
{
  this->id=id;
  this->nomprenom=nomp;
  this->dateNaissance=dN;
  this->niveau=n;
  this->parent=p;
  this->numParent=nP;
}

QString eleves::get_nomprenom(){return  nomprenom;}
QDate eleves::get_date(){return dateNaissance;}
int eleves::get_niv(){return  niveau;}
int eleves::get_num(){return  numParent;}
QString eleves::get_parent(){return parent;}


bool eleves::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO eleves (ID,NOMPRENOM,PARENT,DATENAISSANCE,NIV,NUM) "
                    "VALUES (:id,:nomprenom,:parent,:dateNaissance,:niveau,:numParent)");
query.bindValue(":id", res);
query.bindValue(":nomprenom", nomprenom);
query.bindValue(":dateNaissance", dateNaissance);
query.bindValue(":niveau", niveau);
query.bindValue(":numParent", numParent);
query.bindValue(":parent", parent);
return    query.exec();
}

QSqlQueryModel * eleves::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from eleves");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NomPrenom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Niveau"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Parent"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("NumParent"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("DateNaissance"));



    return model;
}

bool eleves::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from eleves where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool eleves:: modifier(int id,QString nom,QDate dNaissance,int niv,QString nomp,int num)
{

    QSqlQuery qry;
        qry.prepare("UPDATE eleves set NOMPRENOM=(?),PARENT=(?),DATENAISSANCE=(?),NIV=(?),NUM=(?) where ID=(?) ");
        qry.addBindValue(nom);
        qry.addBindValue(nomp);
        qry.addBindValue(dNaissance);
        qry.addBindValue(niv);
        qry.addBindValue(num);
        qry.addBindValue(id);

   return  qry.exec();
}

QSqlQueryModel * eleves::rechercher (const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from eleves where ((ID || NOMPRENOM ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NomPrenom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Niveau"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Parent"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NumParent"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DateNaissance"));

    return model;
}

QSqlQuery eleves::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from eleves where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}

