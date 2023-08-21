#include "data_proses.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ChannelArguments;
using Cloud::protokol_1;
using Cloud::pesan_client;
using Cloud::pesan_server;

struct data siapa;

class GreeterClient{
 public:
  data_proses k;
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(protokol_1::NewStub(channel)) {}
   std::string initial_data(const std::string& user) {
   // Tampil t_proses;
    pesan_client request;
    pesan_server reply;
    ClientContext context;


    request.set_header_pesan("list_info");

//    int flag=0;
//    if(!flag){
//        request.set_header_pesan("list_info");
//        flag=1;
//    }
    //------------tahap 1--------#
    //isi protokol 1;
    //client meminta list data dari server sambil mengirimkan data client;
    //server membalas list info server;
    //client menerima info yang tidak ada di server;
    //------------tahap 2--------#
    //client mengirkan daftar info yang hanya diinginkan oleh client 1 per satu datanya;

    //di klik sekali lalu lanjut ke pembagian pesan ketika posisi apa menerima fungsi apa disini!!

//    qDebug()<<"-------------berikut list datanya:";

    qDebug()<<"size info:"<<siapa.data_n[0].size()<<siapa.cacah_data_name.size();
    if(siapa.data_n[0].size()!=0){
        for(int a=0; a<siapa.data_n[0].size(); a++ ){
          QString ay = siapa.cacah_data_name[a];
          qDebug()<<ay<<
          "id_parm:"<<siapa.data_n[1][a]<<
          "id_tip_parm:"<<siapa.data_n[2][a]<<
          "id_rut:"<<siapa.data_n[3][a]<<
          "time:"<<siapa.data_n[4][a]<<
          "siklus"<<siapa.data_n[5][a];
        }
        std::vector<int> id_param,id_tip_parm,id_rut,time,siklus;//(data_n[0], n);
        id_param    = siapa.data_n[1].toStdVector();
        id_tip_parm = siapa.data_n[2].toStdVector();
        id_rut      = siapa.data_n[3].toStdVector();
        time        = siapa.data_n[4].toStdVector();
        siklus      = siapa.data_n[5].toStdVector();
        google::protobuf::RepeatedField<int> id_param_s(id_param.begin(), id_param.end());
        google::protobuf::RepeatedField<int> id_tip_parm_s(id_tip_parm.begin(), id_tip_parm.end());
        google::protobuf::RepeatedField<int> id_rut_s(id_rut.begin(), id_rut.end());
        google::protobuf::RepeatedField<int> time_s(time.begin(), time.end());
        google::protobuf::RepeatedField<int> siklus_s(siklus.begin(), siklus.end());
        request.mutable_id_param_lama()->Swap(&id_param_s);
        request.mutable_id_tipe_param()->Swap(&id_tip_parm_s);
        request.mutable_id_rute_lama()->Swap(&id_rut_s);
        request.mutable_timestamp()->Swap(&time_s);
        request.mutable_siklus()->Swap(&siklus_s);
    }
    else{
        qDebug()<<"tidak ada data client";
    }

    //Tampil setup_tampil_hirarki_server();

    Status status = stub_->initial_data(&context,request,&reply );

    if (status.ok()) {
       // if(reply.header_pesan()=="list_server"){
            std::cout << request.header_pesan() << std::endl;
            std::cout << reply.header_pesan() << std::endl;
       // }
      return reply.header_pesan();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<protokol_1::Stub> stub_;
};

void data_proses::kirim()
{
    setup_database();
    std::string server_address("127.0.0.1:50051");
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

    GreeterClient greeter( grpc::CreateCustomChannel (server_address, grpc::InsecureChannelCredentials(), ch_args));
    std::string user("world");
    std::string reply = greeter.initial_data(user);
    std::cout << "Greeter received: " << reply << std::endl;
}
data_proses::data_proses()
{

}

void data_proses::setup_database()
{
    QString filename = "rotatinghal.dbb";
    QString con_name;
    con_name = QString("LOC_DB%1").arg(1);
    db =QSqlDatabase::addDatabase("QSQLITE",con_name);
    db.setDatabaseName(filename);
    QSqlQuery buka(db);
    if(!db.open())
    {
      qDebug()<<"db gak kebukak";
      //return;
    }
    else{
        qDebug()<<"buka db"<<filename;
    }
    QString aa;
    //proses_q(query,"SELECT ALL id FROM parameter WHERE true");
    aa = QString("SELECT ALL id_database FROM info_db WHERE true");
    if(!buka.exec(aa)){qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<buka.lastError().text();}
    else{ while(buka.next()){
     //   text1 = "Daftar Semua Data Client ID:"+QString::number(buka.value("id_database").toInt());
        id_database = buka.value("id_database").toInt();
    }}
    mulai_cari(&buka);
}

void data_proses::mulai_cari(QSqlQuery *query)
{
    QVector<int> datax[4];
    QVector<int> data_[4];
    //mengecek keseluruhan data yang ada di data masuk
    QString qu;
            qu = QString("SELECT id,id_param,id_tipe_param,id_rute "
                 "FROM data_masuk"
                 " WHERE true");
    if(!query->exec(qu)){ qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();}
    else{while(query->next()){
        qDebug()<<query->value("id").toInt()
                <<query->value("id_param").toInt()
                <<query->value("id_tipe_param").toInt()
                <<query->value("id_rute").toInt();
        datax[0].push_back(query->value("id").toInt());
        datax[1].push_back(query->value("id_param").toInt());
        datax[2].push_back(query->value("id_tipe_param").toInt());
        datax[3].push_back(query->value("id_rute").toInt());
     }}

    //validasi ulang dari info rute apakah benar data masuk sesuai rute yang ada
    qu.clear();
    for(int i=0; i<datax[0].size(); i++){
        qu = QString("SELECT id_date "
             "FROM rute"
             " WHERE id=%1").arg(QString::number(datax[3][i]));
        if(!query->exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();
        else{while(query->next()){
            data_[0].push_back(datax[0][i]);
            data_[1].push_back(datax[1][i]);
            data_[2].push_back(datax[2][i]);
            data_[3].push_back(datax[3][i]);
         }}
    }

    //mulai cari data berdasarkan time stamp nya
    for(int i=0; i<data_[0].size(); i++){
        qu = QString("SELECT data,data_timestamp "
                    "FROM %1"
                    " WHERE id_param=%2 AND id_data_masuk=%3").arg(get_table_name(data_[2][i]),QString::number(data_[1][i]),QString::number(data_[0][i]));
     if(data_[2][i]==3 || data_[2][i]==28 || data_[2][i]==2|| data_[2][i]==11){
     qu = QString("SELECT data,data_timestamp,siklus "
                 "FROM %1"
                 " WHERE id_param=%2 AND id_data_masuk=%3").arg(get_table_name(data_[2][i]),QString::number(data_[1][i]),QString::number(data_[0][i]));
        }
    if(!query->exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();
    else{while(query->next()){
         all_data.append(query->value("data").toByteArray());
        qDebug()<<"tiem:"<<query->value("data_timestamp").toInt();
        siapa.data_n[0].push_back(data_[0][i]);//id_rute lama
        siapa.data_n[1].push_back(data_[1][i]);//id_param
        siapa.data_n[2].push_back(data_[2][i]);//id_tipe_param
        siapa.data_n[3].push_back(data_[3][i]);//id_rute
        siapa.data_n[4].push_back(query->value("data_timestamp").toInt());
        siapa.data_n[5].push_back(query->value("siklus").toInt());
     }}}

    for(int i=0; i<siapa.data_n[0].size(); i++){
    qu = QString("SELECT nama_rute "
                "FROM rute"
                " WHERE id=%1").arg(QString::number(siapa.data_n[3][i]));
   if(!query->exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();
   else{while(query->next()){
        rute_baru.push_back(query->value("nama_rute").toString());
        qDebug()<<"rute:"<<query->value("nama_rute").toString();
//        QString list_nama_asetku;
//         list_nama_asetku+=query->value("nama_rute").toString();//rute[info_tipe_data[0][i]];
//         list_nama_asetku+="/";
//         list_nama_asetku+= QString::number(data_n[1][i]);
//         list1 = new QLabel(this);
//         box1->addWidget(list1);
//         list1->setText(list_nama_asetku);
    }}}

//--------------------mode cari aset start-----------------------------------------------//
for(int i=0; i<siapa.data_n[0].size(); i++){
    cari_induk_paramm(siapa.data_n[1][i], siapa.data_n[2][i]);
}
//--------------------mode cari aset end-----------------------------------------------//


    //cari data rute_isi yang mau dipindahkan berdasarkan data yang exist
    //tujuannya untuk efisiensi jumlah data yang mau ditambahkan ke rute_isi
    //sehingga tidak semua isi rute dipindahkan langsung.

    for(int i=0; i<siapa.data_n[0].size(); i++){
        qu = QString("SELECT param_setting "
                    "FROM rute_isi"
                    " WHERE id_rute=%1 AND id_param=%2").arg(QString::number(siapa.data_n[3][i]),QString::number(siapa.data_n[1][i]));
           if(!query->exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();
           else{while(query->next()){
                qDebug()<<"list rute_isi"<<siapa.data_n[3][i]<<siapa.data_n[1][i]<<query->value("param_setting").toByteArray().size();
                all_rute_param.append(query->value("param_setting").toByteArray());
            }}
    }
    qDebug()<<"lapor size data_n"<< siapa.data_n[0].size() << siapa.data_n[1].size() <<siapa.data_n[2].size()<< siapa.data_n[3].size() << siapa.data_n[4].size();
}

QString data_proses::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
//    nama_tabel.sprintf("data_%d_tipe", tipe);
    return nama_tabel;
}

void data_proses::cari_induk(int p_id_aset){

    QSqlQuery Q3( db );
    QString nama;
    int id_aset_induk;
    int id_parent_ku;
    QString qu;
    qu = QString("SELECT * FROM aset WHERE id=%1").arg(p_id_aset);
    if(!Q3.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q3.lastError().text();
    else{
     while(Q3.next()){
        id_parent_ku = Q3.value("id_parent").toInt();
        nama = Q3.value("name").toString();
        qDebug()<<"parent:"<<id_parent_ku << "|nama:"<<nama;
        nama+="/";
        initial_rute.prepend(nama);
        if(id_parent_ku!=0){
            cari_induk(id_parent_ku);
        }
        else{
            siapa.cacah_data_name.push_back(initial_rute);
            qDebug()<<"ini"<<initial_rute;
          //  ui->lineEdit->backspace();
          //  ui->lineEdit->setText(initial_rute);
            initial_rute.clear();
            qDebug()<<"emit";
        }
     }
   }
}

void data_proses::cari_induk_paramm(int parameter, int tipe)
{
    QSqlQuery Q2( db );
    int id_aset_induk;
    int id_parent_ku;
    QString qu;
    qu = QString("SELECT id_aset FROM parameter WHERE id=%1").arg(parameter);
    if(!Q2.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q2.lastError().text();
    else
    {
        while (Q2.next())
        {
         id_aset_induk = Q2.value("id_aset").toInt();
         qDebug()<<"id_parent:"<<id_aset_induk;
         cari_induk(id_aset_induk);
      }
   }
}

