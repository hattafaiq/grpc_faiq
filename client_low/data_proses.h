#include <QDebug>
#include <iostream>
#include <memory>
#include <string>
#include "grpcpp/support/channel_arguments.h"
#include <QFile>
#include "gen_cloud2/Cloud.grpc.pb.h"
#include "gen_cloud2/Cloud.pb.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <grpcpp/grpcpp.h>
#include <strk.h>

#ifndef DATA_PROSES_H
#define DATA_PROSES_H


class data_proses
{
public:
    data_proses();
    int id_database;
    QByteArrayList all_data;
     //QVector<int> data_n[6];
     QStringList rute_baru;
     void kirim();
     QByteArrayList all_rute_param;
    // QStringList cacah_data_name;
     QString initial_rute;

private:
    void setup_database();
    void mulai_cari(QSqlQuery *query);
    void cari_induk_paramm(int parameter, int tipe);
    QString get_table_name(int tipe);
    void cari_induk(int p_id_aset);

    QSqlDatabase db;


    //init data
};



#endif // DATA_PROSES_H
