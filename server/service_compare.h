#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include "strc.h"

#ifndef SERVICE_COMPARE_H
#define SERVICE_COMPARE_H


class service_compare
{
public:
    service_compare();
    QString get_table_name(int tipe);

//    QStringList list_aset;
//    QStringList list_rute;
//    QVector<int> t_id_param_lama;
//    QVector<int> t_id_data_masuk;
//    QVector<int> t_tipe_param;
//    QVector<int> t_id_rute;
//    QVector<int> t_time;
//    QVector<int> t_siklus;

    void eliminasi_data(int id_database,
                        QStringList rute,
                        QStringList aset,
                        QVector<int> data_masuk,
                        QVector<int> id_param,
                        QVector<int> tipe_param,
                        QVector<int> id_rute,
                        QVector<int> time,
                        QVector<int> siklus);

};

#endif // SERVICE_COMPARE_H
