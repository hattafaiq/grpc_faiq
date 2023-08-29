////////kemaren crash antara grpc dan sql yang
/// masing masing menggunakan kompiler berbeda
/// protobuf versi 3.21.12
/// grcp versi 1.53.0
///
/// saat ini sama sama menggunakan compiler 11
///-- Using protobuf 3.19.4.0
///-- Using gRPC 1.46.0
///
///
///
//komunikasi masih belum bisa stabil, coba dicari data yang kemaren
//untuk balas balasan 1 sama lain dan tidak terikat 1 loop atau membahayakan

//server kenapa kok hang kadang enggak kadang lancar kadang nggak?
//clearkan dulu kenapa servernya kalo bolak balik compare dan synchronize
//baru nanti yang lain seperti save dan lanjut ke status

#include "bisa.h"
#include "strc.h"
//#include <grpcpp/grpcpp.h>
struct data siapa;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using Cloud::protokol_1;
using Cloud::protokol_2;

using Cloud::pesan_client;
using Cloud::pesan_server;
using Cloud::mes_client;
using Cloud::mes_server;

class GreeterServiceImpl final : public protokol_1::Service  {
    public:
    bisa b;
    Status initial_data(ServerContext* context, const pesan_client* request, pesan_server* reply) override {
        int flag_pesan=0;
        QStringList rute_s;
        QByteArrayList all_data;
        QByteArrayList all_rute_param;
        QStringList cacah_data_aset;
        QVector<int> data_new[7];
        if(request->header_pesan()=="list_info"){
            qDebug()<<"-------------------------";
            qDebug()<<"client:"<<"list info";
            qDebug()<<"server:"<<"balas";
            //-------------------------------------------------//
            std::cout << "mulai cek data: size: " <<
                 request->aset_size()
                << request->rute_size()<<" "
                <<request->id_param_lama_size() << " "
                << request->id_tipe_param_size() << " "
                << request->id_rute_lama_size() << " "
                << request->timestamp_size() << " "
                << request->siklus_size() << " "
                << std::endl;
            //masukkan data pertama kali yang dikirim oleh client
            //data client yang akan dibandingkan dengan data server
            for (int i = 0; i < request->id_param_lama_size(); i++) {
                data_new[0].push_back(request->id_data_masuk(i));//id_data_masuk
                data_new[1].push_back(request->id_param_lama(i));//id_param
                data_new[2].push_back(request->id_tipe_param(i));//id_tipe_param
                data_new[3].push_back(request->id_rute_lama(i));//id_rute
                data_new[4].push_back(request->timestamp(i));//timestamp
                data_new[5].push_back(request->siklus(i));//siklus
                cacah_data_aset.push_back(QString::fromStdString(request->aset(i))); //aset
                rute_s.push_back(QString::fromStdString(request->rute(i)));
                std::cout << request->aset(i)
                << " "<< request->id_data_masuk(i)
                << " "<< request->id_param_lama(i)
                << " "<< request->id_tipe_param(i)
                << " "<< request->id_rute_lama(i)
                << " "<< request->timestamp(i)
                << " "<< request->siklus(i)
                << " "<<request->rute(i)
                << std::endl;
            }
            //cek ukuran array datanya yang sudah dimasukkan
            qDebug()<<"kenapa size: "
                <<data_new[0].size()
                <<data_new[1].size()
                <<data_new[2].size()
                <<data_new[3].size()
                <<data_new[4].size()
                <<data_new[5].size();

            //------mulai eliminasi--------------------//
            b.eliminasi_data(rute_s,cacah_data_aset,data_new[0],data_new[1],data_new[2],data_new[3],data_new[4],data_new[5]);
            //-----------------------------------------------------//

            //---mulai kirim data yang belum ada-------//
//            qDebug()<<"---inisial data yang belom ada di server---";
//            for(int i=0; i<b.t_tipe_param.size(); i++){
//                qDebug()<<b.t_tipe_param[i]<<b.t_time[i]<<b.t_siklus[i];
//            }
            std::vector<int> id_data_masuk, id_param,id_tip_parm,id_rut,time,siklus;
            id_data_masuk = b.t_id_data_masuk.toStdVector();
            id_param    = b.t_id_param_lama.toStdVector();
            id_tip_parm = b.t_tipe_param.toStdVector();
            id_rut      = b.t_id_rute.toStdVector();
            time        = b.t_time.toStdVector();
            siklus      = b.t_siklus.toStdVector();

            google::protobuf::RepeatedField<int> id_data_masuk_s(id_data_masuk.begin(), id_data_masuk.end());
            google::protobuf::RepeatedField<int> id_param_s(id_param.begin(), id_param.end());
            google::protobuf::RepeatedField<int> id_tip_parm_s(id_tip_parm.begin(), id_tip_parm.end());
            google::protobuf::RepeatedField<int> id_rut_s(id_rut.begin(), id_rut.end());
            google::protobuf::RepeatedField<int> time_s(time.begin(), time.end());
            google::protobuf::RepeatedField<int> siklus_s(siklus.begin(), siklus.end());
            reply->mutable_id_param_lama()->Swap(&id_param_s);
            reply->mutable_id_tipe_param()->Swap(&id_tip_parm_s);
            reply->mutable_id_rute_lama()->Swap(&id_rut_s);
            reply->mutable_timestamp()->Swap(&time_s);
            reply->mutable_siklus()->Swap(&siklus_s);
            reply->mutable_id_data_masuk()->Swap(&id_data_masuk_s);
            //----------------------------------------//
            for(int x=0; x<b.list_aset.size(); x++){
                QString ay = b.list_aset[x];
                QString rute = b.list_rute[x];
                reply->mutable_rute()->Add(rute.toStdString());
                reply->mutable_aset()->Add(ay.toStdString());
            }
            reply->set_header_pesan("balas");
        }
    return Status::OK;
}

};

