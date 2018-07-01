#include "searchbook.h"
#include "ui_searchbook.h"


searchbook::searchbook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchbook)
{
    ui->setupUi(this);
    //for(int i=0;i<)
    //ui->tableWidget->setItem(2,2,new QTableWidgetItem("abc"));
}

searchbook::~searchbook()
{
    delete ui;
}




