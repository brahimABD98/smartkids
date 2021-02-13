#include "gestion.h"
#include "ui_gestion.h"
#include <QMessageBox>
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include "stock.h"
#include "bibliotheque.h"
#include "gestion_activite.h"
#include "gestion_employe.h"
#include "charrad/gestiono9.h"
Gestion::Gestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion)
{
    ui->setupUi(this);
    ui->tableView_E->setModel(tmpeleve.afficher());
    ui->tableView_S->setModel(tmpsalle.afficher());
    ui->tableView_T->setModel(tmpbus.afficher());
}

Gestion::~Gestion()
{
    delete ui;
}

void Gestion::on_pushButton_AjouterE_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Gestion::on_pushButton_ModifierE_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Gestion::on_pushButton_SupprimerE_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Gestion::on_pushButton_AjouterS_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void Gestion::on_pushButton_ModifierS_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void Gestion::on_pushButton_SupprimerS_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}

void Gestion::on_pushButton_gest_eleve_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void Gestion::on_pushButton_gest_salle_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void Gestion::on_pushButton_AjoutEleve_clicked()
{
        int id = ui->lineEdit_Aj_id_E->text().toInt();
        QString nom = ui->lineEdit_Aj_NP_E->text();
        QDate daten =ui->dateEdit_Aj->date();
        int n = ui->lineEdit_Aj_NIV_E->text().toInt();
        QString par = ui->lineEdit_Aj_parent_E->text();
        int num = ui->lineEdit_Aj_num_E->text().toInt();
        eleves e(id,nom,daten,n,par,num);
        bool test=e.ajouter();
        if(test)
        {ui->tableView_E->setModel(tmpeleve.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un eleve"),
                          QObject::tr("Eleve ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un eleve"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);



}

void Gestion::on_lineEdit_Mo_id_E_textChanged()
{

    int id=ui->lineEdit_Mo_id_E->text().toInt();
    QSqlQuery query=tmpeleve.rechercher_id(id);
    QString nom ,par;
    int n,num;
    QDate daten;

    if (query.next())
            {
            nom= query.value(1).toString();
            ui->lineEdit_Mo_NP_E->setText(nom);
            daten = query.value(5).toDate();

            ui->dateEdit_Mo->setDate(daten);
            n= query.value(2).toInt();
            ui->lineEdit_Mo_niv_E->setText(QString::number(n));
            par= query.value(3).toString();
            ui->lineEdit_Mo_parent_E->setText(par);
            num= query.value(4).toInt();
            ui->lineEdit_Mo_num_E->setText(QString::number(num));

            }
            else
               {
        ui->lineEdit_Mo_NP_E->clear();
        ui->dateEdit_Mo->clear();
        ui->lineEdit_Mo_niv_E->clear();
        ui->lineEdit_Mo_parent_E->clear();
        ui->lineEdit_Mo_num_E->clear();
    }




}

void Gestion::on_pushButton_ModifierEleve_clicked()
{
        QString nom = ui->lineEdit_Mo_NP_E->text();
        QDate daten =ui->dateEdit_Mo->date();
        int n = ui->lineEdit_Mo_niv_E->text().toInt();
        QString par = ui->lineEdit_Mo_parent_E->text();
        int num = ui->lineEdit_Mo_num_E->text().toInt();




            bool test =tmpeleve.modifier(ui->lineEdit_Mo_id_E->text().toInt(),nom,daten,n,par,num);

              if(test)
              {
                    ui->tableView_E->setModel(tmpeleve.afficher());//refresh
              QMessageBox::information(nullptr, QObject::tr("Modifier Eleve"),
                                QObject::tr("Eleve modifié.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

              }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier Eleve"),
                                QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

}

void Gestion::on_pushButton_SupprimerEleve_clicked()
{
    int id =ui->lineEdit_Su_id_E->text().toInt();
    QSqlQuery query=tmpeleve.rechercher_id(id);
    QString nom ;


    if (query.next())
            {
            nom= query.value(1).toString();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Confirmation");
            msgBox.setText("voulez-vous vraiment supprimer L'eleve ?");
            msgBox.setInformativeText(QString("%1 : %2").arg(id).arg(nom));
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::Yes){





        bool test =tmpeleve.supprimer(id);







            if(test)
            {ui->tableView_E->setModel(tmpeleve.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Supprimer Eleve"),
                            QObject::tr("Eleve supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Supprimer Eleve"),QObject::tr("Erreur !.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }


            }

    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Eleve"),
                    QObject::tr("Erreur eleve introuvable !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion::on_lineEdit_RechercheE_textChanged()
{
    if(ui->lineEdit_RechercheE->text() == "")
            {
                ui->tableView_E->setModel(tmpeleve.afficher());
            }
            else
            {
                 ui->tableView_E->setModel(tmpeleve.rechercher(ui->lineEdit_RechercheE->text()));
            }
}

void Gestion::on_pushButton_PDFE_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_E->model()->rowCount();
            const int columnCount =ui->tableView_E->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        ":/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des eleves</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_E->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_E->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_E->isColumnHidden(column)) {
                               QString data = ui->tableView_E->model()->data(ui->tableView_E->model()->index(row, column)).toString().simplified();
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

void Gestion::on_pushButton_resetE_clicked()
{
    ui->lineEdit_Aj_id_E->clear();
    ui->lineEdit_Aj_NP_E->clear();
    ui->dateEdit_Aj->clear();
    ui->lineEdit_Aj_NIV_E->clear();
    ui->lineEdit_Aj_parent_E->clear();
     ui->lineEdit_Aj_num_E->clear();
}

void Gestion::on_pushButton_resetME_clicked()
{
    ui->lineEdit_Mo_id_E->clear();
    ui->lineEdit_Mo_NP_E->clear();
    ui->dateEdit_Mo->clear();
    ui->lineEdit_Mo_niv_E->clear();
    ui->lineEdit_Mo_parent_E->clear();
    ui->lineEdit_Mo_num_E->clear();
}

void Gestion::on_pushButton_resetSE_clicked()
{
    ui->lineEdit_Su_id_E->clear();
}

void Gestion::on_pushButton_AjouterSalle_clicked()
{
    int n = ui->lineEdit_Aj_num_S->text().toInt();
        QString t = ui->lineEdit_Aj_type_S->text();
        int nbr = ui->lineEdit_Aj_nbrp_S->text().toInt();

        salles s(n,t,nbr);
        bool test=s.ajouter();
        if(test)
        {ui->tableView_S->setModel(tmpsalle.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un salle"),
                          QObject::tr("Salle ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un salle"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

}

void Gestion::on_lineEdit_Mo_num_S_textChanged()
{
    int num=ui->lineEdit_Mo_num_S->text().toInt();
        QSqlQuery query=tmpsalle.rechercher_num(num);
        QString t;
        int nbr;


        if (query.next())
                {
                t= query.value(1).toString();
                ui->lineEdit_Mo_type_S->setText(t);
                nbr= query.value(2).toInt();
                ui->lineEdit_Mo_nbrp_S->setText(QString::number(nbr));

                }
                else
                   {
            ui->lineEdit_Mo_type_S->clear();
            ui->lineEdit_Mo_nbrp_S->clear();
            }
}

void Gestion::on_pushButton_ModifierSalle_clicked()
{
    QString t = ui->lineEdit_Mo_type_S->text();
        int nbr = ui->lineEdit_Mo_nbrp_S->text().toInt();




            bool test =tmpsalle.modifier(ui->lineEdit_Mo_num_S->text().toInt(),t,nbr);

              if(test)
              {
                    ui->tableView_S->setModel(tmpsalle.afficher());//refresh
              QMessageBox::information(nullptr, QObject::tr("Modifier Salle"),
                                QObject::tr("Salle modifié.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

              }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier Salle"),
                                QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion::on_pushButton_SupprimerSalle_clicked()
{
    int id =ui->lineEdit_Su_num_S->text().toInt();
        QSqlQuery query=tmpsalle.rechercher_num(id);
        QString type ;


        if (query.next())
                {
                type= query.value(1).toString();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Confirmation");
                msgBox.setText("voulez-vous vraiment supprimer La salle ?");
                msgBox.setInformativeText(QString("%1 de %2").arg(id).arg(type));
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                if(msgBox.exec() == QMessageBox::Yes){





            bool test =tmpsalle.supprimer(id);







                if(test)
                {ui->tableView_S->setModel(tmpsalle.afficher());//refresh
                    QMessageBox::information(nullptr, QObject::tr("Supprimer Salle"),
                                QObject::tr("Salle supprimé.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Supprimer Salle"),QObject::tr("Erreur !.\n""Click Cancel to exit."), QMessageBox::Cancel);
            }


                }

        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Salle"),
                        QObject::tr("Erreur Salle introuvable !\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion::on_lineEdit_rechercherS_textChanged()
{
    if(ui->lineEdit_rechercherS->text() == "")
                {
                    ui->tableView_S->setModel(tmpsalle.afficher());
                }
                else
                {
                     ui->tableView_S->setModel(tmpsalle.rechercher(ui->lineEdit_rechercherS->text()));
                }
}

void Gestion::on_pushButton_PDFS_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_S->model()->rowCount();
            const int columnCount =ui->tableView_S->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("salle")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des salles</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_S->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_S->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_S->isColumnHidden(column)) {
                               QString data = ui->tableView_S->model()->data(ui->tableView_S->model()->index(row, column)).toString().simplified();
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


void Gestion::on_pushButton_RESETAMS_clicked()
{
   ui->lineEdit_Aj_num_S->clear();
        ui->lineEdit_Aj_type_S->clear();
         ui->lineEdit_Aj_nbrp_S->clear();
}

void Gestion::on_pushButton_ResetMS_clicked()
{
    ui->lineEdit_Mo_num_S->clear();
    ui->lineEdit_Mo_type_S->clear();
    ui->lineEdit_Mo_nbrp_S->clear();
}

void Gestion::on_pushButton_RESETSS_clicked()
{
    ui->lineEdit_Su_num_S->clear();
}




void Gestion::on_pushButton_15_clicked()
{
    hide();
    gestion_activite ga;
    ga.exec();
}

void Gestion::on_pushButton_16_clicked()
{
    hide();
    gestion_employe g;
    g.exec();
}



void Gestion::on_pushButton_17_clicked()
{
    hide();
    gestiono9 G;
    G.exec();
}

void Gestion::on_pushButton_gest_trans_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void Gestion::on_pushButton_AjouterT_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void Gestion::on_pushButton_ModifierT_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void Gestion::on_pushButton_SupprimerT_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}

void Gestion::on_pushButton_AjoutTrans_clicked()
{
    int id = ui->lineEdit_Aj_id_T->text().toInt();
    QString model = ui->lineEdit_Aj_mod_T->text();
    QString chauff =ui->lineEdit_Aj_ch_T->text();
    QString zone = ui->lineEdit_Aj_zone_T->text();
    int n = ui->lineEdit_Aj_nbrp_T->text().toInt();
    bus b(id,model,chauff,zone,n);
    bool test=b.ajouter();
    if(test)
    {ui->tableView_T->setModel(tmpbus.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un bus"),
                      QObject::tr("Bus ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un bus"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion::on_lineEdit_Mo_id_T_textChanged()
{
    int id=ui->lineEdit_Mo_id_T->text().toInt();
        QSqlQuery query=tmpbus.rechercher_id(id);
        QString mod ,chauff,zone;
        int n;


        if (query.next())
                {
                mod= query.value(1).toString();
                ui->lineEdit_Mo_mod_T->setText(mod);

                chauff= query.value(2).toString();
                ui->lineEdit_Mo_ch_T->setText(chauff);
                zone= query.value(3).toString();
                ui->lineEdit_Mo_zone_T->setText(zone);
                n= query.value(4).toInt();
                ui->lineEdit_Mo_nbrp_T->setText(QString::number(n));
                }
                else
                   {
            ui->lineEdit_Mo_mod_T->clear();
            ui->lineEdit_Mo_ch_T->clear();
            ui->lineEdit_Mo_zone_T->clear();
            ui->lineEdit_Mo_nbrp_T->clear();

        }
}

void Gestion::on_pushButton_ModifTrans_clicked()
{
    QString model = ui->lineEdit_Mo_mod_T->text();
    QString chauff =ui->lineEdit_Mo_ch_T->text();
    QString zone = ui->lineEdit_Mo_zone_T->text();
    int n = ui->lineEdit_Mo_nbrp_T->text().toInt();




                bool test =tmpbus.modifier(ui->lineEdit_Mo_id_T->text().toInt(),model,chauff,zone,n);

                  if(test)
                  {
                        ui->tableView_T->setModel(tmpbus.afficher());//refresh
                  QMessageBox::information(nullptr, QObject::tr("Modifier Bus"),
                                    QObject::tr("Bus modifié.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

                  }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("Bus Eleve"),
                                    QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion::on_pushButton_SupprimerTrans_clicked()
{
    int id =ui->lineEdit_Su_id_T->text().toInt();
        QSqlQuery query=tmpbus.rechercher_id(id);
        QString nom ;


        if (query.next())
                {
                nom= query.value(1).toString();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Confirmation");
                msgBox.setText("voulez-vous vraiment supprimer Le bus ?");
                msgBox.setInformativeText(QString("%1 : %2").arg(id).arg(nom));
                msgBox.setStandardButtons(QMessageBox::Yes);
                msgBox.addButton(QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                if(msgBox.exec() == QMessageBox::Yes){





            bool test =tmpbus.supprimer(id);







                if(test)
                {ui->tableView_T->setModel(tmpbus.afficher());//refresh
                    QMessageBox::information(nullptr, QObject::tr("Supprimer Bus"),
                                QObject::tr("Bus supprimé.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Supprimer Bus"),QObject::tr("Erreur !.\n""Click Cancel to exit."), QMessageBox::Cancel);
            }


                }

        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Bus"),
                        QObject::tr("Erreur Bus introuvable !\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion::on_lineEdit_RechercheT_textChanged()
{
    if(ui->lineEdit_RechercheT->text() == "")
                {
                    ui->tableView_T->setModel(tmpbus.afficher());
                }
                else
                {
                     ui->tableView_T->setModel(tmpbus.rechercher(ui->lineEdit_RechercheT->text()));
                }
}

void Gestion::on_pushButton_PDFT_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView_T->model()->rowCount();
                const int columnCount =ui->tableView_T->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("bus")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                            "<h1>Liste des eleves</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView_T->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView_T->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_T->isColumnHidden(column)) {
                                   QString data = ui->tableView_T->model()->data(ui->tableView_T->model()->index(row, column)).toString().simplified();
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

void Gestion::on_pushButton_resetT_clicked()
{
    ui->lineEdit_Aj_id_T->clear();
    ui->lineEdit_Aj_mod_T->clear();
    ui->lineEdit_Aj_ch_T->clear();
    ui->lineEdit_Aj_zone_T->clear();
    ui->lineEdit_Aj_nbrp_T->clear();
}

void Gestion::on_pushButton_resetTm_clicked()
{
    ui->lineEdit_Mo_id_T->clear();
    ui->lineEdit_Mo_mod_T->clear();
    ui->lineEdit_Mo_ch_T->clear();
    ui->lineEdit_Mo_zone_T->clear();
    ui->lineEdit_Mo_nbrp_T->clear();

}

void Gestion::on_pushButton_resetTs_clicked()
{
    ui->lineEdit_Su_id_T->clear();
}



void Gestion::on_pushButton_stock_clicked()
{
    hide();
    stock se;
    se.exec();
}
void Gestion::on_tableView_S_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 0)  ) {

                int i=0;

                QString npr;
                QString qu;
                QString aux;
                int id = index.data().toInt();
                int rows = 0;
                QSqlQuery query("SELECT COUNT(*) FROM equipement ");
                if (query.next()) {
                    rows = query.value(0).toInt();
                }



                do{

                 QSqlQuery query=tmpequipement.rechercher_salle(id);
                if (query.seek(i)) {
                 npr= query.value(1).toString();
                 qu= query.value(2).toString();
                 aux=aux+qu+":"+npr+"\n";
                }

                i++;


                }while(i<rows);

                QMessageBox::information(nullptr, QObject::tr("Salle"),
                                  QObject::tr("La salle est equipe de :\n%1") .arg(aux), QMessageBox::Cancel);

            }
}

void Gestion::on_tableView_E_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 0)  ) {

                int i=0;

                QString npr;
                QString qu;
                QString aux;
                int id = index.data().toInt();
                int rows = 0;
                QSqlQuery query("SELECT COUNT(*) FROM bibliotheque ");
                if (query.next()) {
                    rows = query.value(0).toInt();
                }



                do{

                 QSqlQuery query=tmpbibliotheque.rechercher_eleve(id);
                if (query.seek(i)) {
                 npr= query.value(1).toString();
                 qu= query.value(2).toString();
                 aux=aux+qu+" de "+npr+"\n";
                }

                i++;


                }while(i<rows);

                QMessageBox::information(nullptr, QObject::tr("Eleve"),
                                  QObject::tr("l'eleve %2 a emprunter de la bibliotheque:\n%1") .arg(aux).arg(id) , QMessageBox::Cancel);

            }
}
