#include "gestion_activite.h"
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

gestion_activite::gestion_activite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_activite)
{
    ui->setupUi(this);
    ui->table_club->setModel(tmpclub.afficher_club());
    ui->table_excursion->setModel(tmpexcursion.afficher_excursion());
    ui->dateEdit_excu_ajout->setDate(QDate::currentDate());
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
    QString responsable= ui->lineEdit_ajout_res_c->text();
    QString jour= ui->comboBox_ajout_dateclub->currentText();
    int salle = ui->lineEdit_ajout_salle_c->text().toInt();
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
    QString responsable= ui->lineEdit_ajout_res_exc->text();
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
        ui->lineEdit_modif_res_c->setText(responsable_c);
        jour_c= query.value(3).toString();
        ui->lineEdit_modif_jour_c->setText(jour_c);
        salle_c= query.value(4).toString();
        ui->lineEdit_modif_salle_c->setText(salle_c);


        }
}

void gestion_activite::on_pushButton_modif_club_clicked()
{
    QString nom= ui->lineEdit_modif_nom_c->text();
    QString responsable= ui->lineEdit_modif_res_c->text();
    QString jour= ui->lineEdit_modif_jour_c->text();
    int salle = ui->lineEdit_modif_salle_c->text().toInt();

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
        ui->lineEdit_modif_res_exc->setText(responsable_e);
        date_e= query.value(3).toString();
        ui->lineEdit_modif_date_exc->setText(date_e);
        prix_e= query.value(4).toString();
        ui->lineEdit_modif_prix_exc->setText(prix_e);

        }
}

void gestion_activite::on_pushButton_modif_exc_clicked()
{
    QString destination= ui->lineEdit_modif_dest_exc->text();
    QString responsable= ui->lineEdit_modif_res_exc->text();
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
