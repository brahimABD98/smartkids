#include "gestiono9.h"
#include "ui_gestiono9.h"
#include "deponse.h"
#include <QTextDocument>
#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include "gestion.h"
#include "stock.h"
#include "gestion_activite.h"
#include "gestion_employe.h"


gestiono9::gestiono9(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestiono9)
{
    ui->setupUi(this);
    notifyicon=new QSystemTrayIcon(this);
    notifyicon->setIcon(QIcon(":/icon/Notification.jpg"));
     ui->tableView->setModel(d0.afficher());
     ui->tableView_2->setModel(r0.afficher());
     ui->stackedWidget_2->setCurrentIndex(0);

}

gestiono9::~gestiono9()
{
    delete ui;
}


void gestiono9::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestiono9::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestiono9::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void gestiono9::on_pushButton_22_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);
}

void gestiono9::on_pushButton_23_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(1);
}

void gestiono9::on_pushButton_24_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(2);
}


void gestiono9::on_commandLinkButton_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void gestiono9::on_commandLinkButton_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

}

void gestiono9::on_pushButton_21_clicked()
{
   ui->stackedWidget->setCurrentIndex(3);
    }
void gestiono9::on_pushButton_25_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(3);

}



void gestiono9::on_pushButton_clicked() //ajout
{ //int id = ui->lineEdit_23->text().toInt();
    QSqlQuery query;
    QVector <int> tab;
    int i;
    int aux;
        int id=-1;

        if(query.exec("select idd from  deponse"))
            {
                while (query.next())
                {
                    tab.push_back(query.value(0).toInt());

                }

            }
            qSort(tab.begin(),tab.end());

            if(tab.size()==0)
            {
                id=1;
            }
            else if(tab[0]!=1)
            { id=1;}
            else if(tab.size()==1)
            {
                id=2;
            }

            else
            {for(i=1;i<tab.size();i++)
            {

                if (tab[i]-tab[i-1]>1)
                {
                    id=tab[i-1]+1;
                    break;
                }
            }
            }
            if (id==-1)
            {
                id=tab.size()+1;
            }
        int mont = ui->lineEdit_24->text().toInt();
        QString type;
        QString date =  ui->dateEdit->text();
        if(ui->radioButton->isChecked())
        {

            type = "stock";
        }
        else if(ui->radioButton_2->isChecked())
        {
            type = "salair";
        }
        else
        {
            type = "autres";
        }

        deponse D(id,type,date,mont);
        if(D.ajouter())
        {
            notifyicon->show();
                       notifyicon->showMessage("Success","Ajout avec succes",QSystemTrayIcon::Critical,2000);
            QMessageBox::information(nullptr, QObject::tr("Deponse"),
                        QObject::tr("Deponse ajouté.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(d0.afficher());
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("Deponse"),
                        QObject::tr("erreur.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void gestiono9::on_pushButton_4_clicked() // modifier
{
    int id= ui->lineEdit_28->text().toInt();
           int montant= ui->lineEdit_27->text().toInt();
           QString date=ui->dateEdit_3->text();
           QString type ;
           if(ui->radioButton_6->isChecked())
           {
               type = "stock";
           }
           else if(ui->radioButton_4->isChecked())
           {
               type = "autres";
           }
           else
           {
               type = "salair";
           }
           deponse D(id,type,date,montant);
           D.modifier(id);

           ui->tableView->setModel(d0.afficher());

}

void gestiono9::on_pushButton_6_clicked() //supp
{
    int id = ui->lineEdit_40->text().toInt();
        if(d0.supprimer(id))
        {
            QMessageBox::information(nullptr, QObject::tr("Deponse"),
                        QObject::tr("voulez vous supprimer.\n"
                                    "Click yes."), QMessageBox::Yes);
            QMessageBox::information(nullptr, QObject::tr("Deponse"),
                        QObject::tr("Deponse supprimer.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(d0.afficher());
        }
}

void gestiono9::on_lineEdit_textChanged(const QString &arg1) //recherche
{
    QString id = ui->lineEdit->text();


       if(ui->lineEdit->text() == "")
       {
           ui->tableView->setModel(d0.afficher());
       }
       else
       {
           ui->tableView->setModel(d0.recherche(id));
       }
}

void gestiono9::on_pushButton_7_clicked() //trier
{
    ui->tableView->setModel(d0.afficherTrier());

}


void gestiono9::on_lineEdit_28_textChanged(const QString &arg1)
{
   // int id=ui->lineEdit_28->text().toInt();
     QString id=ui->lineEdit_28->text();
     deponse dx;
     dx.rechercher_id(id);

         //   QSqlQuery query=d0.rechercher_id(id);
           // QString type,date;
            //int montant;



               // montant= query.value(1).toInt();
                ui->lineEdit_27->setText(QString::number(dx.get_montant()));
              //  type= query.value(2).toString();
                if(dx.get_type() =="stock")
                {
                   // ui->radioButton_6->isChecked();
                    ui->radioButton_6->setChecked(true);
                    ui->radioButton_4->setChecked(false);
                    ui->radioButton_5->setChecked(false);
                }

                else if(dx.get_type() =="autres")
                {

                           // ui->radioButton_4->isChecked();
                    ui->radioButton_4->setChecked(true);
                    ui->radioButton_5->setChecked(false);
                    ui->radioButton_6->setChecked(false);

                }
                else
                {
                   // ui->radioButton_5->isChecked();
                    ui->radioButton_5->setChecked(true);
                    ui->radioButton_4->setChecked(false);
                    ui->radioButton_6->setChecked(false);

                }
                ui->dateEdit_3->setDate(dx.datearbi);
                qDebug()<<dx.datearbi;


                // else{ui->lineEdit_28->clear();}
}

void gestiono9::on_pushButton_9_clicked()
{
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView->model()->rowCount();
                   const int columnCount =ui->tableView->model()->columnCount();

                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("depenses")
                           <<  "</head>\n"
                           "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                               "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                               "<h1>Liste des Depenses</h1>"



                               "<table border=1 cellspacing=0 cellpadding=2>\n";


                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView->isColumnHidden(column)) {
                                      QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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
               printer.setOutputFileName("depenses.pdf");
               document->print(&printer);
}


void gestiono9::on_pushButton_10_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView->model()->rowCount();
                const int columnCount =ui->tableView->model()->columnCount();

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
                        if (!ui->tableView->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView->isColumnHidden(column)) {
                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

/*************************revenu*****************************/







void gestiono9::on_pushButton_36_clicked()
{
    QSqlQuery query;
    QVector <int> tab;
    int i;
    int aux;
        int id=-1;

        if(query.exec("select idd from  revenu"))
            {
                while (query.next())
                {
                    tab.push_back(query.value(0).toInt());

                }

            }
            qSort(tab.begin(),tab.end());

            if(tab.size()==0)
            {
                id=1;
            }
            else if(tab[0]!=1)
            { id=1;}
            else if(tab.size()==1)
            {
                id=2;
            }

            else
            {for(i=1;i<tab.size();i++)
            {

                if (tab[i]-tab[i-1]>1)
                {
                    id=tab[i-1]+1;
                    break;
                }
            }
            }
            if (id==-1)
            {
                id=tab.size()+1;
            }
        int montant = ui->lineEdit_30->text().toInt();
        QString type;
        QString date =  ui->dateEdit_5->text();
        if(ui->radioButton_20->isChecked())
        {
            type = "Eleve";
        }

        else
        {
            type = "Evenement";
        }
        revenu R(id,type,date,montant);
        if(R.ajouter())
        {
            QMessageBox::information(nullptr, QObject::tr("Revenu"),
                        QObject::tr("Revenu ajouté.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_2->setModel(r0.afficher());
        notifyicon->show();
                   notifyicon->showMessage("Success","Ajout avec succes",QSystemTrayIcon::Critical,2000);
    ui->tableView->setModel(d0.afficher());
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("revenu"),
                        QObject::tr("erreur.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


}




void gestiono9::on_pushButton_39_clicked()
{
    int id= ui->lineEdit_35->text().toInt();
        int montant= ui->lineEdit_36->text().toInt();
        QString date=ui->dateEdit_9->text();
        QString type ;
        if(ui->radioButton_28->isChecked())
        {
            type = "Eleve";
        }

        else
        {
            type = "Evenement";
        }
        revenu R(id,type,date,montant);
        R.modifier(id);
        ui->tableView_2->setModel(r0.afficher());
}



void gestiono9::on_pushButton_41_clicked()
{
    int id = ui->lineEdit_56->text().toInt();
        if(r0.supprimer(id))
        {
            QMessageBox::information(nullptr, QObject::tr("Revenu"),
                        QObject::tr("voulez vous supprimer.\n"
                                    "Click yes."), QMessageBox::Yes);
            QMessageBox::information(nullptr, QObject::tr("Revenu"),
                        QObject::tr("Revenu supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            ui->tableView_2->setModel(r0.afficher());
        }
}




void gestiono9::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString id = ui->lineEdit_2->text();


        if(ui->lineEdit_2->text() == "")
        {
            ui->tableView_2->setModel(r0.afficher());
        }
        else
        {
            ui->tableView_2->setModel(r0.recherche(id));
        }

}



void gestiono9::on_pushButton_8_clicked()
{
    ui->tableView_2->setModel(r0.afficherTrier());

}






void gestiono9::on_pushButton_11_clicked()
{
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView->model()->rowCount();
                   const int columnCount =ui->tableView->model()->columnCount();

                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("depenses")
                           <<  "</head>\n"
                           "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                               "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                               "<h1>Liste des Depenses</h1>"



                               "<table border=1 cellspacing=0 cellpadding=2>\n";


                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView->isColumnHidden(column)) {
                                      QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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
               printer.setOutputFileName("depenses.pdf");
               document->print(&printer);
}

void gestiono9::on_pushButton_13_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView_2->model()->rowCount();
                const int columnCount =ui->tableView_2->model()->columnCount();

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
                        if (!ui->tableView_2->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_2->isColumnHidden(column)) {
                                   QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
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


void gestiono9::on_pushButton_15_clicked()//gestion
{
    hide();
       gestion_activite ga;
       ga.exec();
}



void gestiono9::on_pushButton_16_clicked()
{
    hide();
       gestion_employe g;
       g.exec();
}

void gestiono9::on_pushButton_28_clicked()
{
    hide();
    Gestion g;
    g.exec();
}

void gestiono9::on_pushButton_eleves_3_clicked()
{
    hide();
    Gestion g;
    g.exec();
}



void gestiono9::on_pushButton_12_clicked()
{
    hide();
       stock s;
       s.exec();
}

void gestiono9::on_lineEdit_35_textChanged(const QString &arg1)
{
    QString id=ui->lineEdit_28->text();
    deponse dx;
    dx.rechercher_id(id);

        //   QSqlQuery query=d0.rechercher_id(id);
          // QString type,date;
           //int montant;



              // montant= query.value(1).toInt();
               ui->lineEdit_36->setText(QString::number(dx.get_montant()));
             //  type= query.value(2).toString();
               if(dx.get_type() =="stock")
               {
                  // ui->radioButton_6->isChecked();
                   ui->radioButton_28->setChecked(true);
                   //ui->radioButton_4->setChecked(false);

               }


               else
               {
                  // ui->radioButton_5->isChecked();
                   ui->radioButton_27->setChecked(true);


               }
               //ui->dateEdit_3->setDate(dx.datearbi);
               qDebug()<<dx.datearbi;
}

void gestiono9::on_pushButton_26_charrad_stat_clicked()
{

    ui->stackedWidget_2->setCurrentIndex(2);
    ui->tableView_charrad_stat->setModel(s0.____());
}
