#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QPoint>
#include <QMouseEvent>
#include <QMessageBox>

#include <menuadmin.h>
#include <menureader.h>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include "main.h"
#include "Book.h"
#include "User.h"
#include "Reader.h"
#include "Admin.h"
#include "Apply.h"
#include "Record.h"
#include "Database.h"



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
   // void reshow();
    //void updateTime();
signals:
    void isignal(User*);

private:
    Ui::Widget *ui;
    QPalette pal;
};

#endif // WIDGET_H
