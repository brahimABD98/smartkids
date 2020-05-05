#ifndef STATISTIQUE_H
#define STATISTIQUE_H
#include <QSqlQueryModel>
#include <QSqlQuery>

class statistique
{
public:
    int id;
    int deponse;
    int revenu;
    QString date;
    int diff;
    statistique();
    statistique(int, int, int, QString, int);

    QSqlQueryModel *  ____();

};

#endif // STATISTIQUE_H