class GreeterServiceImpl2 final : public protokol_2::Service  {
    public:
    bisa *b;
    Status kirim_data(ServerContext* context, const mes_client* request, mes_server* reply) override {
        std::cout <<"req pesan dari client diterima:->" << request->header_pesan() <<std::endl;
        if(request->header_pesan()=="kirim_data"){
            //cek dulu size nya;
            QByteArray all_data = QByteArray::fromStdString(request->data());
            QByteArray all_rute_param = QByteArray::fromStdString(request->param());
            std::cout<<"cek data_upload client:" <<
                          request->jumlah_data()<< " "<<
                          request->pesan_ke()<< " "<<
                          request->aset() << " "<<
                           request->rute() <<" "<<
                           request->id_data_masuk()<<" "<<
                           request->id_param_lama() <<" "<<
                           request->id_tipe_param() <<" "<<
                           request->id_rute_lama() <<" "<<
                           request->timestamp() <<" "<<
                           request->siklus() <<"| size data:"<<
                           all_data.toStdString().size() <<"| size set param: "<<
                           all_rute_param.toStdString().size() <<" "<<
                           std::endl;
                            QString rute = QString::fromStdString(request->rute());
                            QString aset = QString::fromStdString(request->aset());
                            int id_data_masuk = request->id_data_masuk();
                            int id_param = request->id_param_lama();
                            int tipe_param = request->id_tipe_param();
                            int id_rute = request->id_rute_lama();
                            int time = request->timestamp();
                            int siklus = request->siklus();
                            int id_database = 0;
                b = new bisa;
                if(b->save_data(rute,
                            aset,
                            id_data_masuk,
                            id_param,
                            tipe_param,
                            id_rute,
                            time,
                            siklus,
                            id_database,
                            all_rute_param,
                            all_data) == 1)
                reply->set_header_pesan("terima_data");
                else reply->set_header_pesan("reload");

        }
        return Status::OK;
    }
};

bisa::bisa(QObject *parent) : QObject(parent)
{
   // std::cout<<"versinya" <<grpc::Version() << std::endl;
}

void bisa::RunServer() {
    siapa.apa =9;

    GreeterServiceImpl service;
    GreeterServiceImpl2 service2;
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.

    builder.SetMaxSendMessageSize(1024 * 1024 * 1024);
    builder.SetMaxMessageSize(1024 * 1024 * 1024);
    builder.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    std::string server_address("127.0.0.1:50051");

//  grpc::EnableDefaultHealthCheckService(true);
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    builder.RegisterService(&service2);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    // grpc::ServerAsyncResponseWriter<EchoResponse> response_writer()

    // 18 agustus 2023
    //informasi grpc bekerja secara asyncronus sehingga bisa langsung multi client, namun
    //harus mengenal id client dan bagaimana cara membatasi autentifikasinya.

    //sudah bisa nerima informasi dengan selamat secara bolak balik
    //todo berikutnya;
    //---mengenal id client
    //---menghitung size data yang mau dikirim.
    //---metode pengirimannya seperti apa? satu satu data

    server->Wait();
}

