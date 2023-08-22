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

#include "bisa.h"
#include "strc.h"
//#include <grpcpp/grpcpp.h>
struct data siapa;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using Cloud::protokol_1;

using Cloud::pesan_client;
using Cloud::pesan_server;

class GreeterServiceImpl final : public protokol_1::Service  {
    public:
    bisa b;
   // Cloud::protokol_1::AsyncService service;
    Status initial_data(ServerContext* context, const pesan_client* request, pesan_server* reply) override {
        int flag_pesan=0;

        if(request->header_pesan()=="list_info"){
            qDebug()<<"-------------------------";
            qDebug()<<"client:"<<"list info";
            qDebug()<<"server:"<<"balas";
            reply->set_header_pesan("balas");
            //return Status::OK;
        }
        else if(request->header_pesan()=="balas1"){
            qDebug()<<"-------------------------";
            qDebug()<<"client:"<<"balas1";
            qDebug()<<"server:"<<"balas2";
            reply->set_header_pesan("balas2");
        }
        else if(request->header_pesan()=="sudah1"){
            qDebug()<<"-------------------------";
            qDebug()<<"client:"<<"sudah1";
            qDebug()<<"server:"<<"sudah2";
            reply->set_header_pesan("sudah2");
        }
        else if(request->header_pesan()=="finish1"){
            qDebug()<<"-------------------------";
            qDebug()<<"client:"<<"finish1";
            qDebug()<<"server:"<<"finish2";
            reply->set_header_pesan("finish2");
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
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.

    builder.SetMaxSendMessageSize(1024 * 1024 * 1024);
    builder.SetMaxMessageSize(1024 * 1024 * 1024);
    builder.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    std::string server_address("127.0.0.1:50051");


//    grpc::EnableDefaultHealthCheckService(true);
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

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
    //---metode pengirimannya seperti apa?

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

void bisa::eliminasi_data(QVector<int> id_param1, QVector<int> tipe_param1,QVector<int> id_rute1, QVector<int> time1, QVector<int> siklus1)
{
    QVector<int> id_param=id_param1;
    QVector<int> tipe_param=tipe_param1;
    QVector<int> id_rute=id_rute1;
    QVector<int> time=time1;
    QVector<int> siklus=siklus1;
    QSqlDatabase dbx;
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
    qDebug()<<"- jumlah data id_param:"<< id_param.size();//1
    qDebug()<<"- jumlah data tipe_param:"<< tipe_param.size();//2
    qDebug()<<"- jumlah data id_rute:"<<id_rute.size();//3
    qDebug()<<"- jumlah data time:"<<time.size();//4
    qDebug()<<"- jumlah data siklus:"<<siklus.size();//5
    qDebug()<<"----------------------------------------";
    for(int i=0; i<id_param.size(); i++){
        qDebug()<<"cek data:"<<tipe_param[i]<<time[i]<<siklus[i];
    }
    QSqlQuery query(dbx);
    int konter=0;
    int flag_count=0;
    QString qu;
    for(int i=0; i<id_param1.size(); i++){
        //qDebug()<<"2cek data:"<<tipe_param[i]<<time[i]<<siklus[i];
        qu = QString("SELECT id FROM %1 WHERE data_timestamp=%2").arg(get_table_name(tipe_param1[i]),QString::number(time1[i]));
        if(tipe_param1[i]==3 || tipe_param1[i]==28 ||tipe_param1[i]==2|| tipe_param1[i]==11){
         qu = QString("SELECT id FROM %1 WHERE data_timestamp=%2 AND siklus=%3").arg(get_table_name(tipe_param1[i]),QString::number(time1[i]),QString::number(siklus1[i]));
        }
        if(!query.exec(qu)) {}//qDebug()<< "kenapa ERROR:: " <<query.lastError().text();}
        else{while(query.next()){
            if(flag_count==0){
                id_param.erase(id_param.begin()+i);
                tipe_param.erase(tipe_param.begin()+i);
                id_rute.erase(id_rute.begin()+i);
                time.erase(time.begin()+i);
                siklus.erase(siklus.begin()+i);

//                all_rute_param.erase(all_rute_param.begin()+i);
//                rute_baru.erase(rute_baru.begin()+i);
//                all_data.erase(all_data.begin()+i);
//                cacah_data_name.erase(cacah_data_name.begin()+i);
                flag_count+=1;
            }
            else{
                konter+=1;
                id_param.erase(id_param.begin()+i-konter);
                tipe_param.erase(tipe_param.begin()+i-konter);
                id_rute.erase(id_rute.begin()+i-konter);
                time.erase(time.begin()+i-konter);
                siklus.erase(siklus.begin()+i-konter);
//                all_rute_param.erase(all_rute_param.begin()+i-konter);
//                rute_baru.erase(rute_baru.begin()+i-konter);
//                all_data.erase(all_data.begin()+i-konter);
//                cacah_data_name.erase(cacah_data_name.begin()+i-konter);
            }}}
    }

//    //ccek ulang yang tidak ada siapa aja
    qDebug()<<"------------cek sudah eliminasi data----------";
    qDebug()<<"- jumlah data id_param:"<< id_param.size();//1
    qDebug()<<"- jumlah data tipe_param:"<< tipe_param.size();//2
    qDebug()<<"- jumlah data id_rute:"<<id_rute.size();//3
    qDebug()<<"- jumlah data time:"<<time.size();//4
    qDebug()<<"- jumlah data siklus:"<<siklus.size();//5
    qDebug()<<"----------------------------------------";
    for(int a=0; a<id_param.size(); a++){
        qDebug()<<tipe_param[a]
                <<id_rute[a]
                <<time[a]
                <<siklus[a];
    }


}

void bisa::mulai()
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
