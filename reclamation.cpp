#include "reclamation.h"
#include <QDebug>
reclamation::reclamation()
{

}


 reclamation :: reclamation ( int id_reclamation ,QString nom,QDate dater,QString mail,QString message)
{
    this->id_reclamation=id_reclamation;
    this->nom=nom;
    this->dater=dater;
    this->mail=mail;
    this->message=message;

}

bool reclamation  :: modifier_reclamation(   int id_reclamation ,QString nom,QDate dater,QString mail,QString message)
{

    QSqlQuery qry;
        qry.prepare("UPDATE reclamation set NOM=(?),DATER=(?),MAIL=(?),MESSAGE=(?) where ID_RECLAMATION=(?) ");


        qry.addBindValue(nom);
        qry.addBindValue(dater);
        qry.addBindValue(mail);
        qry.addBindValue(message);
        qDebug()<<dater;

         qry.addBindValue(id_reclamation);
   return  qry.exec();
}
bool reclamation::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from reclamation where id_reclamation = :id_reclamation ");
query.bindValue(":id_reclamation", res);
return    query.exec();
}


bool reclamation :: ajouter()
{
QSqlQuery query;
QString res= QString::number(id_reclamation);


query.prepare("INSERT INTO reclamation (ID_RECLAMATION, NOM,DATER,MAIL,MESSAGE)"
 "VALUES (:id_reclamation, :nom, :dater,:mail,:message)");


query.bindValue(":id_reclamation", res);
query.bindValue(":nom", nom);
query.bindValue(":dater", dater);
query.bindValue(":mail", mail);
query.bindValue(":message", message);
return    query.exec();
}
QSqlQueryModel * reclamation ::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from reclamation");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date reclamation"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("message"));




    return model;
}
QSqlQuery reclamation::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from reclamation where ID_reclamation = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}

QSqlQueryModel * reclamation ::recherche (const QString &aux)

{

    QSqlQueryModel * model = new QSqlQueryModel();
 model->setQuery("select * from reclamation where ((ID_reclamation || NOM) LIKE '%"+aux+"%')");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RECLAMATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATER"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MESSAGE"));


    return model;
}

QSqlQueryModel *  reclamation::trier(const QString &critere, const QString &mode )
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from reclamation order by "+critere+" "+mode+"");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID reclamation"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("date reclamation"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("message"));
    return model;
}
QSqlQuery reclamation::rechercher_salle(int salle)
{

    QSqlQuery query;
    query.prepare("SELECT * from reclamation where SALLE_AFFECTER = :salle");
    query.bindValue(":salle", salle);
    query.exec();

    return query;
}
