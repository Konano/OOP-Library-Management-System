#include "menureader.h"
#include "ui_menureader.h"
#include "widget.h"

extern Database db;
extern User* NowUser;

menureader::menureader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menureader)
{
    ui->setupUi(this);
}

menureader::~menureader()
{
    delete ui;
}

void menureader::getsignal(User* us)
{
    user=us;
}

void menureader::on_pushButton_38_clicked() //借閱書籍
{
    static Book* WanttoBorrow;
    Widget* widget = new Widget();
    connect(widget,SIGNAL(isignal(User*)),this,SLOT(getsignal(User*)));
    static QString ISBN=ui->lineEdit_32->text();
    WanttoBorrow = db.Find_Book_ISBN(ISBN);
    if (WanttoBorrow != 0) {
        if (WanttoBorrow->AvailableTotal() == 0)
            QMessageBox::information(NULL,"Failed","当前图书已皆被借出，借阅失败。");
        else if (user->CanBorrow() == 0)
            QMessageBox::information(NULL,"Failed","您当前借阅书籍数量已达到最大借阅数，借阅失败。");
        else
        {
            db.Add_Apply_Borrow(user, WanttoBorrow);
            QMessageBox::information(NULL,"Success","提交借阅申请成功！");
        }
    }
    else
        QMessageBox::information(NULL,"Failed","找不到对应的图书");
}

void menureader::on_pushButton_37_clicked() //歸還書籍
{
    static QString ISBN;
    ISBN = ui->lineEdit_31->text();
    static Book* WanttoReturn;
    WanttoReturn = db.Find_Book_ISBN(ISBN);
    if (WanttoReturn != nullptr)
    {
        if (db.Check_Borrow(user, WanttoReturn))
            QMessageBox::information(NULL,"Failed","您并未借阅该图书，归还失败。");
        else
        {
            db.Add_Apply_Return(user, WanttoReturn);
            QMessageBox::information(NULL,"Success","提交归还申请成功！");
        }
    }
    else
        QMessageBox::information(NULL,"Failed","找不到对应的图书");
}

void menureader::on_pushButton_36_clicked() //查找書籍
{
    static QString name, writer, ISBN, publisher;
    name = ui->lineEdit_26->text();
    writer = ui->lineEdit_27->text();
    ISBN = ui->lineEdit_29->text();
    publisher = ui->lineEdit_28->text();

    // 初始化 BookList
    static vector<Book*> BookList;
    BookList.clear();

    db.Search_Book(BookList, name, writer, publisher, ISBN, 0);
    ui->tableWidget->clear();
    for(int i=0; i<(int)BookList.size(); i++)
    {
        QString avanumb=QString::number(BookList[i]->AvailableTotal());
        QString lentnum=QString::number(BookList[i]->LentTotal());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(BookList[i]->GetName()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(BookList[i]->GetWriter()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(BookList[i]->GetPublisher()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(BookList[i]->GetISBN()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(lentnum + " / " + avanumb));
    }
}
