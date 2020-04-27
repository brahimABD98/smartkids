#ifndef GESTIONC_H
#define GESTIONC_H

#include <QDialog>
#include "deponse.h"
#include "revenu.h"
#include <QMessageBox>
#include "QSystemTrayIcon"

namespace Ui {
class gestionc;
}

class gestionc : public QDialog
{
    Q_OBJECT

public:
    explicit gestionc(QWidget *parent = nullptr);
    ~gestionc();

private:
    Ui::gestionc *ui;
    deponse d0;
    revenu r0;
    QSystemTrayIcon *notifyicon;
};

#endif // GESTIONC_H
