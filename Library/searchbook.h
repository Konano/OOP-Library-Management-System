#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
//#include "database.h"

namespace Ui {
class searchbook;
}

class searchbook : public QWidget
{
    Q_OBJECT

public:
    explicit searchbook(QWidget *parent = 0);
    ~searchbook();


private:
    Ui::searchbook *ui;
};

#endif // SEARCHBOOK_H
