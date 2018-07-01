#ifndef MENUADMIN_H
#define MENUADMIN_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QMessageBox>
#include "database.h"
#include "book.h"


namespace Ui {
class menuadmin;
}

class menuadmin : public QWidget
{
    Q_OBJECT

public:
    explicit menuadmin(QWidget *parent = 0);
    ~menuadmin();

private slots:
    void on_pushButton_27_clicked();
    // void on_pushButton_28_clicked();
    // void on_pushButton_29_clicked();
    // void on_pushButton_32_clicked();
    // void on_pushButton_30_clicked();
    // void on_pushButton_31_clicked();
    // void on_pushButton_33_clicked();
    // void on_pushButton_34_clicked();
    // void on_pushButton_35_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_41_clicked();
    void on_pushButton_42_clicked();

    void tableWidget_4_update();




private:
    Ui::menuadmin *ui;
    QPalette pal;
};

#endif // MENUADMIN_H
