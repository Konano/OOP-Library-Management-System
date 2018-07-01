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

void Database::FILE_Input_Book(ifstream &fin)
{
    static QString name, writer, publisher, ISBN;
    static int number, ava_number;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_String(str, name)) continue;
        if (!FILE_Input_String(str, writer)) continue;
        if (!FILE_Input_String(str, publisher)) continue;
        if (!FILE_Input_String(str, ISBN)) continue;
        if (!FILE_Input_Int(str, number)) continue;
        if (!FILE_Input_Int(str, ava_number)) continue;

        //cout << number << ava_number << endl;

        Book* book = new Book(name, writer, publisher, ISBN, number, ava_number);
        List_Book[book->GetID()] = book;
        Check_ISBN[ISBN]=true;
    }
}

void Database::FILE_Input_Reader(ifstream &fin)
{
    static QString name, pwd;
    static int maxn, nown;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_String(str, name)) continue;
        if (!FILE_Input_String(str, pwd)) continue;
        if (!FILE_Input_Int(str, maxn)) continue;
        if (!FILE_Input_Int(str, nown)) continue;

        Reader* user = new Reader(name, pwd, maxn, nown);
        List_User[user->GetID()] = user;
    }
}


void Database::FILE_Input_Admin(ifstream &fin)
{
    static QString name, pwd;

    static QString str;
    static char str_c[FILE_Input_Size];

    while (true)
    {
        fin.getline(str_c, FILE_Input_Size);
        // puts(str_c.c_str());
        if (strlen(str_c)>1) str = str_c; else return;
        if (!FILE_Input_String(str, name)) continue;
        if (!FILE_Input_String(str, pwd)) continue;

        Admin* user = new Admin(name, pwd);
        List_User[user->GetID()] = user;

        // cout << name.toStdString() << pwd.toStdString() << endl;
    }
}


void Database::FILE_Input_Apply(ifstream &fin)
{
    static QString type;
    static int readerID, bookID, time;

    static QString str;
    static string str_c;

    while (true)
    {
        getline(fin, str_c);
        // puts(str_c.c_str());
        if (str_c.length()>1) str = str_c.c_str(); else return;
        if (!FILE_Input_String(str, type)) continue;
        if (!FILE_Input_Int(str, readerID)) continue;
        if (!FILE_Input_Int(str, bookID)) continue;
        if (!FILE_Input_Int(str, time)) continue;

        List_Apply.push_back(new Apply((type == "Borrow" ? 1 : (type == "Return" ? 2 : 0)),
                                        readerID, bookID, (time_t)time));
    }
}

void Database::FILE_Input_Record(ifstream &fin)
{
    static int readerID, bookID, time;

    static QString str;
    static string str_c;

    while (true)
    {
        getline(fin, str_c);
        // puts(str_c.c_str());
        if (str_c.length()>1) str = str_c.c_str(); else return;
        if (!FILE_Input_Int(str, readerID)) continue;
        if (!FILE_Input_Int(str, bookID)) continue;
        if (!FILE_Input_Int(str, time)) continue;

        List_Record.push_back(new Record(readerID, bookID, (time_t)time));
    }
}

void Database::Init()
{
    ifstream book_fin("book.csv");
    FILE_Input_Book(book_fin);
    ifstream reader_fin("reader.csv");
    FILE_Input_Reader(reader_fin);
    ifstream admin_fin("admin.csv");
    FILE_Input_Admin(admin_fin);
    ifstream apply_fin("apply.csv");
    FILE_Input_Apply(apply_fin);
    ifstream record_fin("record.csv");
    FILE_Input_Record(record_fin);
}

Database::~Database()
{
    FILE_Output_Book();
    FILE_Output_Reader();
    FILE_Output_Admin();
    FILE_Output_Apply();
    FILE_Output_Record();

    for(map<int,User*>::iterator it = List_User.begin(); it != List_User.end(); it++)
    {
        User* tmp = it->second;
        if (tmp->isAdmin())
            delete dynamic_cast<Admin*>(tmp);
        else
            delete dynamic_cast<Reader*>(tmp);
    }
    for(map<int,Book*>::iterator it = List_Book.begin(); it != List_Book.end(); it++) delete it->second;
    for(vector<Apply*>::iterator it = List_Apply.begin(); it != List_Apply.end(); it++) delete (*it);
    for(vector<Record*>::iterator it = List_Record.begin(); it != List_Record.end(); it++) delete (*it);
}

