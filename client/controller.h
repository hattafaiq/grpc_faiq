#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>

#include <QObject>
#include <QDebug>

#include <QFile>
#include <iostream>
#include <memory>
#include <string>
#include "grpcpp/support/channel_arguments.h"
#include <grpcpp/grpcpp.h>
#include "gen_cloud4/Cloud.grpc.pb.h"
#include "gen_cloud4/Cloud.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ChannelArguments;
using Cloud::protokol_1;
using Cloud::protokol_2;

using Cloud::mes_client;
using Cloud::mes_server;
using Cloud::pesan_client;
using Cloud::pesan_server;

#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{
public:
    controller();
    int flag_sukses;
//    int flag_pengiriman;
    QVector<int>data_n[7];
//    int counter_s;
//    int conter_loop;
    QByteArray data_utama;
    QString initial_rute;
    QStringList list_rute;
    QString get_table_name(int tipe);
    QSqlDatabase db;
    QString con_name;
    int id_database;
    QByteArrayList all_data;
    QStringList rute_baru;
    QByteArrayList all_rute_param;
    QStringList cacah_data_name;
    void CallServer(std::string pesan, int flag, std::string server_alamat);
    void initial_database();
    void cari_induk_param(int p_id_aset);
private:
    void cari_induk_paramm(int parameter, int tipe);

    void cari_induk(int p_id_aset);

    void mulai_cari(QSqlQuery *query);

};

#endif // CONTROLLER_H
