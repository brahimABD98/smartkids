#include "compte.h"

compte::compte()
{
    id=0;
    username="";
    password=0;
}

compte::compte(int id ,QString username, int password)
{

    this->id=id;
    this->username=username;
    this->password=password;


}
int compte::get_id(){return id;}
QString compte::get_username(){return username;}
int compte::get_password(){return password;}


bool  compte::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sr= QString::number(password);
    query.prepare("insert into compte (id,username,password) VALUES (:id,:username,:password)");
    query.bindValue(":id", res);
    query.bindValue(":username",username);

   query.bindValue(":password", sr);

    return query.exec();
}

QSqlQueryModel * compte::afficher()
{ QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from compte");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("username "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("password"));

    return model;

/*QSqlTableModel *mmodel = new QSqlTableModel();
           mmodel->setTable("STAFF_TECHNIQUE");
           mmodel->select();
           return mmodel;*/
}
bool compte::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from compte where ID = :idd ");
query.bindValue(":idd", res);
return    query.exec();
}

bool compte::modifier(int id, QString username, int password)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sl= QString::number(password);
    query.prepare("update compte set username=:username,password=:password where id=:id");
    query.bindValue(":id", res);
    query.bindValue(":username",username);

    query.bindValue(":password", sl);

    return query.exec();
}

QSqlQueryModel * compte::afficher_compte()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from compte ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("username"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("password"));

    return model;
}
QSqlQueryModel * compte::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from compte where ((ID || USERNAME || PASSWORD ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("username "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("password"));

    return model;
}

QSqlQuery compte::rechercher_id(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * from compte where ID = :id");
    query.bindValue(":id", id);
    query.exec();

    return query;
}

QSqlQueryModel* compte::trie(int index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select *FROM compte ORDER BY id ASC");
    }
    else
    {
        model->setQuery("select *FROM compte ORDER BY id DESC ");
    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("username"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("password"));

    return model;
}
