#include "database.h"

using namespace std;

inline bool Database::FILE_Input_String(QString &str, QString &s)
{
    static int pos;
    // cout << str.toStdString() << endl;
    pos = str.indexOf(',');
    if (pos > 0)
        s = str.left(pos), str = str.right(str.length()-pos-1);
    else
        s = str, str = "";
    // cout << str.toStdString() << endl;
    return s != "";
}

inline bool Database::FILE_Input_Int(QString &str, int &val)
{
    static int pos;
    // cout << str.toStdString() << endl;
    pos = str.indexOf(',');
    if (pos > 0)
        val = atoi(str.toStdString().substr(0,pos).c_str()), str = str.right(str.length()-pos-1);
    else
        val = atoi(str.toStdString().c_str()), str = "";
    // cout << str.toStdString() << endl;
    return true;
}

void Database::FILE_Input_Book()
{
    ifstream fin("book.csv");

    static QString name, writer, publisher, ISBN;
    static int id, number, ava_number;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_Int(str, id)) continue;
        if (!FILE_Input_String(str, name)) continue;
        if (!FILE_Input_String(str, writer)) continue;
        if (!FILE_Input_String(str, publisher)) continue;
        if (!FILE_Input_String(str, ISBN)) continue;
        if (!FILE_Input_Int(str, number)) continue;
        if (!FILE_Input_Int(str, ava_number)) continue;

        //cout << number << ava_number << endl;

        Book* book = new Book(id, name, writer, publisher, ISBN, number, ava_number);
        List_Book[book->GetID()] = book;
        Check_ISBN[ISBN]=true;
    }
}

void Database::FILE_Input_Reader()
{
    ifstream fin("reader.csv");

    static QString name, pwd;
    static int id, maxn, nown;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_Int(str, id)) continue;
        if (!FILE_Input_String(str, name)) continue;
        if (!FILE_Input_String(str, pwd)) continue;
        if (!FILE_Input_Int(str, maxn)) continue;
        if (!FILE_Input_Int(str, nown)) continue;

        Reader* user = new Reader(id, name, pwd, maxn, nown);
        List_User[user->GetID()] = user;
    }
}


void Database::FILE_Input_Admin()
{
    ifstream fin("admin.csv");

    static QString name, pwd;
    static int id;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_Int(str, id)) continue;
        if (!FILE_Input_String(str, name)) continue;
        if (!FILE_Input_String(str, pwd)) continue;

        Admin* user = new Admin(id, name, pwd);
        List_User[user->GetID()] = user;
    }
}

void Database::FILE_Input_Record()
{
    ifstream fin("record.csv");

    static int readerID, bookID; // , time
    static QString type, deal;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_String(str, type)) continue;
        if (!FILE_Input_String(str, deal)) continue;
        if (!FILE_Input_Int(str, readerID)) continue;
        if (!FILE_Input_Int(str, bookID)) continue;
        // if (!FILE_Input_Int(str, time)) continue;

        if (deal == "UNDEAL")
            List_Apply.push_back(new Record(type.toStdString(), deal.toStdString(), readerID, bookID)); // , (time_t)time)
        else
            List_Record.push_back(new Record(type.toStdString(), deal.toStdString(), readerID, bookID)); // , (time_t)time)
    }
}

Database::Database()
{
    FILE_Input_Book();
    FILE_Input_Reader();
    FILE_Input_Admin();
    FILE_Input_Record();
}

void Database::FILE_Output_Book()
{
    ofstream fou("book.csv");

    for(map<int,Book*>::iterator it = List_Book.begin(); it != List_Book.end(); it++)
    {
        Book* book = it->second;
        fou << book->GetID() << ","
            << book->GetName().toStdString() << ","
            << book->GetWriter().toStdString() << ","
            << book->GetPublisher().toStdString() << ","
            << book->GetISBN().toStdString() << ","
            << book->LentTotal()+book->AvailableTotal() << ","
            << book->AvailableTotal() << endl;
        delete book;
    }
}

