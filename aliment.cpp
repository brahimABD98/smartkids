#include "aliment.h"
#include <QDebug>
aliments::aliments()
{

}
aliments :: aliments( int id ,QString nom_produit,QString type,QDate dlc,double pu,double pt,int quantite)
{
    this->id_aliment=id;
    this->nom_produit=nom_produit;
    this->type=type;
    this->dlc=dlc;
    this->prix_unitaire=pu;
    this->prix_totale=pt;
    this->quantite=quantite;
}

bool aliments:: modifier_aliments(int id_aliment,QString nom_produit,QString type,QDate dlc,int quantite,double prix_unitaire,double prix_totale)
{

    QSqlQuery qry;
        qry.prepare("UPDATE aliment set NOM_PRODUIT=(?),TYPE=(?),DLC=(?),PRIX_UNITAIRE=(?),PRIX_TOTALE=(?) , QUANTITE=(?) where ID_ALIMENT=(?) ");

        qry.addBindValue(nom_produit);
        qry.addBindValue(type);
        qry.addBindValue(dlc);
        qry.addBindValue(prix_unitaire);
        qry.addBindValue(prix_totale);

        qry.addBindValue(quantite);
        qry.addBindValue(id_aliment);

   return  qry.exec();
}
bool aliments::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from aliment where id_aliment = :id_aliment ");
query.bindValue(":id_aliment", res);
return    query.exec();
}
bool aliments :: ajouter()
{
QSqlQuery query;
QString res= QString::number(id_aliment);


query.prepare("INSERT INTO ALIMENT (ID_ALIMENT, NOM_PRODUIT,TYPE,DLC,quantite,prix_unitaire,PRIX_TOTALE)"
 "VALUES (:id_aliment, :nom_produit, :type,:dlc,:quantite,:prix_unitaire,:prix_totale)");

//,PRIX_TOTALE ,:prix_totale
query.bindValue(":id_aliment", res);

query.bindValue(":nom_produit", nom_produit);

query.bindValue(":type", type);

query.bindValue(":dlc", dlc);

query.bindValue(":prix_unitaire", prix_unitaire);

query.bindValue(":prix_totale", prix_totale);

query.bindValue(":quantite", quantite);
//qDebug()<<prix_unitaire;
return    query.exec();
}
QSqlQueryModel * aliments ::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from aliment");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Produit "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DlC"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix unitaire"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix totale"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantité"));




    return model;
}
/*metier*/


QSqlQueryModel * aliments ::recherche (const QString &aux)

{

    QSqlQueryModel * model = new QSqlQueryModel();
 model->setQuery("select * from ALIMENT where ((ID_ALIMENT || NOM_PRODUIT) LIKE '%"+aux+"%')");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Produit "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DlC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix unitaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix totale"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantité"));

    return model;
}

QSqlQueryModel *  aliments::trier(const QString &critere, const QString &mode )
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from aliment order by "+critere+" "+mode+"");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Produit "));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("DlC"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix unitaire"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix totale"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantité"));
    return model;
}
QSqlQuery aliments::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from aliment where ID_ALIMENT = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}

/*fin metier*/


aliments::~aliments()
{
    //dtor
}
