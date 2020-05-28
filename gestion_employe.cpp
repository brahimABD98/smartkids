#include "gestion_employe.h"
#include "ui_gestion_employe.h"
#include "staff_technique.h"
#include "instituteur.h"
#include "salles.h"
#include "compte.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QTextStream>
#include <QComboBox>
#include <QTabWidget>
#include <QObject>
#include <QSqlTableModel>
#include <QString>
#include "charrad/gestiono9.h"
#include "gestion.h"
#include "equipement.h"
#include "aliment.h"
gestion_employe::gestion_employe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_employe)
{
    ui->setupUi(this);
ui->tableView->setModel(tmpinstituteur.afficher_instituteur());
ui->tablestaff_technique->setModel(tmpstaff_technique.afficher_staff_technique());
ui->tableView_2->setModel(tmpcompte.afficher_compte());
}

gestion_employe::~gestion_employe()
{
    delete ui;
}
void gestion_employe::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestion_employe::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestion_employe::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void gestion_employe::on_pushButton_22_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void gestion_employe::on_pushButton_23_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void gestion_employe::on_pushButton_24_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}

void gestion_employe::on_pushButton_29_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void gestion_employe::on_pushButton_28_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}
void gestion_employe::on_pushButton_9_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(2);
}
void gestion_employe::on_pushButton_26_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void gestion_employe::on_pushButton_30_clicked()
{
     ui->stackedWidget_4->setCurrentIndex(1);
}
void gestion_employe::on_pushButton_31_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}


