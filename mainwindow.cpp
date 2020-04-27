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
    hide();
    Gestion G;
    G.exec();
}