bisa::~bisa()
{

}

QString bisa::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
    return nama_tabel;
}

void bisa::mulai_cari_server(QSqlQuery *query)
{

}

void bisa::eliminasi_data(QStringList rute,QStringList aset, QVector<int> id_data_masuk1, QVector<int> id_param1, QVector<int> tipe_param1,QVector<int> id_rute1, QVector<int> time1, QVector<int> siklus1)
{
    QVector<int> id_data_masuk = id_data_masuk1;
    QVector<int> id_param = id_param1;
    QVector<int> tipe_param = tipe_param1;
    QVector<int> id_rute = id_rute1;
    QVector<int> time = time1;
    QVector<int> siklus = siklus1;
    QStringList cacah_data_aset = aset;

    dbx = QSqlDatabase::addDatabase("QMYSQL");
    dbx.setHostName("127.0.0.1");//port 2121
    dbx.setDatabaseName("test");
    dbx.setUserName("root");
    dbx.setPassword("password");
    if (!dbx.open())
    {
      QMessageBox::critical(0, QObject::tr("Database Error"),dbx.lastError().text());
    }else{
        qDebug()<<"bisa";
    }
    //masukin nilainya per array bro
    qDebug()<<"------------cek eliminasi data awal----------";
    qDebug()<<"- jumlah data rute:"<<rute.size();
    qDebug()<<"- jumlah data id_data_masuk:"<< id_data_masuk.size();
    qDebug()<<"- jumlah data id_param:"<< id_param.size();//1
    qDebug()<<"- jumlah data tipe_param:"<< tipe_param.size();//2
    qDebug()<<"- jumlah data id_rute:"<<id_rute.size();//3
    qDebug()<<"- jumlah data time:"<<time.size();//4
    qDebug()<<"- jumlah data siklus:"<<siklus.size();//5
    qDebug()<<"----------------------------------------";
    for(int i=0; i<id_param.size(); i++){
        qDebug()<<"cek data:"<<rute[i]<<id_data_masuk[i]<<tipe_param[i]<<time[i]<<siklus[i];
    }
    QSqlQuery query(dbx);
    int konter=0;
    QString qu;
    for(int i=0; i<id_param1.size(); i++){
        //qDebug()<<"2cek data:"<<tipe_param[i]<<time[i]<<siklus[i];
        qu = QString("SELECT id FROM %1 WHERE data_timestamp=%2").arg(get_table_name(tipe_param1[i]),QString::number(time1[i]));
        if(tipe_param1[i]==3 || tipe_param1[i]==28 ||tipe_param1[i]==2|| tipe_param1[i]==11){
         qu = QString("SELECT id FROM %1 WHERE data_timestamp=%2 AND siklus=%3").arg(get_table_name(tipe_param1[i]),QString::number(time1[i]),QString::number(siklus1[i]));
        }
        if(!query.exec(qu)) {}//qDebug()<< "kenapa ERROR:: " <<query.lastError().text();}
        else{while(query.next()){
                rute.erase(rute.begin()+i-konter);
                id_data_masuk.erase(id_data_masuk.begin()+i-konter);
                id_param.erase(id_param.begin()+i-konter);
                tipe_param.erase(tipe_param.begin()+i-konter);
                id_rute.erase(id_rute.begin()+i-konter);
                time.erase(time.begin()+i-konter);
                siklus.erase(siklus.begin()+i-konter);
                cacah_data_aset.erase(cacah_data_aset.begin()+i-konter);
                konter+=1;
            }}
    }

//    //ccek ulang yang tidak ada siapa aja
    qDebug()<<"------------cek sudah eliminasi data----------";
    qDebug()<<"- jumlah data rute:"<<rute.size();
    qDebug()<<"- jumlah data list aset:"<<cacah_data_aset.size();
    qDebug()<<"- jumlah data id_data_masuk:"<< id_data_masuk.size();//1
    qDebug()<<"- jumlah data id_param:"<< id_param.size();//1
    qDebug()<<"- jumlah data tipe_param:"<< tipe_param.size();//2
    qDebug()<<"- jumlah data id_rute:"<<id_rute.size();//3
    qDebug()<<"- jumlah data time:"<<time.size();//4
    qDebug()<<"- jumlah data siklus:"<<siklus.size();//5
    qDebug()<<"-------------cek data yang sudah dieliminasi---";
    for(int a=0; a<id_param.size(); a++){
        qDebug()<<"-"
                <<cacah_data_aset[a]
                <<tipe_param[a]
                <<id_rute[a]
                <<time[a]
                <<siklus[a]
                <<rute[a]
                <<id_data_masuk[a];
    }
    qDebug()<<"-----------------------------------------------";
    list_rute = rute;
    list_aset = cacah_data_aset;
    t_id_param_lama = id_param;
    t_tipe_param = tipe_param;
    t_id_rute = id_rute;
    t_time = time;
    t_siklus = siklus;
    t_id_data_masuk = id_data_masuk;
}

