#include "stock.h"
#include "ui_stock.h"
#include "aliment.h"
#include <QMessageBox>
#include "equipement.h"
#include <QDebug>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
#include "gestion.h"
#include "gestion_activite.h"
#include "gestion_employe.h"
#include "charrad/gestiono9.h"
#include "reclamation.h"
stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);
    //affichage aliment et equipement
    ui->tableView_aliment->setModel(tmpaliment.afficher());
    ui->tableView_equipement->setModel(tmpequipement.afficher());
    ui->tab_reclamation->setModel(tmpreclamation.afficher());
    ui->comboBox_salle_a_e->setModel(tmpequipement.affichersalle());
    ui->comboBox_salle_m_e->setModel(tmpequipement.affichersalle());

}

stock::~stock()
{
    delete ui;
}
/*clicked interface crud aliment */
void stock::on_pushButton_ajouter_aliment_clicked()
{
    ui->stackedWidget_crud_aliment->setCurrentIndex(0);
}

void stock::on_pushButton_modifier_aliment_clicked()
{
    ui->stackedWidget_crud_aliment->setCurrentIndex(1);
}

void stock::on_pushButton_supprimer_aliment_clicked()
{
    ui->stackedWidget_crud_aliment->setCurrentIndex(2);
}

void stock::on_pushButton_ok_a_a_clicked()
{
    int id=   ui->lineEdit_id_aliment->text().toInt();

           QString nom= ui->lineEdit_nom_aliment->text();
           QString type= ui->lineEdit_type_aliment->text();

           QDate dlc =ui->dateEdit_dlc->date();

           double prix_unitaire = ui->doubleSpinBox_prix_unutaire_aliments->value();
           int quantite=ui->spinBox_quatite_aliments->text().toInt();
           double prix_total=prix_unitaire*quantite;
           aliments a (id ,nom,type,dlc,prix_unitaire,prix_total,quantite);


           bool test=a.ajouter();
           if(test)
         {
               ui->tableView_aliment->setModel(tmpaliment.afficher());
          //refresh
         QMessageBox::information(nullptr, QObject::tr("Ajouter un aliment"),
                           QObject::tr("aliment ajouté.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);



         }
           else
               QMessageBox::critical(nullptr, QObject::tr("Ajouter un aliement"),
                           QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);


}

void stock::on_pushButton_ok_m_a_clicked()
{
    double prix_totale= ui->spinBox_quatite_modif_aliments->text().toInt() * ui->doubleSpinBox_prix_unutaire_modif_aliments->value() ;
       bool test =tmpaliment.modifier_aliments(ui->lineEdit_id_modif_aliment->text().toInt(),ui->lineEdit_nom_modif_aliment->text(),
                                              ui->lineEdit_type_modif_aliment->text(),ui->dateEdit_dlc_modif_aliment->date(),
                                      ui->spinBox_quatite_modif_aliments->text().toInt(),ui->doubleSpinBox_prix_unutaire_modif_aliments->value(),prix_totale);

         if(test)
         {
               ui->tableView_aliment->setModel(tmpaliment.afficher());//refresh
         QMessageBox::information(nullptr, QObject::tr("modifier un aliment"),
                           QObject::tr("aliment modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

         }
           else
               QMessageBox::critical(nullptr, QObject::tr("modifier un aliment"),
                           QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void stock::on_pushButton_ok_s_a_clicked()
{
    int id =ui->lineEdit_id_supp_aliment->text().toInt();
    QSqlQuery query=tmpaliment.rechercher_id(id);
    QString nom ;


    if (query.next())
            {
            nom= query.value(1).toString();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Confirmation");
            msgBox.setText("voulez-vous vraiment supprimer L'aliment ?");
            msgBox.setInformativeText(QString("%1 : %2").arg(id).arg(nom));
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::Yes){





        bool test =tmpaliment.supprimer(id);







            if(test)
            {ui->tableView_aliment->setModel(tmpaliment.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Supprimer aliment"),
                            QObject::tr("aliment supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->lineEdit_id_supp_aliment->clear();

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("supprimer aliment"),QObject::tr("Erreur !.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }


            }

    else
      {  QMessageBox::critical(nullptr, QObject::tr("Supprimer aliment"),
                    QObject::tr("Erreur aliment introuvable !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_id_supp_aliment->clear();

    }
}

void stock::on_pushButton_annuler_ajouter_aliment_clicked()
{
ui->lineEdit_id_aliment->clear();
ui->lineEdit_nom_aliment->clear();
ui->lineEdit_type_aliment->clear();
ui->spinBox_quatite_aliments->clear();
ui->dateEdit_dlc->clear();
ui->doubleSpinBox_prix_unutaire_aliments->clear();
}

void stock::on_pushButton_annuler_modif_aliment_clicked()
{
    ui->lineEdit_id_modif_aliment->clear();
    ui->lineEdit_nom_modif_aliment->clear();
    ui->dateEdit_dlc_modif_aliment->clear();
    ui->spinBox_quatite_modif_aliments->clear();
    ui->lineEdit_type_modif_aliment->clear();
    ui->doubleSpinBox_prix_unutaire_modif_aliments->clear();
}

void stock::on_pushButton_supp_aliment_clicked()
{
    ui->lineEdit_id_supp_aliment->clear();
}

void stock::on_pushButton_exporter_aliment_clicked()
{
    ui->stackedWidget_crud_aliment->setCurrentIndex(3);
}

void stock::on_lineEdit_id_modif_aliment_textChanged()
{
    int id=ui->lineEdit_id_modif_aliment->text().toInt();
    QSqlQuery query=tmpaliment.rechercher_id(id);
    QString nom;
    QString type;

    QDate dlc ;
    double prix_unitaire;
    int quantite;
  //  double prix_total;

    if (query.next())
            {
            nom= query.value(1).toString();
            ui->lineEdit_nom_modif_aliment->setText(nom);

            dlc = query.value(3).toDate();
            ui->dateEdit_dlc_modif_aliment->setDate(dlc);

            quantite= query.value(6).toInt();
            ui->spinBox_quatite_modif_aliments->setValue(quantite);

            type= query.value(2).toString();
            ui->lineEdit_type_modif_aliment->setText(type);

            prix_unitaire= query.value(4).toDouble();
            ui->doubleSpinBox_prix_unutaire_modif_aliments->setValue(prix_unitaire);

            }
            else
               {
        ui->lineEdit_nom_modif_aliment->clear();
        ui->dateEdit_dlc_modif_aliment->clear();
        ui->spinBox_quatite_modif_aliments->clear();
        ui->lineEdit_type_modif_aliment->clear();
        ui->doubleSpinBox_prix_unutaire_modif_aliments->clear();
    }


}

void stock::on_lineEdit_id_supp_aliment_textChanged()
{
    QString id=ui->lineEdit_id_supp_aliment->text();
    if(ui->lineEdit_id_supp_aliment->text() == "")
            {
                ui->tableView_aliment->setModel(tmpaliment.afficher());
            }
            else
            {
                 ui->tableView_aliment->setModel(tmpaliment.recherche(id));
    }
}



void stock::on_pushButton_tri_aliment_clicked()
{
     ui->stackedWidget_crud_aliment->setCurrentIndex(4);
}

void stock::on_pushButton_ok_tri_aliment_clicked()
{
    QString mode="ASC";
   if (ui->checkBox_tri_aliment->checkState()==false)
       mode="DESC";
// ui->comboBox->currentText();
ui->tableView_aliment->setModel(tmpaliment.trier(ui->comboBox_tri_aliment->currentText(),mode));

}

void stock::on_lineEdit_rechercher_aliment_textChanged()
{
    if(ui->lineEdit_rechercher_aliment->text() == "")
            {
                ui->tableView_aliment->setModel(tmpaliment.afficher());
            }
            else
            {
                 ui->tableView_aliment->setModel(tmpaliment.recherche(ui->lineEdit_rechercher_aliment->text()));
                 qDebug() <<ui->lineEdit_rechercher_aliment->text();
            }
}



void stock::on_pushButton_print_aliment_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_aliment->model()->rowCount();
            const int columnCount =ui->tableView_aliment->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des ALIMENT</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_aliment->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_aliment->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_aliment->isColumnHidden(column)) {
                               QString data = ui->tableView_aliment->model()->data(ui->tableView_aliment->model()->index(row, column)).toString().simplified();
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
                       document->print(&printer);}
}

void stock::on_pushButton_pdf_aliment_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_aliment->model()->rowCount();
            const int columnCount =ui->tableView_aliment->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des ALIMENT</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_aliment->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_aliment->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_aliment->isColumnHidden(column)) {
                               QString data = ui->tableView_aliment->model()->data(ui->tableView_aliment->model()->index(row, column)).toString().simplified();
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


      //  QTextDocument document;
       // document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("aliment.pdf");
        document->print(&printer);
}

void stock::on_pushButton_aliment_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void stock::on_pushButton_equipement_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void stock::on_pushButton_ajouter_equipement_clicked()
{
    ui->stackedWidget_crud_equipement->setCurrentIndex(0);
}

void stock::on_pushButton_modifier_equip_clicked()
{
    ui->stackedWidget_crud_equipement->setCurrentIndex(1);
}

void stock::on_pushButton_supp_equip_clicked()
{
    ui->stackedWidget_crud_equipement->setCurrentIndex(2);
}

void stock::on_pushButton_exporter_equip_clicked()
{
    ui->stackedWidget_crud_equipement->setCurrentIndex(4);

}

void stock::on_pushButton_tri_equipement_clicked()
{
    ui->stackedWidget_crud_equipement->setCurrentIndex(5);

}

void stock::on_pushButton_a_e_clicked()
{
    int id=   ui->lineEdit_id_equipement->text().toInt();

           QString nom= ui->lineEdit_nom_equipement->text();
           QString type= ui->lineEdit_type_equipement->text();
           QString salle_affecter =ui->comboBox_salle_a_e->currentText();
           //QDate dlc =ui->dateEdit_dlc->date();
           double prix_unitaire = ui->doubleSpinBox_prix_unutaire_equipement->value();
           int quantite=ui->spinBox_quatite_equipement->text().toInt();
           double prix_total=prix_unitaire*quantite;
           equipement e ( id , nom, quantite, type, salle_affecter,prix_unitaire,prix_total);


           bool test=e.ajouter();
           if(test)
         {
               ui->tableView_equipement->setModel(tmpequipement.afficher());
          //refresh
         QMessageBox::information(nullptr, QObject::tr("Ajouter un equipement"),
                           QObject::tr("equipement ajouté.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);



         }
           else
               QMessageBox::critical(nullptr, QObject::tr("Ajouter un equipement"),
                           QObject::tr("Erreur !.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void stock::on_pushButton_ok_m_e_clicked()
{
    double prix_totale= ui->spinBox_quatite_modif_equip->text().toInt() * ui->doubleSpinBox_prix_unutaire_modif_equip->value() ;
       bool test =tmpequipement.modifier_equipement(ui->lineEdit_id_modif_equip->text().toInt(),ui->lineEdit_nom_modif_equip->text(),   ui->spinBox_quatite_modif_equip->text().toInt(),
                                              ui->lineEdit_type_modif_equip->text(),             ui->comboBox_salle_m_e->currentText()
,
                                   ui->doubleSpinBox_prix_unutaire_modif_equip->value(),prix_totale);

         if(test)
         {
               ui->tableView_equipement->setModel(tmpequipement.afficher());//refresh
         QMessageBox::information(nullptr, QObject::tr("modifier un equipement"),
                           QObject::tr("equipement modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

         }
           else
               QMessageBox::critical(nullptr, QObject::tr("modifier un equipement"),
                           QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void stock::on_lineEdit_id_modif_equip_textChanged()
{
    int id=ui->lineEdit_id_modif_equip->text().toInt();
    QSqlQuery query=tmpequipement.rechercher_id(id);
    QString nom;
    QString type;

    QString salle_affecter ;
    double prix_unitaire;
    int quantite;
  //  double prix_total;

    if (query.next())
            {
            nom= query.value(1).toString();
            ui->lineEdit_nom_modif_equip->setText(nom);

            salle_affecter= query.value(4).toString();

            ui->comboBox_salle_m_e->setCurrentText(salle_affecter);


            quantite= query.value(2).toInt();
            ui->spinBox_quatite_modif_equip->setValue(quantite);

            type= query.value(3).toString();
            ui->lineEdit_type_modif_equip->setText(type);

            prix_unitaire= query.value(5).toDouble();
            ui->doubleSpinBox_prix_unutaire_modif_equip->setValue(prix_unitaire);

            }
            else
               {
        ui->lineEdit_nom_modif_equip->clear();
        ui->comboBox_salle_m_e->clear();
        ui->spinBox_quatite_modif_equip->clear();
        ui->lineEdit_type_modif_equip->clear();
        ui->doubleSpinBox_prix_unutaire_modif_equip->clear();
    }

}

void stock::on_lineEdit_id_supp_equip_textChanged()
{
    QString id=ui->lineEdit_id_supp_equip->text();
    if(ui->lineEdit_id_supp_equip->text() == "")
            {
                ui->tableView_equipement->setModel(tmpequipement.afficher());
            }
            else
            {
                 ui->tableView_equipement->setModel(tmpequipement.recherche(id));
    }
}

void stock::on_pushButton_s_e_clicked()
{
    int id =ui->lineEdit_id_supp_equip->text().toInt();
    QSqlQuery query=tmpequipement.rechercher_id(id);
    QString nom ;


    if (query.next())
            {
            nom= query.value(1).toString();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Confirmation");
            msgBox.setText("voulez-vous vraiment supprimer L'equipement ?");
            msgBox.setInformativeText(QString("%1 : %2").arg(id).arg(nom));
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::Yes){





        bool test =tmpequipement.supprimer(id);







            if(test)
            {ui->tableView_equipement->setModel(tmpequipement.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Supprimer equipement"),
                            QObject::tr("equipement supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->lineEdit_id_supp_equip->clear();

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("supprimer equipement"),QObject::tr("Erreur !.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }


            }

    else
      {  QMessageBox::critical(nullptr, QObject::tr("Supprimer equipement"),
                    QObject::tr("Erreur equipement introuvable !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_id_supp_aliment->clear();

    }
}





void stock::on_lineEdit_recherche_equip_textChanged()
{
    if(ui->lineEdit_recherche_equip->text() == "")
            {
                ui->tableView_equipement->setModel(tmpequipement.afficher());
            }
            else
            {
                 ui->tableView_equipement->setModel(tmpequipement.recherche(ui->lineEdit_recherche_equip->text()));

            }
}

void stock::on_pushButton_ok_tri_equipement_clicked()
{

    QString mode="ASC";
   if (ui->checkBox_tri_equipement->checkState()==false)
       mode="DESC";
// ui->comboBox->currentText();
ui->tableView_equipement->setModel(tmpequipement.trier(ui->comboBox_tri_equipement->currentText(),mode));
}

void stock::on_pushButton_pdf_equipement_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_equipement->model()->rowCount();
            const int columnCount =ui->tableView_equipement->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des equipements</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_equipement->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_equipement->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_equipement->isColumnHidden(column)) {
                               QString data = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, column)).toString().simplified();
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


  //  QTextDocument document;
   // document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("equipement.pdf");
    document->print(&printer);
}

void stock::on_pushButton_print_equipement_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_equipement->model()->rowCount();
            const int columnCount =ui->tableView_equipement->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des equipements</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_equipement->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_equipement->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_equipement->isColumnHidden(column)) {
                               QString data = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, column)).toString().simplified();
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
                       document->print(&printer);}
}

void stock::on_pushButton_eleves_2_clicked()
{
      hide();
   Gestion g;
   g.exec();

}

void stock::on_pushButton_activite_clicked()
{
    hide();
    gestion_activite ga;
    ga.exec();
}

void stock::on_pushButton_employer_clicked()
{
    hide();
 gestion_employe g;
 g.exec();
}


void stock::on_pushButton_comp_clicked()
{
    hide();
    gestiono9 G;
    G.exec();
}

void stock::on_pushButton_equipement_2_clicked()
{

}

void stock::on_pushButton_reclamation_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void stock::on_pushButton_ajouter_rec_clicked()
{
    ui->stackedWidget_crud_rec->setCurrentIndex(0);
}

void stock::on_pushButton_modifier_rec_clicked()
{
 ui->stackedWidget_crud_rec->setCurrentIndex(1);
}

void stock::on_pushButton_supprimer_rec_clicked()
{
    ui->stackedWidget_crud_rec->setCurrentIndex(2);
}

void stock::on_pushButton_exporter_rec_clicked()
{
    ui->stackedWidget_crud_rec->setCurrentIndex(3);
}

void stock::on_pushButton_ok_a_r_clicked()
{
    int id=   ui->lineEdit_id_ar->text().toInt();

           QString nom= ui->lineEdit_nom_ar->text();
           QString mail= ui->lineEdit_mail_ar->text();
           QDate dater =ui->dateEdit_date_ar->date();


           QString message= ui->textEdit_msg_ar->toPlainText();
           int i,j;
           bool test1=false;
           bool test2=true;

           for (i=0 ; i<mail.length();i++)
           {
                if (mail[i]=="@")
           {
                 test1=true;
           }
                }
           for (j=0;j<nom.length();j++) {
               if (nom[j]=="0" || nom[j]=="1" || nom[j]=="2" || nom[j]=="3" || nom[j]=="4" || nom[j]=="5" || nom[j]=="6" || nom[j]=="7" || nom[j]=="8" || nom[j]=="9")
                  {
                   test2=false;
                   }
           }

           if (test1 && test2)
           {
            reclamation r(id,nom,dater,mail,message);
            bool test=r.ajouter();
            if(test)
          {
                ui->tab_reclamation->setModel(tmpreclamation.afficher());

          QMessageBox::information(nullptr, QObject::tr("Ajouter une réclamation"),
                            QObject::tr("Réclamation ajoutée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

          }
            else
                QMessageBox::critical(nullptr, QObject::tr("Ajouter une réclamation"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

          }
}

void stock::on_lineEdit_id_mr_textChanged()
{
    int id=ui->lineEdit_id_mr->text().toInt();
    QSqlQuery query=tmpreclamation.rechercher_id(id);
    QString nom;

    QDate dater ;
    QString mail;
    QString message;
  //  double prix_total;

    if (query.next())
            {
            nom= query.value(1).toString();
            ui->lineEdit_nom_mr->setText(nom);

            dater = query.value(2).toDate();
            ui->dateEdit_mr->setDate(dater);


            mail= query.value(3).toString();
            ui->lineEdit_mail_mr->setText(mail);

            message= query.value(4).toString();
            ui->textEdit_msg_mr->setText(message);

            }
            else
               {
        ui->lineEdit_nom_mr->clear();
        ui->dateEdit_mr->clear();
        ui->lineEdit_mail_mr->clear();
        ui->textEdit_msg_mr->clear();
    }


}

void stock::on_pushButton_ok_mr_clicked()
{
           int id=   ui->lineEdit_id_mr->text().toInt();
           QString nom= ui->lineEdit_nom_mr->text();
           QString mail= ui->lineEdit_mail_mr->text();
           QDate dater =ui->dateEdit_mr->date();
           QString message=ui->textEdit_msg_mr->toPlainText();


    bool test =tmpreclamation.modifier_reclamation(id,nom,dater,mail,message);

         if(test)
         {
               ui->tab_reclamation->setModel(tmpreclamation.afficher());//refresh
         QMessageBox::information(nullptr, QObject::tr("modifier une réclamation"),
                           QObject::tr("réclamation modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

         }
           else
               QMessageBox::critical(nullptr, QObject::tr("modifier une réclamation"),
                           QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void stock::on_lineEdit_id_supp_rec_textChanged()
{
    QString id=ui->lineEdit_id_supp_rec->text();
    if(ui->lineEdit_id_supp_rec->text() == "")
            {
                ui->tab_reclamation->setModel(tmpreclamation.afficher());
            }
            else
            {
                 ui->tab_reclamation->setModel(tmpreclamation.recherche(id));
            }
}


void stock::on_pushButton_s_r_clicked()
{
    int id =ui->lineEdit_id_supp_rec->text().toInt();
    QSqlQuery query=tmpreclamation.rechercher_id(id);
    QString nom ;
           if (query.next())
            {
            nom= query.value(1).toString();
            QMessageBox msgBox;
            msgBox.setWindowTitle("Confirmation");
            msgBox.setText("voulez-vous vraiment supprimer la reclamation ?");
            msgBox.setInformativeText(QString("%1 : %2").arg(id).arg(nom));
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::Yes){
        bool test =tmpreclamation.supprimer(id);
            if(test)
            {ui->tab_reclamation->setModel(tmpreclamation.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Supprimer réclamation"),
                            QObject::tr("reclamation supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->lineEdit_id_supp_rec->clear();
            }
            else
                QMessageBox::critical(nullptr, QObject::tr("supprimer reclamation"),QObject::tr("Erreur !.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }
            }
    else
      {  QMessageBox::critical(nullptr, QObject::tr("Supprimer reclamation"),
                    QObject::tr("Erreur reclamaiton introuvable !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_id_supp_rec->clear();
    }
}

void stock::on_lineEdit_recherche_rec_textChanged()
{
    if(ui->lineEdit_recherche_rec->text() == "")
            {
                ui->tab_reclamation->setModel(tmpreclamation.afficher());
            }
            else
            {
                 ui->tab_reclamation->setModel(tmpreclamation.recherche(ui->lineEdit_recherche_rec->text()));
           //      qDebug() <<ui->lineEdit_rechercher_aliment->text();
            }
}

void stock::on_pushButton_print_rec_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tab_reclamation->model()->rowCount();
            const int columnCount =ui->tab_reclamation->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des reclamations</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_reclamation->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab_reclamation->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tab_reclamation->isColumnHidden(column)) {
                               QString data = ui->tab_reclamation->model()->data(ui->tab_reclamation->model()->index(row, column)).toString().simplified();
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
                       document->print(&printer);}
}

void stock::on_pushButton_pdf_rec_clicked()
{
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tab_reclamation->model()->rowCount();
            const int columnCount =ui->tab_reclamation->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                        "<h1>Liste des reclamation</h1>"



                        "<table border=1 cellspacing=0 cellpadding=2>\n";


            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_reclamation->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab_reclamation->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tab_reclamation->isColumnHidden(column)) {
                               QString data = ui->tab_reclamation->model()->data(ui->tab_reclamation->model()->index(row, column)).toString().simplified();
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


  //  QTextDocument document;
   // document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("reclamation.pdf");
    document->print(&printer);
}

