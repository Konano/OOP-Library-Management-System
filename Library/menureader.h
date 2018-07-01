#ifndef MENUREADER_H
#define MENUREADER_H

#include "book.h"
#include "database.h"
#include "admin.h"
#include "user.h"
#include "reader.h"
#include <QWidget>
#include <QMessageBox>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class menureader;
}

class menureader : public QWidget
{
    Q_OBJECT

public:
    explicit menureader(QWidget *parent = 0);
    ~menureader();

private slots:
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_38_clicked();

private:
    Ui::menureader *ui;
};

#endif // MENUREADER_H
