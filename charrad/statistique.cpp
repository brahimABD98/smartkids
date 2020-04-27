#include "statistique.h"
#include <QDebug>

#include "connexion.h"

statistique::statistique()
{
       montantd=0;
       montantr=0;
       moi=0;
}
statistique::statistique(int moi, int montantd,int montantr)
{
    this->moi=moi;
    this->montantd=montantd;
    this->montantr=montantr;
}
int statistique::get_moi(){return moi;}
int statistique::get_montantd(){return montantd;}
int statistique::get_montantr(){return montantr;}

QSqlQueryModel * statistique::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select sum(d.montant),sum(r.montant),extract(month from d.dat) from deponse d, revenu r group by extract(month from r.dat)");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("d.montant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("r.montant "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
        return model;
}
