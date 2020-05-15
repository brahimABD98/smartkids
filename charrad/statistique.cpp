#include "statistique.h"
#include <QDebug>

#include "connexion.h"

statistique::statistique()
{
       id=0;
       deponse=0;
       revenu=0;
       date = "";
       diff = 0;
}
statistique::statistique(int _1, int _2,int _3, QString _4, int _5)
{
    id=_1;
    deponse=_2;
    revenu=_3;
    date = _4;
    diff = _5;
}

QSqlQueryModel *  statistique::____()
{
    //**********************************************************
    QSqlQuery query;
    query.prepare("Delete from statt ");
    query.exec();
    //***********************************************************

    //**********************************************************
    int _ = 0;
    statistique tabs[100];
    for(int i=0; i<100 ; i++) {
        tabs[i].id = -1;
    }
    QSqlQuery query1;
    QSqlQuery query2;
    QSqlQuery query3;
    query1.exec("Select DISTINCT dat from deponse");
    while(query1.next()) {
        int deponse = 0;
        int revenu = 0;
        query2.exec("Select dat, montant from deponse");
        while(query2.next()) {
            if (query1.value(0).toString() == query2.value(0).toString()) {
                deponse += query2.value(1).toInt();
            }
        }
        query3.exec("Select dat, montant from revenu");
        while (query3.next()) {
            if (query1.value(0).toString() == query3.value(0).toString()) {
                revenu += query3.value(1).toInt();
            }
        }
        tabs[_].id = _ + 1;
        tabs[_].deponse = deponse;
        tabs[_].revenu = revenu;
        tabs[_].date = query1.value(0).toString();
        tabs[_].diff = deponse - revenu;
        _++;
    }

    query1.exec("Select DISTINCT dat from revenu");
    while(query1.next()) {
        int revenu = 0;
        for(int i=0; i<100 ; i++) {
            if(tabs[i].date == query1.value(0).toString()){
                break;
            }
            if(tabs[i].id == -1) {
                query3.exec("Select dat, montant from revenu");
                while (query3.next()) {
                    if (query1.value(0).toString() == query3.value(0).toString()) {
                        revenu += query3.value(1).toInt();
                    }
                }

                tabs[_].id = _ + 1;
                tabs[_].deponse = 0;
                tabs[_].revenu = revenu;
                tabs[_].date = query1.value(0).toString();
                tabs[_].diff = 0 - revenu;
                _++;

                break;
            }
        }
    }
    //**********************************************************

    //**********************************************************
    for(int i=0; i<100 ; i++) {
        if(tabs[i].id == -1) {
            break;
        }
        QSqlQuery query__;
        query.prepare("INSERT INTO statt (id, deponse, revenu , dat, diff) "
                            "VALUES (:id, :deponse, :revenu , :dat, :diff)");
        query.bindValue(":id", QString::number(tabs[i].id));
        query.bindValue(":deponse", QString::number(tabs[i].deponse));
        query.bindValue(":revenu", QString::number(tabs[i].revenu));
        query.bindValue(":dat", tabs[i].date);
        query.bindValue(":diff", QString::number(tabs[i].diff));

         query.exec();
    }
    //**********************************************************

    //**********************************************************
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select dat, deponse, revenu, diff from statt order by dat");
    return model;
    //**********************************************************
}
