#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::ouvrirConnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_projet2A");
db.setUserName("alaa");//inserer nom de l'utilisateur
db.setPassword("30061998");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
