#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include "strc.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{
public:
    controller();
    int save_data(QString rute,
                     QString aset,
                     int id_data_masuk,
                     int id_param,
                     int tipe_param,
                     int id_rute,
                     int time,
                     int siklus,
                     int id_database,
                     QByteArray all_rute_param,
                     QByteArray all_data);

    int simpan_param(QSqlQuery *query,
                      int id_paramnya,
                      int flag_param,
                      int id_aset,
                      int id_parent,
                      QString rute_baru,
                      QString cacah_data_name,
                      int id_data_masuk,
                      int id_param,
                      int tipe_param,
                      int id_rute,
                      int time,
                      int siklus,
                      int id_database,
                      QByteArray all_rute_param,
                      QByteArray all_data);

    int simpan_aset(QSqlQuery *query,
                      QString rute_baru,
                      QString cacah_data_name,
                      int id_data_masuk,
                      int id_param,
                      int tipe_param,
                      int id_rute,
                      int time,
                      int siklus,
                      int id_database,
                      QByteArray all_rute_param,
                      QByteArray all_data);

    QString get_table_name(int tipe);
    int s_id_rute_baru;
    void database_connect();

};

#endif // CONTROLLER_H