void gestion_employe::on_pushButton_ajtinst_2_clicked()
{
    int id = ui->lineEdit_23->text().toUInt();
    QString nom= ui->lineEdit_24->text();
    QString prenom= ui->lineEdit_28->text();
    QString diplome= ui->lineEdit_25->text();
   float salaire= ui->lineEdit_26->text().toFloat();
    int exprience= ui->lineEdit_27->text().toUInt();
    QString niveau= ui->lineEdit_29->text();
  instituteur i(id,nom,prenom,diplome,salaire,exprience,niveau);
  bool test=i.ajouter();
  if(test)
{ui->tableView->setModel( tmpinstituteur.afficher());;//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un instituteur"),
                  QObject::tr("instituteur ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un instituteur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}


void gestion_employe::on_pushButton_sup_ins_clicked()
{
int idd = ui->lineEdit_40->text().toInt();
bool test=tmpinstituteur.supprimer(idd);
if(test)
{ui->tableView->setModel(tmpinstituteur.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un instituteur"),
                QObject::tr("instituteur supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un staff technique"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}


void gestion_employe::on_pushButton_modi_ins_clicked()
{
    int id = ui->lineEdit_35->text().toUInt();
    QString nom = ui->lineEdit_37->text();
    QString prenom= ui->lineEdit_33->text();
    QString diplome= ui->lineEdit_34->text();
    float salaire= ui->lineEdit_36->text().toFloat();
    int exprience = ui->lineEdit_45->text().toInt();
    QString niveau= ui->lineEdit_46->text();
    instituteur i ;
    bool atout=i.modifier(id,nom,prenom,diplome,salaire,exprience,niveau);
    if(atout)
    {ui->tableView->setModel(tmpinstituteur.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier un instituteur "),
                                 QObject::tr("instituteur  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un instituteur "),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

 }
    void gestion_employe::on_lineEdit_textChanged()
    {
        if(ui->lineEdit->text() == "")
            {
                ui->tableView->setModel(tmpinstituteur.afficher());
            }
            else
            {
                 ui->tableView->setModel(tmpinstituteur.rechercher(ui->lineEdit->text()));
            }




    }
    void gestion_employe::on_pushButton_tric_clicked()
    {
       ui->tableView->setModel(tmpinstituteur.trie(0));
    }

    void gestion_employe::on_pushButton_8_clicked()
    {
         ui->tableView->setModel(tmpinstituteur.trie(1));
    }


    void gestion_employe::on_lineEdit_35_textChanged()
    {
        int id=ui->lineEdit_35->text().toInt();

        QSqlQuery query=tmpinstituteur.rechercher_id(id);
        QString nom,prenom,diplome;
        QString salaire,exprience,niveau;


             if (query.next())
            {

            nom= query.value(1).toString();
            ui->lineEdit_37->setText(nom);
            prenom= query.value(2).toString();
            ui->lineEdit_33->setText(prenom);
            diplome= query.value(3).toString();
            ui->lineEdit_34->setText(diplome);
            salaire= query.value(4).toString();
            ui->lineEdit_36->setText(salaire);
            exprience= query.value(5).toString();
            ui->lineEdit_45->setText(exprience);
            niveau= query.value(6).toString();
            ui->lineEdit_46->setText(niveau);

            }
    }
    void gestion_employe::on_tableView_doubleClicked(const QModelIndex &index)
    {
        if ((index.isValid()) && (index.column() == 0)  ) {

            QString type;
            QString nbr;
            QString num;
            int id = index.data().toInt();
            QSqlQuery query=tmpsalles.rechercher_num(id);
            if (query.next()) {
            num=query.value(0).toString();
            type= query.value(1).toString();
            nbr= query.value(2).toString();
            }


            QMessageBox::information(nullptr, QObject::tr("Salle"),
                              QObject::tr(" Numero de la salle : %0 \n Type : %1 \n Nbr de places: %3 ").arg(num) .arg(type).arg(nbr), QMessageBox::Cancel);

        }
     }
/*------------------------------------------------------------------------*/


void gestion_employe::on_pushButton_clicked()
{
    int id = ui->lineEdit_38->text().toUInt();
    QString nom= ui->lineEdit_39->text();
    QString prenom= ui->lineEdit_41->text();
   float salaire= ui->lineEdit_47->text().toFloat();
    QString spcialite= ui->lineEdit_48->text();
  staff_technique s(id,nom,prenom,salaire,spcialite);
  bool test=s.ajouter();
  if(test)
{ui->tablestaff_technique->setModel(tmpstaff_technique.afficher());;//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un staff technique"),
                  QObject::tr("staff_technique ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un staff technique"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}



void gestion_employe::on_pushButton_sup_4_clicked()
{
int idd = ui->lineEdit_49->text().toInt();
bool test=tmpstaff_technique.supprimer(idd);
if(test)
{ui->tablestaff_technique->setModel(tmpstaff_technique.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un staff techniquet"),
                QObject::tr("staff technique supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un staff technique"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void gestion_employe::on_pushButton_4_clicked()
{
    int id = ui->lineEdit_44->text().toUInt();
    QString nom = ui->lineEdit_43->text();
    QString prenom= ui->lineEdit_42->text();
    float salaire= ui->lineEdit_50->text().toFloat();
    QString spcialite = ui->lineEdit_51->text();
    staff_technique s ;
    bool atout=s.modifier(id,nom,prenom,salaire,spcialite);
    if(atout)
    {ui->tablestaff_technique->setModel(tmpstaff_technique.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier un staff technique"),
                                 QObject::tr("staff technique modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un staff technique"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_employe::on_lineEdit_2_textChanged()
{
    if(ui->lineEdit_2->text() == "")
        {
            ui->tablestaff_technique->setModel(tmpstaff_technique.afficher());
        }
        else
        {
             ui->tablestaff_technique->setModel(tmpstaff_technique.rechercher(ui->lineEdit_2->text()));
        }
}

void gestion_employe::on_pushButton_6_clicked()
{
   ui->tablestaff_technique->setModel(tmpstaff_technique.trie(0));
}

void gestion_employe::on_pushButton_7_clicked()
{
     ui->tablestaff_technique->setModel(tmpstaff_technique.trie(1));
}



void gestion_employe::on_lineEdit_44_textChanged()
{
    int id=ui->lineEdit_44->text().toInt();

    QSqlQuery query=tmpstaff_technique.rechercher_id(id);
    QString nom,prenom,spcialite;
    QString salaire;


         if (query.next())
        {

        nom= query.value(1).toString();
        ui->lineEdit_43->setText(nom);
        prenom= query.value(2).toString();
        ui->lineEdit_42->setText(prenom);
        salaire= query.value(3).toString();
        ui->lineEdit_50->setText(salaire);
        spcialite= query.value(4).toString();
        ui->lineEdit_51->setText(spcialite);


        }
}

void gestion_employe::on_tablestaff_technique_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 0)  ) {

        QString nom;
        QString qt;
        QString idd;
        int id = index.data().toInt();
        QSqlQuery query=tmpequipement.rechercher_num(id);
        if (query.next()) {
        idd = query.value(0).toString();
        nom= query.value(1).toString();
        qt= query.value(2).toString();
        }


        QMessageBox::information(nullptr, QObject::tr("equipement"),
                          QObject::tr(" id : %0 \n  Nom de produit : %1 \n Quantite : %2  ") .arg(idd) .arg(nom) .arg(qt), QMessageBox::Cancel);

    }
 }

/*------------------------------------------------------------------------*/



void gestion_employe::on_pushButton_ajtcomp_clicked()
{
     int id = ui->lineEdit_4->text().toUInt();
    QString username= ui->lineEdit_53->text();
    int password= ui->lineEdit_54->text().toUInt();

  compte c(id,username,password);
  bool test=c.ajouter();
  if(test)
{ui->tableView_2->setModel(tmpcompte.afficher());;//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un staff technique"),
                  QObject::tr("staff_technique ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un staff technique"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void gestion_employe::on_pushButton_modcomp_clicked()
{
    int id = ui->lineEdit_59->text().toUInt();
    QString username = ui->lineEdit_58->text();
    int password= ui->lineEdit_57->text().toInt();

    compte c ;
    bool atout=c.modifier(id,username,password);
    if(atout)
    {ui->tableView_2->setModel(tmpcompte.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier un staff technique"),
                                 QObject::tr("staff technique modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un staff technique"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_employe::on_pushButton_sup_5_clicked()
{
int idd = ui->lineEdit_62->text().toInt();
bool test=tmpcompte.supprimer(idd);
if(test)
{ui->tableView_2->setModel(tmpcompte.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un staff techniquet"),
                QObject::tr("staff technique supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un staff technique"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}



void gestion_employe::on_lineEdit_3_textChanged()
{
    if(ui->lineEdit_3->text() == "")
        {
            ui->tableView_2->setModel(tmpcompte.afficher());
        }
        else
        {
             ui->tableView_2->setModel(tmpcompte.rechercher(ui->lineEdit_3->text()));
        }




}

void gestion_employe::on_pushButton_27_clicked()
{
    hide();
 gestion_employe g;
 g.exec();
}

void gestion_employe::on_pushButton_17_clicked()
{
    hide();
    gestiono9 G;
    G.exec();
}

void gestion_employe::on_pushButton_eleves_2_clicked()
{
    hide();
    Gestion g;
    g.exec();
}








void gestion_employe::on_lineEdit_59_textChanged()
{
    int id=ui->lineEdit_59->text().toInt();

    QSqlQuery query=tmpcompte.rechercher_id(id);
    QString username,password;



         if (query.next())
        {

        username= query.value(1).toString();
        ui->lineEdit_58->setText(username);
        password= query.value(2).toString();
        ui->lineEdit_57->setText(password);



        }
}

void gestion_employe::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    if ((index.isValid()) && (index.column() == 0)  ) {

        QString nom;
        QString prenom;
        QString diplome;
        int id = index.data().toInt();
        QSqlQuery query=tmpinstituteur.rechercher_id(id);
        if (query.next()) {
        nom=query.value(1).toString();
        prenom= query.value(2).toString();
        diplome= query.value(3).toString();
        }


        QMessageBox::information(nullptr, QObject::tr("instituteur"),
                          QObject::tr(" nom : %1 \n prenom : %2 \n diplome: %3 ").arg(nom) .arg(prenom).arg(diplome), QMessageBox::Cancel);

    }
 }
