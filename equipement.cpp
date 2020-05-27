#include "equipement.h"
#include <QDebug>

equipement :: equipement()
{
}
 equipement :: equipement ( int id_equipement ,QString nom_produit,int quantite,QString type,QString salle_affecter,double pu,double pt)
{
    this->id_equipement=id_equipement;
    this->nom_produit=nom_produit;
    this->type=type;
    this->salle_affecter=salle_affecter;
    this->prix_unitaire=pu;
    this->prix_totale=pt;
    this->quantite=quantite;
}

bool equipement  :: modifier_equipement( int id_equipement ,QString nom_produit,int quantite,QString type,QString salle_affecter,double pu,double pt )
{

    QSqlQuery qry;
        qry.prepare("UPDATE equipement set NOM_PRODUIT=(?),QUANTITE=(?),TYPE=(?),SALLE_AFFECTER=(?),PRIX_UNITAIRE=(?),PRIX_TOTALE=(?) where ID_EQUIPEMENT=(?) ");


        qry.addBindValue(nom_produit);
        qry.addBindValue(quantite);
        qry.addBindValue(type);
        qry.addBindValue(salle_affecter);
        qry.addBindValue(pu);
        qry.addBindValue(pt);
         qry.addBindValue(id_equipement);
   return  qry.exec();
}
bool equipement::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from equipement where id_equipement = :id_equipement ");
query.bindValue(":id_equipement", res);
return    query.exec();
}


bool equipement :: ajouter()
{
QSqlQuery query;
QString res= QString::number(id_equipement);


query.prepare("INSERT INTO equipement (ID_EQUIPEMENT, NOM_PRODUIT,QUANTITE,TYPE,SALLE_AFFECTER,PRIX_UNITAIRE,PRIX_TOTALE)"
 "VALUES (:id_equipement, :nom_produit, :quantite,:type,:salle_affecter,:prix_unitaire,:prix_totale)");

//,PRIX_TOTALE ,:prix_totale
query.bindValue(":id_equipement", res);
query.bindValue(":nom_produit", nom_produit);
query.bindValue(":type", type);
query.bindValue(":salle_affecter", salle_affecter);
query.bindValue(":prix_unitaire", prix_unitaire);
query.bindValue(":prix_totale", prix_totale);
query.bindValue(":quantite", quantite);
//qDebug()<<prix_unitaire;
return    query.exec();
}
QSqlQueryModel * equipement ::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from equipement");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Produit "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantité"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("salle affecter"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix unitaire"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("prix totale"));




    return model;
}
QSqlQuery equipement::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from equipement where ID_EQUIPEMENT = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}

QSqlQueryModel * equipement ::recherche (const QString &aux)

{

    QSqlQueryModel * model = new QSqlQueryModel();
 model->setQuery("select * from equipement where ((ID_EQUIPEMENT || NOM_PRODUIT) LIKE '%"+aux+"%')");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Produit "));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantité"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salle affecter"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix unitaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix totale"));


    return model;
}
QSqlQueryModel *  equipement ::trier(const QString &critere, const QString &mode )
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from equipement order by "+critere+" "+mode+"");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Produit "));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantité"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("salle affecter"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix unitaire"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("prix totale"));
    return model;
}

QSqlQuery equipement::rechercher_salle(int salle)
{

    QSqlQuery query;
    query.prepare("SELECT * from equipement where SALLE_AFFECTER = :salle");
    query.bindValue(":salle", salle);
    query.exec();

    return query;
}
QSqlQueryModel * equipement::affichersalle ()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select NUMS from SALLES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMS"));
    return model;
}
QSqlQuery equipement::rechercher_num(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from equipement where id = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}
