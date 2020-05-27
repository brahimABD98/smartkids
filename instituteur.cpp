#include "instituteur.h"
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>
instituteur::instituteur()
{
    id=0;
    nom="";
    prenom="";
    diplome="";
    salaire=0;
    exprience=0;
    niveau="";

}
instituteur::instituteur(int id,QString nom,QString prenom,QString diplome,float salaire,int exprience,QString niveau)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->diplome=diplome;
    this->salaire=salaire;
    this->exprience=exprience;
    this->niveau=niveau;
}
int instituteur::get_id(){return id;}
QString instituteur::get_nom(){return nom;}
QString instituteur::get_prenom(){return prenom;}
QString instituteur::get_diplome(){return diplome;}
float instituteur::get_salaire(){return salaire;}
int instituteur::get_exprience(){return exprience;}
QString instituteur::get_niveau(){return niveau;}


bool instituteur::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sri= QString::number(salaire);
    QString exp= QString::number(exprience);
    query.prepare("insert into instituteur (id,nom,prenom,diplome,salaire,exprience,niveau) VALUES (:id,:nom,:prenom,:diplome,:salaire,:exprience,:niveau)");
    query.bindValue(":id", res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":diplome",diplome);
    query.bindValue(":salaire", sri);
    query.bindValue(":exprience", exp);
    query.bindValue(":niveau",niveau);
    return query.exec();
}
QSqlQueryModel * instituteur::afficher()
{ QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from instituteur");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("diplome"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("exprience"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("niveau"));
    return model;
    }
bool instituteur::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from instituteur where ID = :idd ");
query.bindValue(":idd", res);
return    query.exec();
}

bool instituteur::modifier(int id, QString nom, QString prenom,QString diplome, float salaire,int exprience,QString niveau)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sri= QString::number(salaire);
    QString ex= QString::number(exprience);
    query.prepare("update instituteur set nom=:nom,prenom=:prenom,diplome=:diplome,salaire=:salaire,exprience=:exprience,niveau=:niveau where id=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
     query.bindValue(":diplome",diplome);
    query.bindValue(":salaire",sri);
    query.bindValue(":exprience",ex);
    query.bindValue(":niveau",niveau);
    return query.exec();
}
QSqlQueryModel * instituteur::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from instituteur where ((ID || NOM || PRENOM || DIPLOME || SALAIRE || EXPRIENCE ||NIVEAU) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("diplome"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("exprience"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("niveau"));
    return model;
}

QSqlQueryModel* instituteur::trie(int index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select *FROM instituteur ORDER BY salaire ASC");
    }
    else
    {
        model->setQuery("select *FROM instituteur ORDER BY salaire DESC ");
    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("diplome"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("exprience"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("niveau"));
    return model;
}


QSqlQuery instituteur::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from instituteur where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}
QSqlQueryModel * instituteur::afficher_instituteur()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from instituteur ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("diplome"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("exprience"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("niveau"));
    return model;
}
