#include "widget.h"
#include "ui_widget.h"
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
#include "Record.h"
#include "Database.h"

extern Database db;
extern User* NowUser;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        if ((NowUser = db.Find_User_Name(ui->lineEdit->text())) != NULL && NowUser->CheckPassword(ui->lineEdit_2->text()))
        {
            menureader* m_reader = new menureader();
            m_reader->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(NULL,"ERROR","密碼錯誤");
        }
    }
    else if(ui->radioButton_2->isChecked())
    {
        if ((NowUser = db.Find_User_Name(ui->lineEdit->text())) != NULL && NowUser->CheckPassword(ui->lineEdit_2->text()) && NowUser->isAdmin())
        {
            menuadmin* ma = new menuadmin();
            ma->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(NULL,"ERROR","密碼錯誤");
        }
    }
}
