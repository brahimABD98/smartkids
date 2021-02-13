#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>


class reclamation
{
    public:
        reclamation();
        reclamation(int ,QString,QDate,QString,QString);
//bnj
        bool ajouter();

        bool modifier_reclamation(int,QString,QDate,QString,QString);
        bool supprimer(int idd);
        QSqlQueryModel * recherche (const QString &aux);
        QSqlQueryModel * afficher();
       QSqlQuery rechercher_id(int id);
       QSqlQuery rechercher_salle(int salle);
       QSqlQueryModel *  trier(const QString &critere, const QString &mode );

        int Getid_reclamation() { return id_reclamation; }
        void Setid_reclamation(int val) { id_reclamation = val; }
        QString Getnom() { return nom; }
        void Setnom(QString val) { nom = val; }
        QDate Getdater() { return dater; }
        void Setdater(QDate val) { dater = val; }
        QString Getmail() { return mail; }
        void Setmail(QString val) { mail = val; }
        QString Getmessage() { return message; }
        void Setmessage(QString val) { message = val; }

    protected:

    private:
        int id_reclamation;
        QString nom;
        QDate dater;
        QString mail;
        QString message;
};

#endif // RECLAMATION_H