void Database::FILE_Output_User()
{
    ofstream f_r("reader.csv");
    ofstream f_a("admin.csv");

    for(map<int,User*>::iterator it = List_User.begin(); it != List_User.end(); it++)
    {
        User* tmp = it->second;
        if (tmp->isAdmin())
        {
            Admin* admin = dynamic_cast<Admin*>(tmp);
            f_a << admin->GetID() << ","
                << admin->GetName().toStdString() << ","
                << admin->GetPwd().toStdString() << endl;
            delete admin;
        }
        else
        {
            Reader* reader = dynamic_cast<Reader*>(tmp);
            f_r << reader->GetID() << ","
                << reader->GetName().toStdString() << ","
                << reader->GetPwd().toStdString() << ","
                << reader->MaxBorrow() << ","
                << reader->NowBorrow() << endl;
            delete reader;
        }
    }
}

void Database::FILE_Output_Record()
{
    ofstream fou("record.csv");

    for(vector<Record*>::iterator it = List_Record.begin(); it != List_Record.end(); it++)
    {
        fou << (*it)->GetType() << ","
            << ((*it)->BoolDeal() ? ((*it)->BoolAccept() ? "ACCEPT" : "REJECT") : "UNDEAL") << ","
            << (*it)->GetReaderID() << ","
            << (*it)->GetBookID() << endl;
        delete (*it);
    }

    for(vector<Record*>::iterator it = List_Apply.begin(); it != List_Apply.end(); it++)
    {
        fou << (*it)->GetType() << ","
            << ((*it)->BoolDeal() ? ((*it)->BoolAccept() ? "ACCEPT" : "REJECT") : "UNDEAL") << ","
            << (*it)->GetReaderID() << ","
            << (*it)->GetBookID() << endl;
        delete (*it);
    }
}

Database::~Database()
{
    FILE_Output_Book();
    FILE_Output_User();
    FILE_Output_Record();
}

Book* Database::Find_Book_ID(const int ID) const
{
    if (List_Book.count(ID)) return List_Book.at(ID);
    return nullptr;
}

Book* Database::Find_Book_ISBN(const QString ISBN) const
{
    map<int,Book*>::const_iterator iter;
    for(iter=List_Book.begin(); iter!=List_Book.end(); iter++)
        if (iter->second->GetISBN() == ISBN)
            return iter->second;
    return nullptr;
}

void Database::Search_Book(vector<Book*> &List, const QString name, const QString writer, const QString publisher, const QString ISBN, const int ID) const
{
    map<int,Book*>::const_iterator iter;
    for (iter=List_Book.begin(); iter!=List_Book.end(); iter++)
        if ((ID==0 || iter->second->GetID()==ID) &&
            (ISBN=="" || iter->second->GetISBN()==ISBN) &&
            (writer=="" || iter->second->GetWriter().contains(writer)) &&
            (name=="" || iter->second->GetName().contains(name)) &&
            (publisher=="" || iter->second->GetPublisher().contains(publisher)))
        List.push_back(iter->second);
    cout << List.size() << endl;
}

void Database::Search_Record(vector<Record*> &List, const int readerID, const int bookID, const int type) const
{
    for (int i=0; i<(int)List_Record.size(); i++)
        if ((readerID==0 || List_Record[i]->GetReaderID()==readerID) &&
            (bookID==0 || List_Record[i]->GetBookID()==bookID) &&
            (type==0 || ((type==1)==(List_Record[i]->GetType()=="BORROW"))))
        List.push_back(List_Record[i]);
    cout << List.size() << endl;
}

void Database::Search_Apply(vector<Record*> &List, const int readerID, const int bookID, const int type) const
{
    for (int i=0; i<(int)List_Apply.size(); i++)
        if ((readerID==0 || List_Apply[i]->GetReaderID()==readerID) &&
            (bookID==0 || List_Apply[i]->GetBookID()==bookID) &&
            (type==0 || ((type==1)==(List_Apply[i]->GetType()=="BORROW"))))
        List.push_back(List_Apply[i]);
    cout << List.size() << endl;
}


void Database::Add_Book(const QString name, const QString writer, const QString publisher, const QString ISBN, const int total)
{
    Book* book = new Book(0, name, writer, publisher, ISBN, total, total);
    List_Book[book->GetID()] = book;
}

// void Database::Delete_Book(const int ID)
// {
//     List_Book.erase(ID);
//     //////////////////////////////////////////////////////////////////////////////
// }

// void Database::Modify_Book(const int ID, const QString name, const QString writer, const QString publisher, const QString ISBN, const int total)
// {
//     List_Book[ID]->Modify(total);
//     List_Book[ID]->Modifyname(name);
//     List_Book[ID]->Modifywriter(writer);
//     List_Book[ID]->Modifypublisher(publisher);
//     List_Book[ID]->ModifyISBN(ISBN);
// }

