#include "gestionc.h"
#include "ui_gestionc.h"

gestionc::gestionc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionc)
{
    ui->setupUi(this);
    notifyicon=new QSystemTrayIcon(this);
    notifyicon->setIcon(QIcon(":/icon/Notification.jpg"));
     ui->tableView->setModel(d0.afficher());
     ui->tableView_2->setModel(r0.afficher());
}

gestionc::~gestionc()
{
    delete ui;
}
