#ifndef COMPTE_H
#define COMPTE_H
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>
#include <QSqlQuery>
#include "QFileDialog"
#include "QTextBrowser"
#include <QSqlQueryModel>

class compte
{
public:
    compte();
    compte(int , QString, int);
    int get_id();
     QString get_username();
     int get_password();

    bool ajouter();


     QSqlQueryModel * afficher();
 bool supprimer(int);
 bool modifier(int,QString,int);
  QSqlQueryModel * rechercher (const QString &aux);
 QSqlQueryModel* trie(int index);
 QSqlQueryModel * afficher_compte ();
 private:

     QString username;
     int id,password;


};

#endif // COMPTE_H
