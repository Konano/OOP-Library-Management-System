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

void menuadmin::on_pushButton_27_clicked() //新增書籍
{
    static QString name, writer, ISBN, publisher;
    name = ui->lineEdit_14->text();
    writer = ui->lineEdit_26->text();
    ISBN = ui->lineEdit_32->text();
    publisher = ui->lineEdit_31->text();

    int total = ui->lineEdit_33->text().toInt();

    if (name == "" || writer == "" || ISBN == "" || publisher == "" || ui->lineEdit_33->text() == "")
        QMessageBox::information(NULL,"Fail","信息不完整。添加失败。");
    else if (db.Check_Book_ISBN(ui->lineEdit_32->text()))
        QMessageBox::information(NULL,"Fail","ISBN 在数据库内已存在。添加失败。");
    else
    {
        db.Add_Book(name, writer, publisher, ISBN, total);
        QMessageBox::information(NULL,"Success","添加成功");
    }
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

// //warning改改改 先顯示再讀入修改
// void menuadmin::on_pushButton_29_clicked() //修改書籍
// {
//     static QString name=ui->lineEdit_11->text(),writer=ui->lineEdit_12->text(),ISBN=ui->lineEdit_14->text(),publisher=ui->lineEdit_13->text();
//     static int ID=ui->lineEdit_15->text().toInt();
//     static vector<Book*> BookList;
//     db.Search_Book(BookList, name, writer, publisher, ISBN, ID);
//     QMessageBox::information(NULL,"Modify","請直接修改表格中的值");
//     ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);//任何時候都能對單元格修改
//     for(int i=0;i < (int)BookList.size(); i++){
//         QString IDnumb=QString::number(BookList[i]->GetID());
//         QString totalnum=QString::number(BookList[i]->AvailableTotal());
//         QString lentnumb=QString::number(BookList[i]->LentTotal());
//         ui->tableWidget->setItem(i,0,new QTableWidgetItem(BookList[i]->GetName()));//要改成getName
//         ui->tableWidget->setItem(i,1,new QTableWidgetItem(BookList[i]->GetWriter()));//改getWriter
//         ui->tableWidget->setItem(i,2,new QTableWidgetItem(BookList[i]->GetPublisher()));//改getPublisher
//         ui->tableWidget->setItem(i,3,new QTableWidgetItem(BookList[i]->GetISBN()));//改getISBN
//         ui->tableWidget->setItem(i,4,new QTableWidgetItem(IDnumb));//改getID
//         ui->tableWidget->setItem(i,5,new QTableWidgetItem(totalnum));//改getAvailableTotal
//         ui->tableWidget->setItem(i,6,new QTableWidgetItem(lentnumb));//改LentTotal
//     }
// }

// void menuadmin::on_pushButton_32_clicked() //刪除書籍
// {
//     if (!db.Check_Book_Exist(ui->lineEdit_26->text().toInt())){
//         QMessageBox::information(NULL,"Error","找不到該ID的書");
//     }
//     else{
//         db.Delete_Book(ui->lineEdit_26->text().toInt());
//         QMessageBox::information(NULL,"Success","刪除成功");
//     }
// }

// void menuadmin::on_pushButton_30_clicked() //新增讀者
// {
//     static QString name=ui->lineEdit_16->text(),password=ui->lineEdit_17->text();
//     static int max_borrow=ui->lineEdit_18->text().toInt();
//     db.Add_Reader(name,password ,max_borrow);
//     QMessageBox::information(NULL,"Success","添加成功!");

// }

// void menuadmin::on_pushButton_33_clicked() //查找讀者
// {
//     static QString name=ui->lineEdit_19->text();
//     static int ID=ui->lineEdit_20->text().toInt();
//     static vector<Reader*> ReaderList;
//     db.Search_Reader(ReaderList, name, ID);
//     for(int i=0;i < (int)ReaderList.size(); i++){
//         QString IDnumb=QString::number(ReaderList[i]->GetID());
//         ui->tableWidget->setItem(i,0,new QTableWidgetItem(ReaderList[i]->GetName()));//要改成getName
//         ui->tableWidget->setItem(i,1,new QTableWidgetItem(IDnumb));//改getWriter

//     }
//     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格禁止編輯
// }

// void menuadmin::on_pushButton_34_clicked() //修改書籍
// {
//     static QString name=ui->lineEdit_19->text();
//     static int ID=ui->lineEdit_20->text().toInt();
//     static vector<Reader*> ReaderList;
//     if (!db.Check_Reader_Exist(ID)){
//         QMessageBox::information(NULL,"Error","找不到該讀者");
//     }
//     else{

//         QMessageBox::information(NULL,"Modify","請直接修改表格中的值");
//         //同理上面
//     }
//     ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);//任何時候都能對單元格修改

// }

// void menuadmin::on_pushButton_31_clicked() //刪除書籍
// {
//     if (!db.Check_Book_Exist(ui->lineEdit_22->text().toInt())){
//         QMessageBox::information(NULL,"Error","找不到該ID的讀者");
//     }
//     else{
//         db.Delete_Book(ui->lineEdit_22->text().toInt());
//         QMessageBox::information(NULL,"Success","刪除成功");
//     }
// }


// //日期輸入方式
// void menuadmin::on_pushButton_35_clicked() //查詢借閱紀錄
// {
//     static vector<Record*> RecordList;
//     static QString d_year, d_month, d_day;
//     static QString userid=ui->lineEdit_23->text();
//     static QString bookid=ui->lineEdit_24->text();
//     //static QString date=ui->lineEdit_25->text();
//     //db.Search_Record(RecordList, readerID, bookID, type, d_year, d_month, d_day);
//     if(ui->radioButton->isChecked()){  //借閱

//     }
//     else if(ui->radioButton_2->isChecked()){ //歸還


//     }
//     else{}
// }

// void menuadmin::on_pushButton_36_clicked() //借閱審核
// {

// }