bool Database::Check_Book_ISBN(const QString ISBN) const
{
    return Check_ISBN.count(ISBN);
}

// bool Database::Check_Book_Exist(const int id) const
// {
//     int bookid = List_Book.count(id);
//     if(bookid!=0)    return true;
//     else            return false;
// }



// // Book Part (END)
// // User Part (Start)
User* Database::Find_User_Name(const QString &name) const
{
    map<int,User*>::const_iterator iter;
    for(iter = List_User.begin(); iter != List_User.end(); iter++)
    {
        if(iter->second->GetName() == name)
            return iter->second;
    }
    return nullptr;
}

User* Database::Find_User_ID(const int ID) const
{
    if (List_User.count(ID)) return List_User.at(ID);
    puts("Fuck");
    return nullptr;
}

// void Database::Search_Reader(vector<Reader*> &List, const QString name, const int ID) const
// {
//     map<int,Reader*>::const_iterator iter;
//     if(ID == 0)
//     {
//         for(iter = List_Reader.begin(); iter != List_Reader.end(); iter++)
//         {
//             if(iter->second->GetName() == name)
//                 List.push_back(iter->second);
//         }
//     }
//     else
//     {
//         int count = List_Reader.count(ID);
//         if(count != 0)
//             List.push_back(List_Reader.at(ID));
//     }
// }

// void Database::Add_Reader(const QString name, const QString password, const int max_borrow)
// {
//     Reader *user = new Reader(0, name, password, max_borrow);
//     List_Reader[user->GetID()] = user;
// }

// void Database::Delete_Reader(const int ID)
// {
//     map<int,User*>::iterator iter;
//     iter = List_User.find(ID);
//     //List_User[ID]->Modifyalive();
//     List_User.erase(iter);

// }

// void Database::Modify_Reader(const int ID, const QString name, const int max_borrow)
// {
//     List_User[ID]->ModifyName(name);
//     List_Reader[ID]->Modify(max_borrow);
//     return;
// }

// bool Database::Check_Reader_Exist(const int id) const
// {
//     return List_Reader.count(id);
// }

bool Database::Check_Borrow(const User* user, const Book* WanttoReturn) const
{
    int borrow_or_not = 0;
    for(int i=0; i<(int)List_Record.size(); i++)
        if (List_Record[i]->GetReaderID() == user->GetID() && List_Record[i]->GetBookID() == WanttoReturn->GetID())
            borrow_or_not += (List_Record[i]->GetType() == "BORROW"),
            borrow_or_not -= (List_Record[i]->GetType() == "RETURN");
    return borrow_or_not > 0;
}

void Database::Add_Apply(const string typestr, const User* user, const Book* WanttoBorrow)
{
    List_Apply.push_back(new Record(typestr, "UNDEAL", user->GetID(), WanttoBorrow->GetID()));
}

void Database::Apply_Delete(const int id)
{
    List_Record.push_back(List_Apply[id]);
    for(int i=id; i<(int)List_Apply.size()-1; i++)
        List_Apply[i] = List_Apply[i+1];
    List_Apply.pop_back();
}

void Database::Apply_Accept(const int id)
{
    Reader* rd = dynamic_cast<Reader*>(Find_User_ID(List_Apply[id]->GetReaderID()));
    Book* bk = Find_Book_ID(List_Apply[id]->GetBookID());

    if (List_Apply[id]->GetType() == "BORROW")
        rd -> Borrow(), bk -> Lent();
    else
        rd -> Giveback(), bk -> Return();
    List_Apply[id]->Accept();
    Apply_Delete(id);

    if (rd -> CanBorrow() == 0)
        for(int i=0; i<(int)List_Apply.size(); i++)
            if (List_Apply[i]->GetReaderID() == rd->GetID())
                Apply_Reject(i--);

    if (bk -> AvailableTotal() == 0)
        for(int i=0; i<(int)List_Apply.size(); i++)
            if (List_Apply[i]->GetBookID() == bk->GetID())
                Apply_Reject(i--);
}

void Database::Apply_Reject(const int id)
{
    List_Apply[id]->Reject();
    Apply_Delete(id);
}
