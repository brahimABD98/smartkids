#include "gestion_activite.h"
#include "gestion_employe.h"
#include "ui_gestion_activite.h"
#include "club.h"
#include "excursion.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include "gestion.h"
#include "stock.h"
#include "charrad/gestiono9.h"
#include "bibliotheque.h"
#include "QCheckBox"

gestion_activite::gestion_activite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_activite)
{
    ui->setupUi(this);
    ui->table_club->setModel(tmpclub.afficher_club());
    ui->table_excursion->setModel(tmpexcursion.afficher_excursion());
    ui->table_livre->setModel(tmplivre.afficher_livre());
    ui->dateEdit_excu_ajout->setDate(QDate::currentDate()); 
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->comboBox_eleve_livre->setModel(tmplivre.afficher_eleve());
    ui->comboBox_modif_eleve_livre->setModel(tmplivre.afficher_eleve());
    ui->comboBox_ajout_salle_club->setModel(tmpclub.afficher_salle());
    ui->comboBox_modif_salle_club->setModel(tmpclub.afficher_salle());
    ui->comboBox_ajout_res_exc->setModel(tmpexcursion.afficher_responsable());
    ui->comboBox_modif_res_exc->setModel(tmpexcursion.afficher_responsable());
    ui->comboBox_ajout_res_c->setModel(tmpclub.afficher_responsable());
    ui->comboBox_modif_res_c->setModel(tmpclub.afficher_responsable());

}

gestion_activite::~gestion_activite()
{
    delete ui;
}

void gestion_activite::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestion_activite::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestion_activite::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void gestion_activite::on_pushButton_22_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void gestion_activite::on_pushButton_23_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void gestion_activite::on_pushButton_24_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}

