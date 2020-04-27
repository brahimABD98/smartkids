#include "revenu.h"
#include <QDebug>
#include "connexion.h"

revenu::revenu()
{
id=0;
montant=0;
date="";
type="";
}
revenu::revenu(int id ,QString type,QString date,double montant)
{
    this->id=id;
    this->type=type;
    this->date=date;
    this->montant=montant;
}
QString revenu::get_type(){return  type;}
QString revenu::get_date(){return date;}
int revenu::get_id(){return  id;}
double revenu::get_montant(){return montant;}



bool revenu::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO REVENU (IDD, TYP, DAT , MONTANT) "
                    "VALUES (:id, :type, :date , :montant)");
query.bindValue(":id", res);
query.bindValue(":type", type);
query.bindValue(":date", date);
query.bindValue(":montant", montant);

return    query.exec();
}


QSqlQueryModel * revenu::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from REVENU");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    return model;
}

void revenu::modifier(int ID)
{
    QSqlQuery q;
    q.prepare("UPDATE revenu  SET TYP=:type,MONTANT=:montant,DAT=:date where IDD=:ID");

    q.bindValue(":ID",ID);
    q.bindValue(":type", this->type);
    q.bindValue(":montant", this->montant);
    q.bindValue(":date", this->date);
if(q.exec())
qDebug()<<"Produit modifie";
}

bool revenu::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from REVENU where IDD = :id ");
query.bindValue(":id", res);
return    query.exec();
}


QSqlQueryModel * revenu::recherche(QString id)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from REVENU where IDD like :id");
    query.bindValue(":id", QString("%%1%").arg(id));
    query.exec();
model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
    return model;
}
QSqlQueryModel * revenu::afficherTrier()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from REVENU order by typ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    return model;
}
