#include "staff_technique.h"
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>
staff_technique::staff_technique()
{
    id=0;
    nom="";
    prenom="";
    salaire=0;
    spcialite="";
}

staff_technique::staff_technique(int id ,QString nom, QString prenom,float salaire, QString spcialite )
{

    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->salaire=salaire;
    this->spcialite=spcialite;

}
int staff_technique::get_id(){return id;}
QString staff_technique::get_nom(){return nom;}
QString staff_technique::get_prenom(){return prenom;}
float staff_technique::get_salaire(){return salaire;}
QString staff_technique::get_spcialite(){return spcialite;}

bool staff_technique::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sr= QString::number(salaire);
    query.prepare("insert into staff_technique (id,nom,prenom,salaire,spcialite) VALUES (:id,:nom,:prenom,:salaire,:spcialite)");
    query.bindValue(":id", res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
   query.bindValue(":salaire", sr);
    query.bindValue(":spcialite",spcialite);
    return query.exec();
}

QSqlQueryModel * staff_technique::afficher()
{ QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from STAFF_TECHNIQUE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("spcialite"));
    return model;

/*QSqlTableModel *mmodel = new QSqlTableModel();
           mmodel->setTable("STAFF_TECHNIQUE");
           mmodel->select();
           return mmodel;*/
}
bool staff_technique::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from staff_technique where ID = :idd ");
query.bindValue(":idd", res);
return    query.exec();
}

bool staff_technique::modifier(int id, QString nom, QString prenom, float salaire,QString spcialite)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sl= QString::number(salaire);
    query.prepare("update staff_technique set nom=:nom,prenom=:prenom,salaire=:salaire,spcialite=:spcialite where id=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire", sl);
    query.bindValue(":spcialite",spcialite);
    return query.exec();
}
/*
QSqlQueryModel * staff_technique::chercher(int id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * from staff_technique where id like :id order by nom ");
    query.bindValue(":id",id);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("salire"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("spcialite"));


    return model;
}*/
QSqlQueryModel* staff_technique::trie(int index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select *FROM staff_technique ORDER BY salaire ASC");
    }
    else
    {
        model->setQuery("select *FROM staff_technique ORDER BY salaire DESC ");
    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("spcialite"));

    return model;
}
QSqlQueryModel * staff_technique::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from staff_technique where ((ID || NOM || PRENOM || SALAIRE || SPCIALITE) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("spcialite"));

    return model;
}

QSqlQuery staff_technique::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from staff_technique where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}
