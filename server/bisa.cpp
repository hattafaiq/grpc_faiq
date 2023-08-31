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
//data dirubah karena tidak efisien sehingga butuh info data aja untuk relasi aset dengan data info terdahulu
#include "bisa.h"
#include "strc.h"
//#include <grpcpp/grpcpp.h>
//struct data data_base;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using Cloud::protokol_1;
using Cloud::protokol_2;

//pesan kebutuhan kirim pesan data//
using Cloud::pesan_client;
//using Cloud::pesan_client_info_data;
using Cloud::pesan_server;
//using Cloud::pesan_server_info_data;

//pesan kebutuhan kirim pesan data//
using Cloud::mes_client;
//using Cloud::mes_client_isi_data;
//using Cloud::mes_client_info_data;
using Cloud::mes_server;
//using Cloud::mes_server_isi_data;
//using Cloud::mes_server_info_data;

class GreeterServiceImpl final : public protokol_1::Service  {
    public:
    //bisa b;
    controller *cc;
    Status initial_data(ServerContext* context, const pesan_client* request, pesan_server* reply) override {
        QStringList rute_s;
        QStringList cacah_data_aset;
        QVector<int> data_new[7];
        int id_database;
        cc = new controller;
        cc->database_connect();
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
            cc->eliminasi_data(
                    request->id_database(),
                    rute_s,
                    cacah_data_aset,
                    data_new[0],
                    data_new[1],
                    data_new[2],
                    data_new[3],
                    data_new[4],
                    data_new[5]);
            //-----------------------------------------//

            //---mulai kirim data yang belum ada-------//
//            qDebug()<<"---inisial data yang belom ada di server---";
//            for(int i=0; i<b.t_tipe_param.size(); i++){
//                qDebug()<<b.t_tipe_param[i]<<b.t_time[i]<<b.t_siklus[i];
//            }
            std::vector<int> id_data_masuk, id_param,id_tip_parm,id_rut,time,siklus;
            id_data_masuk = cc->t_id_data_masuk.toStdVector();
            id_param    = cc->t_id_param_lama.toStdVector();
            id_tip_parm = cc->t_tipe_param.toStdVector();
            id_rut      = cc->t_id_rute.toStdVector();
            time        = cc->t_time.toStdVector();
            siklus      = cc->t_siklus.toStdVector();

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
            for(int x=0; x<cc->list_aset.size(); x++){
                QString ay = cc->list_aset[x];
                QString rute = cc->list_rute[x];
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
//    bisa *b;
    controller *cc;
    Status kirim_data(ServerContext* context, const mes_client* request, mes_server* reply) override {
        std::cout <<"req pesan dari client diterima:->" << request->header_pesan() <<std::endl;
        if(request->header_pesan()=="kirim_data"){
            //cek dulu size nya;
            QByteArray all_data = QByteArray::fromStdString(request->data());
            QByteArray all_rute_param = QByteArray::fromStdString(request->param());
            std::cout<<"cek data_upload client:" <<
                          request->id_database()<< " "<<
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
                        int id_database = request->id_database();
                cc = new controller;
                if(cc->save_data(rute,
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
 // database_connect();
}

void bisa::RunServer() {
   // siapa.apa =9;

    GreeterServiceImpl service;
    GreeterServiceImpl2 service2;
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.

    builder.SetMaxSendMessageSize(1024 * 1024 * 1024);
    builder.SetMaxMessageSize(1024 * 1024 * 1024);
    builder.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    std::string server_address("127.0.0.1:50051");

    grpc::EnableDefaultHealthCheckService(true);
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



void bisa::mulai_cari_server(QSqlQuery *query)
{

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