void bisa::simpan_param(QSqlQuery *query, int id_paramnya, int flag_masukkan_param, int id_aset, int id_parent, QString rute_baru, QString cacah_data_name, int id_data_masuk, int id_param, int tipe_param, int id_rute, int time, int siklus, int id_database, QByteArray all_rute_param, QByteArray all_data)
{
    QString aa;
    if(flag_masukkan_param==0){
        //aa = QString("INSERT INTO parameter ( id_tipe_param, id_aset, urut) VALUES('%1',%2,%3)").arg(QString::number(data_new[2][a]),QString::number(id_parent),QString::number(1));
        aa = QString("INSERT INTO parameter (id_tipe_param,id_aset,urut)"
                     " SELECT %1,%2,%3 WHERE NOT EXISTS "
                     "(SELECT id_tipe_param,id_aset,urut FROM parameter "
                     "WHERE id_tipe_param=%4 AND id_aset=%5)").
                     arg(QString::number(tipe_param),//id_tipe_param
                         QString::number(id_parent),//id_aset
                         QString::number(1),//urut
                         QString::number(tipe_param),//id_tipe_param
                         QString::number(id_parent));//id_aset
        qDebug()<<id_parent<<"------<<>>";
        id_paramnya=id_parent;
        if(!query->exec(aa)){qDebug()<<"1gagal simpen"<<id_aset;}
        else{while(query->next()){qDebug()<<"1sukses="<<id_aset;
            id_paramnya=query->lastInsertId().toInt();
           // flag_masuk_param1=1;
            }}
    }
    else{
   // aa = QString("INSERT INTO parameter ( id_tipe_param, id_aset, urut) VALUES('%1',%2,%3)").arg(QString::number(data_new[2][a]),QString::number(id_aset),QString::number(1));
    aa = QString("INSERT INTO parameter (id_tipe_param, id_aset, urut)"
                 " SELECT %1,%2,%3 WHERE NOT EXISTS "
                 "(SELECT id_tipe_param,id_aset,urut FROM parameter "
                 "WHERE id_tipe_param=%4 AND id_aset=%5)").
            arg(QString::number(tipe_param),//id_tipe_param
                QString::number(id_aset),//id_aset
                QString::number(1),//urut
                QString::number(tipe_param),//id_tipe_param
                QString::number(id_aset));//id_aset
    qDebug()<<aa;
    if(!query->exec(aa)){qDebug()<<"1gagal simpen"<<id_aset;}
    else{while(query->next()){qDebug()<<"1sukses="<<id_aset;
        id_paramnya=query->lastInsertId().toInt();
        //flag_masuk_param2=1;
        }}
    flag_masukkan_param=0;
    }
    id_param = id_paramnya;
    id_parent=0;
}

