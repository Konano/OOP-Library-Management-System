#include "menuadmin.h"
#include "ui_menuadmin.h"

extern Database db;
extern User* NowUser;

menuadmin::menuadmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuadmin)
{
    ui->setupUi(this);
}

menuadmin::~menuadmin()
{
    delete ui;
}

void menuadmin::on_pushButton_41_clicked() //查找書籍
{
    static QString name, writer, ISBN, publisher;
    name = ui->lineEdit_30->text();
    writer = ui->lineEdit_34->text();
    ISBN = ui->lineEdit_36->text();
    publisher = ui->lineEdit_35->text();

    // 初始化 BookList
    static vector<Book*> BookList;
    BookList.clear();

    db.Search_Book(BookList, name, writer, publisher, ISBN, 0);
    ui->tableWidget->clear();
    for(int i=0; i<(int)BookList.size(); i++)
    {
        QString id=QString::number(BookList[i]->GetID());
        QString avanumb=QString::number(BookList[i]->AvailableTotal());
        QString lentnum=QString::number(BookList[i]->LentTotal());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(id));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(BookList[i]->GetName()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(BookList[i]->GetWriter()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(BookList[i]->GetPublisher()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(BookList[i]->GetISBN()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(lentnum + " / " + avanumb));
    }
}

void menuadmin::tableWidget_4_update()
{
    static vector<Record*> RecordList;
    RecordList.clear();

    db.Search_Apply(RecordList, 0, 0, 0);
    ui->tableWidget_4->clearContents();
    for(int i=0; i<(int)RecordList.size(); i++)
    {
        cout << db.Find_User_ID(RecordList[i]->GetReaderID()) << endl;
        ui->tableWidget_4->setItem(i,0,new QTableWidgetItem(db.Find_User_ID(RecordList[i]->GetReaderID())->GetName()));
        ui->tableWidget_4->setItem(i,1,new QTableWidgetItem(db.Find_Book_ID(RecordList[i]->GetBookID())->GetName()));
        ui->tableWidget_4->setItem(i,2,new QTableWidgetItem(QString::fromStdString(RecordList[i]->GetType())));
    }
}

void menuadmin::on_pushButton_42_clicked()
{
    tableWidget_4_update();
}

void menuadmin::on_pushButton_37_clicked()
{
    int pid = ui->lineEdit_27->text().toInt() - 1;
    if (pid < 0 || pid >= db.GetApplyTotal())
    {
        QMessageBox::information(NULL,"Fail","PID 非法。");
        return;
    }
    db.Apply_Accept(pid);
    tableWidget_4_update();
}

void menuadmin::on_pushButton_38_clicked()
{
    int pid = ui->lineEdit_27->text().toInt() - 1;
    if (pid < 0 || pid >= db.GetApplyTotal())
    {
        QMessageBox::information(NULL,"Fail","PID 非法。");
        return;
    }
    db.Apply_Reject(pid);
    tableWidget_4_update();
}

void menuadmin::on_pushButton_35_clicked()
{
    int type = 0;
    if (ui->radioButton->isChecked()) type = 1;
    if (ui->radioButton_2->isChecked()) type = 2;
    int readerID = ui->lineEdit_23->text().toInt();
    int bookID = ui->lineEdit_24->text().toInt();

    static vector<Record*> RecordList;
    RecordList.clear();

    db.Search_Record(RecordList, readerID, bookID, type);
    ui->tableWidget_3->clearContents();
    for(int i=0; i<(int)RecordList.size(); i++)
    {
        cout << db.Find_User_ID(RecordList[i]->GetReaderID()) << endl;
        ui->tableWidget_3->setItem(i,0,new QTableWidgetItem(db.Find_User_ID(RecordList[i]->GetReaderID())->GetName()));
        ui->tableWidget_3->setItem(i,1,new QTableWidgetItem(db.Find_Book_ID(RecordList[i]->GetBookID())->GetName()));
        ui->tableWidget_3->setItem(i,2,new QTableWidgetItem(QString::fromStdString(RecordList[i]->GetType())));
    }
}

static Reader* rd_modify_id = nullptr;

void menuadmin::on_pushButton_30_clicked()
{
    Reader* rd = dynamic_cast<Reader*>(db.Find_User_ID(ui->lineEdit_20->text().toInt()));
    if (rd)
    {
        ui->lineEdit_21->setText(rd->GetName());
        ui->lineEdit_28->setText("");
        ui->lineEdit_29->setText(QString::number(rd->MaxBorrow()));
        rd_modify_id = rd;
    }
    else
        QMessageBox::information(NULL,"Fail","找不到匹配的读者。");
}

void menuadmin::on_pushButton_36_clicked()
{
    if (rd_modify_id == nullptr)
    {
        QMessageBox::information(NULL,"Fail","需要先输入想修改的读者的 ID 并按下「查找」。");
        return;
    }

    static QString name, pwd; static int max_borrow;
    name = ui->lineEdit_21->text();
    pwd = ui->lineEdit_28->text();
    max_borrow = ui->lineEdit_29->text().toInt();

    if (name == "" || pwd == "" || max_borrow == 0)
        QMessageBox::information(NULL,"Fail","信息不准确。修改失败。");
    else
    {
        rd_modify_id->Modify(name, pwd, max_borrow);
        QMessageBox::information(NULL,"Success","修改成功");
    }
}

void menuadmin::on_pushButton_34_clicked()
{
    static QString name, pwd; static int max_borrow;
    name = ui->lineEdit_21->text();
    pwd = ui->lineEdit_28->text();
    max_borrow = ui->lineEdit_29->text().toInt();

    if (name == "" || pwd == "" || max_borrow == 0)
        QMessageBox::information(NULL,"Fail","信息不准确。添加失败。");
    else
    {
        db.Add_Reader(name, pwd, max_borrow);
        QMessageBox::information(NULL,"Success","添加成功");
    }
}

void menuadmin::on_pushButton_33_clicked()
{
    User* us = db.Find_User_ID(ui->lineEdit_20->text().toInt());
    if (us)
    {
        db.Delete_User(us->GetID());
        QMessageBox::information(NULL,"Success","删除成功");
    }
    else
        QMessageBox::information(NULL,"Fail","找不到匹配的读者。");
}




static Book* bk_modify_id = nullptr;

void menuadmin::on_pushButton_39_clicked()
{
    Book* bk = db.Find_Book_ID(ui->lineEdit_12->text().toInt());
    if (bk)
    {
        ui->lineEdit_14->setText(bk->GetName());
        ui->lineEdit_26->setText(bk->GetWriter());
        ui->lineEdit_31->setText(bk->GetPublisher());
        ui->lineEdit_32->setText(bk->GetISBN());
        ui->lineEdit_33->setText(QString::number(bk->LentTotal()+bk->AvailableTotal()));
        bk_modify_id = bk;
    }
    else
        QMessageBox::information(NULL,"Fail","找不到匹配的书籍。");
}

void menuadmin::on_pushButton_40_clicked()
{
    if (bk_modify_id == nullptr)
    {
        QMessageBox::information(NULL,"Fail","需要先输入想修改的书籍的 ID 并按下「查找」。");
        return;
    }

    static QString name, writer, publisher, ISBN; static int totalnum;
    name = ui->lineEdit_14->text();
    writer = ui->lineEdit_26->text();
    publisher = ui->lineEdit_31->text();
    ISBN = ui->lineEdit_32->text();
    totalnum = ui->lineEdit_33->text().toInt();

    if (name == "" || writer == "" || publisher == "" || ISBN == "" || totalnum == 0)
        QMessageBox::information(NULL,"Fail","信息不准确。添加失败。");
    else if (db.Check_Book_ISBN(ui->lineEdit_32->text()) && ISBN!=bk_modify_id->GetISBN())
        QMessageBox::information(NULL,"Fail","ISBN 在数据库内已存在。添加失败。");
    else
    {
        bk_modify_id->Modify(name, writer, publisher, ISBN, totalnum);
        QMessageBox::information(NULL,"Success","修改成功");
    }
}

void menuadmin::on_pushButton_27_clicked() //新增書籍
{
    static QString name, writer, ISBN, publisher;
    name = ui->lineEdit_14->text();
    writer = ui->lineEdit_26->text();
    ISBN = ui->lineEdit_32->text();
    publisher = ui->lineEdit_31->text();

    int total = ui->lineEdit_33->text().toInt();

    if (name == "" || writer == "" || ISBN == "" || publisher == "" || ui->lineEdit_33->text() == "")
        QMessageBox::information(NULL,"Fail","信息不准确。添加失败。");
    else if (db.Check_Book_ISBN(ui->lineEdit_32->text()))
        QMessageBox::information(NULL,"Fail","ISBN 在数据库内已存在。添加失败。");
    else
    {
        db.Add_Book(name, writer, publisher, ISBN, total);
        QMessageBox::information(NULL,"Success","添加成功");
    }
}

void menuadmin::on_pushButton_32_clicked()
{
    Book* bk = db.Find_Book_ID(ui->lineEdit_20->text().toInt());
    if (bk)
    {
        db.Delete_Book(bk->GetID());
        QMessageBox::information(NULL,"Success","删除成功");
    }
    else
        QMessageBox::information(NULL,"Fail","找不到匹配的书籍。");
}
