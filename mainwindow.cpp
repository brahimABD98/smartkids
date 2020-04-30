#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestion.h"
#include "ui_gestion.h"
#include "charrad/gestiono9.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString username;
    QString password;
    username=ui->lineEdit->text();
    password=ui->lineEdit_2->text();
    QSqlQuery qry;
    if(qry.exec( "select * from compte where username='"+username +"' and password='"+password +"'"))
      {
        int count=0;
    while(qry.next())
       {
        count++;
        }
    if(count==1)
    {
        hide();
        Gestion G;
        G.exec();
    }
    if(count<1)
    {
        QMessageBox::critical(nullptr, QObject::tr("password incorrect"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        /*  ui->label-setText("false")*/
    }
    }
}
