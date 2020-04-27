#include "deponse.h"
#include <QDebug>
#include "connexion.h"

deponse::deponse()
{
id=0;
montant=0;
date="";
type="";
}
deponse::deponse(int id ,QString type,QString date,double montant)
{
    this->id=id;
    this->type=type;
    this->date=date;
    this->montant=montant;
}
QString deponse::get_type(){return  type;}
QString deponse::get_date(){return date;}
int deponse::get_id(){return  id;}
double deponse::get_montant(){return montant;}



bool deponse::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO DEPONSE (IDD, TYP, DAT , MONTANT) "
                    "VALUES (:id, :type, :date , :montant)");
query.bindValue(":id", res);
query.bindValue(":type", type);
query.bindValue(":date", date);
query.bindValue(":montant", montant);

return    query.exec();
}


QSqlQueryModel * deponse::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from DEPONSE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    return model;
}



void deponse::modifier(int ID)
{
    QSqlQuery q;
    q.prepare("UPDATE DEPONSE  SET TYP=:type,MONTANT=:montant,DAT=:date where IDD=:ID");

    q.bindValue(":ID",ID);
    q.bindValue(":type", this->type);
    q.bindValue(":montant", this->montant);
    q.bindValue(":date", this->date);
if(q.exec())
qDebug()<<"Produit modifie";
}



bool deponse::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from DEPONSE where IDD = :id ");
query.bindValue(":id", res);
return    query.exec();
}






QSqlQueryModel * deponse::recherche(QString id)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from DEPONSE where IDD like :id");
    query.bindValue(":id", QString("%%1%").arg(id));
    query.exec();
model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));
    return model;
}


QSqlQueryModel * deponse::afficherTrier()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from DEPONSE order by typ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    return model;
}

QSqlQuery deponse::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from deponse where IDD = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}