void bisa::simpan_aset(QSqlQuery *query, QString rute_baru, QString cacah_data_name, int id_data_masuk, int id_param, int tipe_param, int id_rute, int time, int siklus, int id_database, QByteArray all_rute_param, QByteArray all_data)
{
    int id_aset=0;
    int id_parent=0;
    int flag_masukkan_param=0;
    QStringList list_aset = cacah_data_name.split("/");
    QString aa;
    int id_paramnya=0;

    for(int k=0; k<list_aset.size()-1; k++){
        QString name = (QString) list_aset[k];
        aa = QString("SELECT id FROM aset"
                     " WHERE name='%1'AND id_parent=%2 AND id_database=%3").
                arg(name,
                    QString::number(id_parent),
                    QString::number(id_database));//note id_database yang kurang
        if(!query->exec(aa)){qDebug()<<"tidak ada1="<<name;}
        if(query->first()){qDebug()<<"ada="<<name;
        id_parent = query->value("id").toInt();
            }
        else {
          qDebug()<<"tidak ada2="<<name;
          flag_masukkan_param=1;

          //id_parent = query1.lastInsertId().toInt();
          aa = QString("INSERT INTO aset ( name, id_kind, id_parent, id_database, id_user) "
                       "VALUES('%1',%2,%3,%4,%5)").
                       arg(name,
                           QString::number(0),
                           QString::number(id_parent),
                           QString::number(id_database),
                           QString::number(0));
          if(!query->exec(aa)){qDebug()<<"1gagal simpen"<<name;}
          else{while(query->next())qDebug()<<"1sukses="<<name;
          id_paramnya=query->lastInsertId().toInt();//coba
          }

          if(query->first()){qDebug()<<"2sukses="<<name;}
          else{qDebug()<<"mulai simpen"<<name;
          id_parent = query->lastInsertId().toInt();}
        }
        id_aset=query->lastInsertId().toInt();
    }

    simpan_param(query,
                 id_paramnya,
                 flag_masukkan_param,
                 id_aset,
                 id_parent,
                 rute_baru,
                 cacah_data_name,
                 id_data_masuk,
                 id_param,
                 tipe_param,
                 id_rute,
                 time,
                 siklus,
                 id_database,
                 all_rute_param,
                 all_data);
}


