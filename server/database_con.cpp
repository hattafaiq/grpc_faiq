#include "database_con.h"

struct data data_base;

database_con::database_con()
{

}

void database_con::connect_db()
{
    data_base.db = QSqlDatabase::addDatabase("QMYSQL");
    data_base.db.setHostName("127.0.0.1");//port 2121
    data_base.db.setDatabaseName("test");
    data_base.db.setUserName("root");
    data_base.db.setPassword("password");

    if (!data_base.db.open())
    {
      data_base.counter+=1;
      qDebug()<<"tidak bisa buka database???????----->"<<data_base.counter;
    }else{
        qDebug()<<"bisa";
    }
}
