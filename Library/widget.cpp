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
#include "Apply.h"
#include "Record.h"
#include "Database.h"


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
//QMessageBox::information(NULL, "error", "打不开root文件.");
    User* user;
    emit isignal(user);
    if(ui->radioButton->isChecked())
    {
      // if ((user = db.Find_User_Name(ui->lineEdit->text())) != NULL && user->CheckPassword(ui->lineEdit_2->text()))
      //  {
        menureader* m_reader = new menureader();
        m_reader->show();
        this->hide();
      //  }
      //  else{
      //      QMessageBox::information(NULL,"ERROR","密碼錯誤");
      //  }
    }
    else if(ui->radioButton_2->isChecked())
    {
      //  if ((user = db.Find_User_Name(ui->lineEdit->text())) != NULL && user->CheckPassword(ui->lineEdit_2->text()))
      //  {
         menuadmin* ma = new menuadmin();
         ma->show();
         this->hide();
       // }
      //  else{
      //      QMessageBox::information(NULL,"ERROR","密碼錯誤");
      //  }
    }
    //請選擇登入類型
    else {}

}
