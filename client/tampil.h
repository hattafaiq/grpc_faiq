#ifndef TAMPIL_H
#define TAMPIL_H
//#include "pars.h"
#include <QDebug>
#include <QStandardItem>
#include <QMainWindow>
#include "treesubwin.h"
#include "strc.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>

#include <QObject>
#include <QDebug>
#include <iostream>
#include <memory>
#include <string>
#include "grpcpp/support/channel_arguments.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <grpcpp/grpcpp.h>
#include "gen_cloud2/Cloud.grpc.pb.h"
#include "gen_cloud2/Cloud.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ChannelArguments;
using Cloud::protokol_1;
using Cloud::pesan_client;
using Cloud::pesan_server;

namespace Ui {
class Tampil;
}

class Tampil : public QMainWindow
{
    Q_OBJECT

public:
    //std::unique_ptr<Greeter2::Stub> stub_;
    explicit Tampil(QWidget *parent = nullptr);
    ~Tampil();
    //pars a;
   // void pesan_pertama();
    int flag_sukses;
    int flag_pengiriman;
    QVector<int>data_n[7];
    int counter_s;
    int conter_loop;
    int flag_kirim_ok;
    QStandardItem* assign_icon_x( QString name, int id_kind);
    QStandardItem* assign_icon(QStandardItemModel *tree, QString name, int id_kind, int id);
    QStandardItem* assign_icon_item(QStandardItem *tree, QString name, int id_kind, int id);
    void set_assign_icon_item(QStandardItem *tree, QString name, int id_kind, int id);
    void load_aset(QStandardItem *si, int id, int siapa);
    void load_param(QStandardItem *si, int id_aset, int siapa);
    //-----------------------------------
    void terima_data_proses();
    QByteArray data_utama;
    int flag_kirim;
    int flag_masukkan_param;
    void kirim1_info();
    Ui::Tampil *ui;
    QString initial_rute;
    QStringList list_rute;
    void tambah_aset(int parent, QString aset);
    QString get_table_name(int tipe);
    void susun_data(int id_param, int tipe_data);
    void kirim_data(int id_param, int tipe_data, QByteArray data);
    void cari_induk_param(int p_id_param);
    void cari_induk(int p_id_param);
    QAction *hapus;
    QMenu *menu_tgl;
    QStringList tampung_data;
    int index_data_hapus;
    int last_select_view_data;
    QString last_kota;
    void re_write();
    void setup_tampil_hirarki_server();
    void setup_tampil_hirarki_sofhaliza();
    void setup_tampil_hirarki_haliza();
    void index_tree_selected(QModelIndex index);
    void getAllChildren(QModelIndex idx, QModelIndexList &list);
    QList<int> onRouteChildTree;
    int kind_select;
    int id_select;
    QStandardItemModel *tree1;
    QStandardItemModel *tree2;
    int sudah_ada_aset;
    QSqlDatabase db;
    QString con_name;
    QSqlQuery *pQ;
    QSqlRelationalTableModel *r_model;
    QStringList data_ini;
    int id_database;
    void mulai_cari(QSqlQuery *query);
    QByteArrayList all_data;
    QStringList rute_baru;
    void cari_induk_paramm(int parameter, int tipe);
    QByteArrayList all_rute_param;
    QStringList cacah_data_name;

public slots:
    void on_treeView_clicked(QModelIndex index);
    void on_treeView_expanded(QModelIndex index);
    void on_treeView_activated(QModelIndex index);
    void CallServer(std::string pesan, int flag, std::string server_alamat);

private slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableView_2_pressed(const QModelIndex &index);

    void on_PB_connect_clicked();
    void on_PB_kirim_clicked();
    void on_PB_compare_clicked();
    void on_PB_synchron_clicked();

signals:
    void balas(std::string pesan, int flag, std::string server_alamat);

private:

};

#endif // TAMPIL_H
