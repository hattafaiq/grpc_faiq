#include <QSqlDatabase>

#ifndef STRC_H
#define STRC_H

struct data{
    QSqlDatabase db;
    int counter;
};

struct id_info_data{
    int id;
};


#endif // STRC_H
