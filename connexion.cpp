#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::ouvrirConnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_projet2A");
db.setUserName("user");//inserer nom de l'utilisateur
db.setPassword("user");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
