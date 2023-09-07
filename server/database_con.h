#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <strc.h>
#include <QDebug>

#ifndef DATABASE_CON_H
#define DATABASE_CON_H


class database_con
{
public:
    database_con();
    void connect_db();
};

#endif // DATABASE_CON_H