// Book Part(start)

Book* Database::Find_Book_ID(const int ID) const
{
    int count = List_Book.count(ID);
    Book* book =List_Book.at(ID);
    if(count!=0) return book;
    return nullptr;
}
Book* Database::Find_Book_ISBN(const QString ISBN) const
{
    map<int,Book*>::const_iterator iter;
    for(iter=List_Book.begin(); iter!=List_Book.end();iter++){
        if(iter->second->GetISBN()==ISBN)
            return iter->second;
    }
    return nullptr;
}
void Database::Search_Book(vector<Book*> &List, const QString name, const QString writer, const QString publisher, const QString ISBN, const int ID) const
{
    map<int,Book*>::const_iterator iter;
    if(ID == 0)
    {
        for(iter = List_Book.begin();iter!=List_Book.end();iter++){
            if(iter->second->GetISBN()==ISBN||iter->second->GetWriter()==writer||iter->second->GetName()==name||iter->second->GetPublisher()==publisher)
                List.push_back(iter->second);
        }
    }
    else
    {
        int count = List_Book.count(ID);
        if(count!=0)
            List.push_back(List_Book.at(ID));
    }
    cout << writer.toStdString() << List.size() << endl;
}

void Database::Add_Book(const QString name, const QString writer, const QString publisher, const QString ISBN, const int total){
    Book* book = new Book(name, writer, publisher, ISBN, total,1);
    List_Book[book->GetID()] = book;
}

void Database::Delete_Book(const int ID){
    List_Book.erase(ID);
}

void Database::Modify_Book(const int ID, const QString name, const QString writer, const QString publisher, const QString ISBN, const int total){
    List_Book[ID]->Modify(total);
    List_Book[ID]->Modifyname(name);
    List_Book[ID]->Modifywriter(writer);
    List_Book[ID]->Modifypublisher(publisher);
    List_Book[ID]->ModifyISBN(ISBN);

}
bool Database::Check_Book_ISBN(const QString ISBN) const
{
    int count = Check_ISBN.count(ISBN);
    if(count!=0) return true;
    else         return false;

}
bool Database::Check_Book_Exist(const int id) const
{
    int bookid = List_Book.count(id);
    if(bookid!=0)    return true;
    else            return false;
}



// Book Part (END)
// User Part (Start)
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

Reader* Database::Find_Reader_ID(const int ID) const
{
    int count = List_Reader.count(ID);
    Reader* user=List_Reader.at(ID);
    if(count != 0) return user;
    return nullptr;
}

void Database::Search_Reader(vector<Reader*> &List, const QString name, const int ID) const
{
    map<int,Reader*>::const_iterator iter;
    if(ID == 0)
    {
        for(iter = List_Reader.begin(); iter != List_Reader.end(); iter++)
        {
            if(iter->second->GetName() == name)
                List.push_back(iter->second);
        }
    }
    else
    {
        int count = List_Reader.count(ID);
        if(count != 0)
            List.push_back(List_Reader.at(ID));
    }

}

void Database::Add_Reader(const QString name, const QString password, const int max_borrow)
{
    Reader *user = new Reader(name, password, max_borrow);
    List_Reader[user->GetID()] = user;
}

void Database::Delete_Reader(const int ID)
{
    map<int,User*>::iterator iter;
    iter = List_User.find(ID);
    //List_User[ID]->Modifyalive();
    List_User.erase(iter);

}

void Database::Modify_Reader(const int ID, const QString name, const int max_borrow)
{
    List_User[ID]->ModifyName(name);
    List_Reader[ID]->Modify(max_borrow);
    return;
}

bool Database::Check_Reader_Exist(const int id) const
{
    int count = List_Reader.count(id);
    if(count != 0) return true;
    return false;
}

// User Part End
bool Database::Check_Borrow(const User* user, const Book* WanttoReturn) const
{

}
void Database::Add_Apply_Borrow(const User* user, const Book* WanttoBorrow)
{

}


 void Database::Add_Apply_Return(const User* user, const Book* WanttoBorrow)
 {

 }

 Database::Database() {}