void gestion_activite::on_pushButton_28_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void gestion_activite::on_pushButton_eleves_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void gestion_activite::on_pushButton_ajout_club_clicked()
{
    int id = ui->lineEdit_ajout_id_c->text().toInt();
    QString nom= ui->lineEdit_ajout_nom_c->text();
    int responsable= ui->comboBox_ajout_res_c->currentText().toInt();
    QString jour= ui->comboBox_ajout_dateclub->currentText();
    int salle = ui->comboBox_ajout_salle_club->currentText().toInt();
  Club c(id,nom,responsable,jour,salle);
  bool test=c.ajouter_club();
  if(test)
{ui->table_club->setModel(tmpclub.afficher_club());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un club"),
                  QObject::tr("Club ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un club"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_activite::on_pushButton_ajout_exc_clicked()
{
    int id = ui->lineEdit_ajout_id_exc->text().toInt();
    QString destination= ui->lineEdit_ajout_dest_exc->text();
    int responsable= ui->comboBox_ajout_res_exc->currentText().toInt();
    QString date= ui->dateEdit_excu_ajout->date().toString();
    int prix = ui->lineEdit_ajout_prix_exc->text().toInt();
  Excursion e(id,destination,responsable,date,prix);
  bool test=e.ajouter_excursion();
  if(test)
{ui->table_excursion->setModel(tmpexcursion.afficher_excursion());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une excursion"),
                  QObject::tr("Excursion ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une excursion"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_activite::on_lineEdit_modif_id_c_textChanged()
{
    int id=ui->lineEdit_modif_id_c->text().toInt();

    QSqlQuery query=tmpclub.rechercher_id_club(id);
    QString nom_c,responsable_c,jour_c;
    QString salle_c;


         if (query.next())
        {

        nom_c= query.value(1).toString();
        ui->lineEdit_modif_nom_c->setText(nom_c);
        responsable_c= query.value(2).toString();
        ui->comboBox_modif_res_c->setCurrentText(responsable_c);
        jour_c= query.value(3).toString();
        ui->lineEdit_modif_jour_c->setText(jour_c);
        salle_c= query.value(4).toString();
        ui->comboBox_modif_salle_club->setCurrentText(salle_c);


        }
}

void gestion_activite::on_pushButton_modif_club_clicked()
{
    QString nom= ui->lineEdit_modif_nom_c->text();
    int responsable= ui->comboBox_modif_res_c->currentText().toInt();
    QString jour= ui->lineEdit_modif_jour_c->text();
    int salle = ui->comboBox_modif_salle_club->currentText().toInt();

    bool test =tmpclub.modifier_club(ui->lineEdit_modif_id_c->text().toInt(),ui->lineEdit_modif_nom_c->text()
                ,responsable,jour,salle);

      if(test)
      {
          ui->table_club->setModel(tmpclub.afficher_club());//refresh
          QMessageBox::information(nullptr, QObject::tr("Modifier un club"),
                            QObject::tr("Club modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier un club"),
                        QObject::tr("Erreur !.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_activite::on_lineEdit_modif_id_exc_textChanged()
{
    int id=ui->lineEdit_modif_id_exc->text().toInt();

    QSqlQuery query=tmpexcursion.rechercher_id_excursion(id);
    QString destination_e,responsable_e,date_e;
    QString prix_e;


         if (query.next())
        {

        destination_e= query.value(1).toString();
        ui->lineEdit_modif_dest_exc->setText(destination_e);
        responsable_e= query.value(2).toString();
        ui->comboBox_modif_res_exc->setCurrentText(responsable_e);
        date_e= query.value(3).toString();
        ui->lineEdit_modif_date_exc->setText(date_e);
        prix_e= query.value(4).toString();
        ui->lineEdit_modif_prix_exc->setText(prix_e);

        }
}

void gestion_activite::on_pushButton_modif_exc_clicked()
{
    QString destination= ui->lineEdit_modif_dest_exc->text();
    int responsable= ui->comboBox_modif_res_exc->currentText().toInt();
    QString date= ui->lineEdit_modif_date_exc->text();
    int prix = ui->lineEdit_modif_prix_exc->text().toInt();

    bool test =tmpexcursion.modifier_excursion(ui->lineEdit_modif_id_exc->text().toInt(),ui->lineEdit_modif_dest_exc->text()
                ,responsable,date,prix);

      if(test)
      {
          ui->table_excursion->setModel(tmpexcursion.afficher_excursion());//refresh
          QMessageBox::information(nullptr, QObject::tr("Modifier une excursion"),
                            QObject::tr("Excursion modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier une excursion"),
                        QObject::tr("Erreur !.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_activite::on_pushButton_supp_club_clicked()
{
    int id = ui->lineEdit_supp_id_club->text().toInt();
    QSqlQuery query=tmpclub.rechercher_id_club(id);
    QString nom_c,responsable_c,jour_c;
    QString salle_c;

    if (query.next())
   {
    nom_c= query.value(1).toString();
    responsable_c= query.value(2).toString();
    jour_c= query.value(3).toString();
    salle_c= query.value(4).toString();
   }

    int reponse = QMessageBox::question(this, "Interrogatoire", "Voulez-vous supprimer le club :\n nom : " +nom_c+ "\n responsable : " +responsable_c+ "\n jour : " +jour_c+ "\n salle : " +salle_c , QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        bool test=tmpclub.supprimer_club(id);
        if(test)
        {ui->table_club->setModel(tmpclub.afficher_club());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer un club"),
                        QObject::tr("Club supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un club"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_supp_id_club->clear() ;
    }
    else if (reponse == QMessageBox::No)
    {
        ui->lineEdit_supp_id_club->clear() ;
    }
}

void gestion_activite::on_pushButton_supp_exc_clicked()
{
    int id = ui->lineEdit_supp_exc->text().toInt();
    QSqlQuery query=tmpexcursion.rechercher_id_excursion(id);
    QString destination_e,responsable_e,date_e;
    QString prix_e;

    if (query.next())
   {
    destination_e= query.value(1).toString();
    responsable_e= query.value(2).toString();
    date_e= query.value(3).toString();
    prix_e= query.value(4).toString();
   }

    int reponse = QMessageBox::question(this, "Interrogatoire", "Voulez-vous supprimer l'excursion :\n destination : " +destination_e+ "\n responsable : " +responsable_e+ "\n date : " +date_e+ "\n prix : " +prix_e , QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        bool test=tmpexcursion.supprimer_excursion(id);
        if(test)
        {ui->table_excursion->setModel(tmpexcursion.afficher_excursion());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer une excursion"),
                        QObject::tr("Excursion supprimée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer une excursion"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_supp_exc->clear() ;
    }
    else if (reponse == QMessageBox::No)
    {
        ui->lineEdit_supp_exc->clear() ;
    }
}

void gestion_activite::on_lineEdit_recherche_club_textChanged()
{
    if(ui->lineEdit_recherche_club->text() == "")
            {
                ui->table_club->setModel(tmpclub.afficher_club());
            }
            else
            {
                 ui->table_club->setModel(tmpclub.rechercher_club(ui->lineEdit_recherche_club->text()));
            }
}

void gestion_activite::on_lineEdit_recherche_excursion_textChanged()
{
    if(ui->lineEdit_recherche_excursion->text() == "")
            {
                ui->table_excursion->setModel(tmpexcursion.afficher_excursion());
            }
            else
            {
                 ui->table_excursion->setModel(tmpexcursion.rechercher_excursion(ui->lineEdit_recherche_excursion->text()));
            }
}

void gestion_activite::on_pushButton_PDF_club_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->table_club->model()->rowCount();
            const int columnCount =ui->table_club->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src='C:/Users/ksemt/Desktop/final/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des clubs</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->table_club->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->table_club->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->table_club->isColumnHidden(column)) {
                               QString data = ui->table_club->model()->data(ui->table_club->model()->index(row, column)).toString().simplified();
                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                           }
                       }
                       out << "</tr>\n";
                   }
                   out <<  "</table>\n"
                       "</body>\n"
                       "</html>\n";

                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);

                   QPrinter printer;

                   QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                   if (dialog->exec() == QDialog::Accepted) {
                       document->print(&printer);
                }
}

void gestion_activite::on_pushButton_PDF_exc_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->table_excursion->model()->rowCount();
            const int columnCount =ui->table_excursion->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src='C:/Users/ksemt/Desktop/final/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des excursions</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->table_excursion->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->table_excursion->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->table_excursion->isColumnHidden(column)) {
                               QString data = ui->table_excursion->model()->data(ui->table_excursion->model()->index(row, column)).toString().simplified();
                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                           }
                       }
                       out << "</tr>\n";
                   }
                   out <<  "</table>\n"
                       "</body>\n"
                       "</html>\n";

                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);

                   QPrinter printer;

                   QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                   if (dialog->exec() == QDialog::Accepted) {
                       document->print(&printer);
                }
}

void gestion_activite::on_pushButton_eleves_2_clicked()
{
    hide();
 Gestion g;
 g.exec();
}

void gestion_activite::on_pushButton_12_clicked()
{
    hide();
    stock s;
    s.exec();
}

void gestion_activite::on_pushButton_17_clicked()
{
    hide();
    gestiono9 G;
    G.exec();
}

void gestion_activite::on_pushButton_16_clicked()
{
    hide();
    gestion_employe Ge;
    Ge.exec();
}


void gestion_activite::on_table_club_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 4)  ) {

        QString type;
        QString nbr;
        int id = index.data().toInt();
        QSqlQuery query=tmpsalles.rechercher_num(id);
        if (query.next()) {
        type= query.value(1).toString();
        nbr= query.value(2).toString();
        }


        QMessageBox::information(nullptr, QObject::tr("Salle"),
                          QObject::tr(" Type : %1 \n Nbr de places: %2 ") .arg(type).arg(nbr), QMessageBox::Cancel);

    }

    else if ((index.isValid()) && (index.column() == 2)  ) {

        QString nom;
        QString prenom;
        int id = index.data().toInt();
        if (!(id==0)){
        QSqlQuery query=tmpinstituteur.rechercher_id(id);
        if (query.next()) {
        nom= query.value(1).toString();
        prenom= query.value(2).toString();
        }


        QMessageBox::information(nullptr, QObject::tr("Responsable"),
                          QObject::tr(" Nom : %1 \n N° Prénom: %2 ") .arg(nom).arg(prenom), QMessageBox::Cancel);

       }
       }
}

void gestion_activite::on_pushButton_eleves_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void gestion_activite::on_pushButton_27_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void gestion_activite::on_pushButton_29_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void gestion_activite::on_pushButton_30_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}

void gestion_activite::on_pushButton_ajout_livre_clicked()
{
    QCheckBox* checkBox = ui->checkBox;
    int id = ui->lineEdit_ajout_id_livre->text().toInt();
    QString nom= ui->lineEdit_ajout_nom_livre->text();
    QString auteur= ui->lineEdit_ajout_auteur_livre->text();
    QString langue= ui->comboBox_langue_livre->currentText();
    int eleve;

    if(checkBox->checkState() == Qt::Unchecked)
        {
        eleve = ui->comboBox_eleve_livre->currentText().toInt();
        }
    else
        {
        eleve = 0;
        }
  Bibliotheque b(id,nom,auteur,langue,eleve);
  bool test=b.ajouter_livre();
  if(test)
{ui->table_livre->setModel(tmplivre.afficher_livre());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un livre"),
                  QObject::tr("Livre ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un livre"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_activite::on_lineEdit_modif_id_livre_textChanged()
{
    int id=ui->lineEdit_modif_id_livre->text().toInt();


    QSqlQuery query=tmplivre.rechercher_id_livre(id);
    QString nom_l,auteur_l,langue_l;
    QString eleve_l;


         if (query.next())
        {

        nom_l= query.value(1).toString();
        ui->lineEdit_modif_nom_livre->setText(nom_l);
        auteur_l= query.value(2).toString();
        ui->lineEdit_modif_auteur_livre->setText(auteur_l);
        langue_l= query.value(3).toString();
        ui->comboBox_modif_langue_livre->setCurrentText(langue_l);
        eleve_l= query.value(4).toString();
        ui->comboBox_modif_eleve_livre->setCurrentText(eleve_l);


        }
}

void gestion_activite::on_pushButton_modif_livre_clicked()
{
    bool test;
    QCheckBox* checkBox = ui->checkBox_2;
    QString nom= ui->lineEdit_modif_nom_livre->text();
    QString auteur= ui->lineEdit_modif_auteur_livre->text();
    QString langue= ui->comboBox_modif_langue_livre->currentText();
    int eleve = ui->comboBox_modif_eleve_livre->currentText().toInt();
    if(checkBox->checkState() == Qt::Unchecked){
        test =tmplivre.modifier_livre(ui->lineEdit_modif_id_livre->text().toInt(),ui->lineEdit_modif_nom_livre->text()
                ,auteur,langue,eleve);
        }
    else {
        test =tmplivre.modifier_livre(ui->lineEdit_modif_id_livre->text().toInt(),ui->lineEdit_modif_nom_livre->text()
                ,auteur,langue,0);

        }

      if(test)
      {
          ui->table_livre->setModel(tmplivre.afficher_livre());//refresh
          QMessageBox::information(nullptr, QObject::tr("Modifier un livre"),
                            QObject::tr("Livre modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier un livre"),
                        QObject::tr("Erreur !.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_activite::on_pushButton_supp_livre_clicked()
{
    int id = ui->lineEdit_supp_livre->text().toInt();
    QSqlQuery query=tmplivre.rechercher_id_livre(id);
    QString nom_l,auteur_l,langue_l;
    QString eleve_l;

    if (query.next())
   {
    nom_l= query.value(1).toString();
    auteur_l= query.value(2).toString();
    langue_l= query.value(3).toString();
    eleve_l= query.value(4).toString();
   }

    int reponse = QMessageBox::question(this, "Interrogatoire", "Voulez-vous supprimer le club :\n nom : " +nom_l+ "\n auteur : " +auteur_l+ "\n langue : " +langue_l+ "\n eleve : " +eleve_l , QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        bool test=tmplivre.supprimer_livre(id);
        if(test)
        {ui->table_livre->setModel(tmplivre.afficher_livre());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer un livre"),
                        QObject::tr("Livre supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un livre"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_supp_livre->clear() ;
    }
    else if (reponse == QMessageBox::No)
    {
        ui->lineEdit_supp_livre->clear() ;
    }
}

void gestion_activite::on_pushButton_PDF_livre_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->table_livre->model()->rowCount();
            const int columnCount =ui->table_livre->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("livre")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src='C:/Users/ksemt/Desktop/final/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des livres</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->table_livre->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->table_livre->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->table_livre->isColumnHidden(column)) {
                               QString data = ui->table_livre->model()->data(ui->table_livre->model()->index(row, column)).toString().simplified();
                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                           }
                       }
                       out << "</tr>\n";
                   }
                   out <<  "</table>\n"
                       "</body>\n"
                       "</html>\n";

                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);

                   QPrinter printer;

                   QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                   if (dialog->exec() == QDialog::Accepted) {
                       document->print(&printer);
                }
}

void gestion_activite::on_lineEdit_recherche_livre_textChanged()
{
    if(ui->lineEdit_recherche_livre->text() == "")
            {
                ui->table_livre->setModel(tmplivre.afficher_livre());
            }
            else
            {
                 ui->table_livre->setModel(tmplivre.rechercher_livre(ui->lineEdit_recherche_livre->text()));
            }
}

void gestion_activite::on_table_livre_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 4)  ) {

        QString nom;
        QString num;
        int id = index.data().toInt();
        if (!(id==0)){
        QSqlQuery query=tmpeleves.rechercher_id(id);
        if (query.next()) {
        nom= query.value(1).toString();
        num= query.value(4).toString();
        }


        QMessageBox::information(nullptr, QObject::tr("Salle"),
                          QObject::tr(" Nom : %1 \n N° de téléphone: %2 ") .arg(nom).arg(num), QMessageBox::Cancel);

       }
       }
}





void gestion_activite::on_pushButton_tri_asc_clicked()
{
    ui->table_excursion->setModel(tmpexcursion.trie(0));
}

void gestion_activite::on_pushButton_tri_desc_clicked()
{
    ui->table_excursion->setModel(tmpexcursion.trie(1));
}

void gestion_activite::on_table_excursion_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 2)  ) {

        QString nom;
        QString prenom;
        int id = index.data().toInt();
        if (!(id==0)){
        QSqlQuery query=tmpinstituteur.rechercher_id(id);
        if (query.next()) {
        nom= query.value(1).toString();
        prenom= query.value(2).toString();
        }


        QMessageBox::information(nullptr, QObject::tr("Responsable"),
                          QObject::tr(" Nom : %1 \n N° Prénom: %2 ") .arg(nom).arg(prenom), QMessageBox::Cancel);

       }
       }
}