int bisa::save_data(QString rute_baru,
                       QString cacah_data_name,
                       int id_data_masuk,
                       int id_param,
                       int tipe_param,
                       int id_rute,
                       int time,
                       int siklus,
                       int id_database,
                       QByteArray all_rute_param,
                       QByteArray all_data)
{
    id_database=49965;
    QSqlQuery query(dbx);
 //---------------------------------------------------------------------------------------------------//
    qDebug()<<"id paramnya size";
    simpan_aset(&query,
                rute_baru,
                cacah_data_name,
                id_data_masuk,
                id_param,
                tipe_param,
                id_rute,
                time, siklus,
                id_database,
                all_rute_param,
                all_data);

    int id_rute_baru;
    QString qu;
    qu = QString("INSERT INTO rute (nama_rute,id_database)"
                 " SELECT '%1',%2 WHERE NOT EXISTS "
                 "(SELECT nama_rute,id_database FROM rute "
                 "WHERE nama_rute='%3' AND id_database=%4)").
            arg(rute_baru,QString::number(id_database),
            rute_baru,QString::number(id_database));
    if(!query.exec(qu)) {qDebug()<< "ERROR:: " <<query.lastError().text();}
    else{while(query.next()){
            id_rute_baru=query.lastInsertId().toInt();
            s_id_rute_baru=id_rute_baru;//new id rute
            qDebug()<<"id_rute baru tambah:"<<id_rute_baru<<rute_baru;
    }}

    qDebug()<<"------------cek eliminasi data awal----------";
    qDebug()<<"- jumlah data rute:"<<rute_baru;
    qDebug()<<"- jumlah data id_data_masuk:"<< id_data_masuk;//0
    qDebug()<<"- jumlah data id_param:"<< id_param;//1
    qDebug()<<"- jumlah data tipe_param:"<< tipe_param;//2
    qDebug()<<"- jumlah data id_rute:"<<id_rute;//3
    qDebug()<<"- jumlah data time:"<<time;//4
    qDebug()<<"- jumlah data siklus:"<<siklus;//5
    qDebug()<<"----------------------------------------";
//masukkan isi_rute dulu

    qu = QString("SELECT id FROM rute WHERE nama_rute='%1'").
            arg(rute_baru);
    if(!query.exec(qu)) {qDebug()<< "ERROR:: " <<query.lastError().text();}
    else{while(query.next()){
             id_rute_baru=query.value("id").toInt();
             s_id_rute_baru=id_rute_baru;//new id rute
             qDebug()<<"id_rute:"<<id_rute_baru <<rute_baru;
             QByteArray datax;
             datax.resize(100);
             QString qa;
                     qa.sprintf("INSERT INTO rute_isi (id_rute,id_tipe_param,id_last_param,kanal,param_setting)"
                                " SELECT :id_rute,:id_tipe_param,:id_last_param,:kanal,:param_setting "
                                "WHERE NOT EXISTS (SELECT id_rute,id_last_param FROM rute_isi "
                                "WHERE id_rute=:id_rute AND id_last_param=:id_last_param)");
                     query.exec("pragma synchronous = off;");
                     query.prepare(qa);
                     query.bindValue(":id_rute",id_rute_baru);
                     query.bindValue(":id_tipe_param",tipe_param);
                     query.bindValue(":id_last_param",id_param);
                     query.bindValue(":kanal",1);
                     query.bindValue(":param_setting",all_rute_param);
                     query.exec();
            }
        }
      qDebug()<<"rute baru cek"<<rute_baru;

    qu = QString("SELECT id FROM rute WHERE nama_rute='%1'").
            arg(rute_baru);
    if(!query.exec(qu)) {qDebug()<< "ERROR:: " <<query.lastError().text();}
    else{while(query.next()){
         id_rute_baru=query.value("id").toInt();
         s_id_rute_baru=id_rute_baru;//new id rute}
         qDebug()<<"tipe_data:"<<tipe_param;
         if(tipe_param==410 || tipe_param==420 || tipe_param==430||
            tipe_param==41 || tipe_param==42 || tipe_param==43){
             //tambahin id_isi_rute?

              QString tipe_data = get_table_name(tipe_param);
              QString qa;
              qa.sprintf("INSERT INTO %s (id_param,id_rute,data,flag_set_param,data_timestamp)"
                           " SELECT :id_param,:id_rute,:data,:flag_set_param,:data_timestamp "
                           "WHERE NOT EXISTS (SELECT id_rute,data_timestamp FROM %s "
                           "WHERE id_rute=:id_rute AND data_timestamp=:data_timestamp)",
                            tipe_data.toUtf8().data(),tipe_data.toUtf8().data());
                              query.exec("pragma synchronous = off;");
                              query.prepare(qa);
                              query.bindValue(":id_param",id_param);
                              query.bindValue(":id_rute",id_rute_baru);
                              query.bindValue(":data",all_data);
                              query.bindValue(":flag_set_param",0);
                              query.bindValue(":data_timestamp",time);
                              //query.exec();
                              if(!query.exec())return 0;
                              else return 1;
             //---------------------------------------------------------------//

        }
        else if(tipe_param==28 || tipe_param==3 ||tipe_param==2 || tipe_param==11){
             //tambahin siklus dan id_isi_rute?

             QString tipe_data = get_table_name(tipe_param);
             QString qStr;
             qStr.sprintf("insert into %s (id_param,id_rute, data, flag_set_param, data_timestamp, siklus) "
                          "values (:id_param, :id_rute, :data, :flag_set_param, :data_timestamp, :siklus)",tipe_data.toUtf8().data());
             query.exec("pragma synchronous = off;");
             query.prepare(qStr);
             query.bindValue(":id_param",id_param);
             query.bindValue(":id_rute", id_rute_baru);
             query.bindValue(":data", all_data);
             query.bindValue(":flag_set_param", 0);
             query.bindValue(":data_timestamp", time);
             query.bindValue(":siklus", siklus);

             if(!query.exec())return 0;
             else return 1;

             }
         }
    }

}


//QVector<int> validasi[3];

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int decode_fft_lines(int setting_lines )
{
    if ( setting_lines == FFT_LINES_DISABLE)
        return 0;
    else if (setting_lines == FFT_LINES_50)
        return 50;
    else if (setting_lines == FFT_LINES_100)
        return 100;
    else if (setting_lines == FFT_LINES_200)
        return 200;
    else if (setting_lines == FFT_LINES_400)
        return 400;
    else if (setting_lines == FFT_LINES_800)
        return 800;
    else if (setting_lines == FFT_LINES_1600)
        return 1600;
    else if (setting_lines == FFT_LINES_3200)
        return 3200;
    else if (setting_lines == FFT_LINES_6400)
        return 6400;
    else if (setting_lines == FFT_LINES_12800)
        return 12800;
    else
        return 0;
}
