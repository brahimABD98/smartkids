#include "bibliotheque.h"
#include "eleves.h"

Bibliotheque::Bibliotheque()
{
    id=0;
    nom="";
    auteur="";
    langue="";
    eleve=0;
}


Bibliotheque::Bibliotheque(int id,QString nom,QString auteur,QString langue,int eleve)
{
  this->id=id;
  this->nom=nom;
  this->auteur=auteur;
  this->langue=langue;
  this->eleve=eleve;
}


QString Bibliotheque::get_nom(){return  nom;}
QString Bibliotheque::get_auteur(){return auteur;}
QString Bibliotheque::get_langue(){return  langue;}
int Bibliotheque::get_id(){return  id;}
int Bibliotheque::get_eleve(){return  eleve;}

bool Bibliotheque::ajouter_livre()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO bibliotheque (ID, NOM, AUTEUR, LANGUE, ELEVE) "
                    "VALUES (:id, :nom, :auteur, :langue, :eleve)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":auteur", auteur);
query.bindValue(":langue", langue);
query.bindValue(":eleve", eleve);

return    query.exec();
}


QSqlQueryModel * Bibliotheque::afficher_livre()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from bibliotheque");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Auteur"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Langue"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Eleve"));
    return model;
}


bool Bibliotheque::supprimer_livre(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from bibliotheque where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Bibliotheque::modifier_livre(int id,QString nom,QString auteur,QString langue,int eleve)
{

    QSqlQuery qry;
        qry.prepare("UPDATE bibliotheque set NOM=(?),AUTEUR=(?),LANGUE=(?),ELEVE=(?) where ID=(?) ");


        qry.addBindValue(nom);
        qry.addBindValue(auteur);
        qry.addBindValue(langue);
        qry.addBindValue(eleve);

        qry.addBindValue(id);


   return  qry.exec();
}

QSqlQuery Bibliotheque::rechercher_id_livre(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from bibliotheque where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}


QSqlQueryModel * Bibliotheque::rechercher_livre (const QString &aux)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from bibliotheque where ( LOWER (ID || NOM || AUTEUR || LANGUE  ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Auteur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Langue"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Eleve"));

    return model;
}

QSqlQueryModel * Bibliotheque::afficher_eleve(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select ID from eleves");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("eleve"));
    return model;
}
QSqlQuery Bibliotheque::rechercher_eleve(int id)
{

    QSqlQuery query;
    query.prepare("SELECT * from bibliotheque where ELEVE = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}
