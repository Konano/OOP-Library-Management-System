#ifndef DATABASE_H
#define DATABASE_H

#include "main.h"
#include "book.h"
#include "user.h"
#include "reader.h"
#include "admin.h"
#include "record.h"
#include <QString>
#include <qdebug.h>
#include <QMap>
#include <map>
#include <fstream>

#define FILE_Input_Size 1000

class Database
{
    map<int,User*>		List_User;
    map<int,Book*>		List_Book;
    map<QString,bool>   Check_ISBN;
    vector<Record*>		List_Apply;
    vector<Record*>		List_Record;

    bool FILE_Input_String(QString &str, QString &s);
    bool FILE_Input_Int(QString &str, int &val);
    void FILE_Input_Book();
    void FILE_Input_Reader();
    void FILE_Input_Admin();
    void FILE_Input_Record();

    void FILE_Output_Book();
    void FILE_Output_User();
    void FILE_Output_Record();

public:

    Database();
    ~Database();

    Record* GetApply(const int id) const;
    int GetApplyTotal() const { return (int)List_Apply.size(); }

    User* Find_User_Name(const QString &name) const;		// 由名字查找 User，若查不到则返回 nullprt
    User* Find_User_ID(const int ID) const;			// 由 ID 查找 Reader，若查不到则返回 nullprt
    Book* Find_Book_ID(const int ID) const;				// 由 ID 查找 Book，若查不到则返回 nullprt
    Book* Find_Book_ISBN(const QString ISBN) const;		// 由 ISBN 查找 Book，若查不到则返回 nullprt

    void Search_Book(vector<Book*> &List, const QString name, const QString writer, const QString publisher, const QString ISBN, const int ID) const;
    // 书的检索，将检索的信息 push_back 到 List 中，未限定的条件，表现为字符串为空串 & int 为 0
    void Search_Reader(vector<Reader*> &List, const QString name, const int ID) const;
    // 读者的检索，将检索的信息 push_back 到 List 中，未限定的条件，表现为字符串为空串 & int 为 0
    void Search_Record(vector<Record*> &List, const int readerID, const int bookID, const int type) const;
    // 记录的检索，将检索的信息 push_back 到 List 中，未限定的条件，表现为字符串为空串 & int 为 0
    void Search_Apply(vector<Record*> &List, const int readerID, const int bookID, const int type) const;
    // 未处理申请的检索，将检索的信息 push_back 到 List 中，未限定的条件，表现为字符串为空串 & int 为 0
    void Search_unReturnBook(vector<Record*> &List, const int readerID) const;
    // 未归还书的检索，将检索的信息 push_back 到 List 中，未限定的条件，表现为字符串为空串 & int 为 0

    void Add_Book(const QString name, const QString writer, const QString publisher, const QString ISBN, const int total);
    // 添加书本
    void Add_Reader(const QString name, const QString password, const int max_borrow);
    // 添加读者
    void Add_Apply(const string typestr, const User* user, const Book* WanttoBorrow);
    // 添加申请

    void Delete_Book(const int ID);
    // 删除书本
    void Delete_User(const int ID);
    // 删除用户

    void Modify_Book(const int ID, const QString name, const QString writer, const QString publisher, const QString ISBN, const int total);
    // 修改书本
    void Modify_Reader(const int ID, const QString name, const int max_borrow);
    // 修改读者

    void Apply_Delete(const int id);
    // 删除申请并转成记录
    void Apply_Accept(const int id);
    // 批准申请
    void Apply_Reject(const int id);
    // 拒绝申请

    bool Check_Borrow(const User* user, const Book* WanttoReturn) const;
    // 检查这本书是否正被某读者借阅中
    bool Check_Book_ISBN(const QString ISBN) const;
    // 检查是否存在此 ISBN 对应的书
};

#endif // DATABASE_H
