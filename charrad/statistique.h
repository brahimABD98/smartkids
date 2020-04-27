#ifndef STATISTIQUE_H
#define STATISTIQUE_H
#include <QSqlQueryModel>
#include <QSqlQuery>

class statistique
{
public:
    statistique();
    statistique(int,int,int);
        int get_moi();
        int get_montantd();
        int get_montantr();
        QSqlQueryModel * afficher();
    private:
        int montantd ;
        int montantr;
        int moi;
};

#endif // STATISTIQUE_H
