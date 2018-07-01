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

void menureader::on_pushButton_38_clicked() //借閱書籍
{
    static QString ISBN;
    ISBN = ui->lineEdit_32->text();

    static Book* WanttoBorrow;
    WanttoBorrow = db.Find_Book_ISBN(ISBN);

    if (WanttoBorrow != nullptr)
    {
        if (WanttoBorrow->AvailableTotal() == 0)
            QMessageBox::information(NULL,"Failed","当前图书已皆被借出，借阅失败。");
        else if (NowUser->CanBorrow() == 0)
            QMessageBox::information(NULL,"Failed","您当前借阅书籍数量已达到最大借阅数，借阅失败。");
        else
        {
            db.Add_Apply("BORROW", NowUser, WanttoBorrow);
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
        if (db.Check_Borrow(NowUser, WanttoReturn) == false)
            QMessageBox::information(NULL,"Failed","您并未借阅该图书，归还失败。");
        else
        {
            db.Add_Apply("RETURN", NowUser, WanttoReturn);
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
    ui->tableWidget->clearContents();
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

void menureader::on_pushButton_42_clicked()
{
    static vector<Record*> RecordList;
    RecordList.clear();

    db.Search_Record(RecordList, NowUser->GetID(), 0, 0);
    ui->tableWidget_2->clearContents();
    for(int i=0; i<(int)RecordList.size(); i++)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(db.Find_Book_ID(RecordList[i]->GetBookID())->GetName()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::fromStdString(RecordList[i]->GetType())));
    }

    RecordList.clear();

    db.Search_Apply(RecordList, NowUser->GetID(), 0, 0);
    ui->tableWidget_3->clearContents();
    for(int i=0; i<(int)RecordList.size(); i++)
    {
        ui->tableWidget_3->setItem(i,0,new QTableWidgetItem(db.Find_Book_ID(RecordList[i]->GetBookID())->GetName()));
        ui->tableWidget_3->setItem(i,1,new QTableWidgetItem(QString::fromStdString(RecordList[i]->GetType())));
    }
}
