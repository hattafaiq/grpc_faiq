#include "controller.h"

controller::controller()
{

}

class GreeterClient{
private:
//    extern struct T dat;

 public:
    pesan_client request;
    pesan_server reply;
    mes_client mes_request;
    mes_server mes_reply;
    ClientContext context;
    GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(protokol_1::NewStub(channel)) {}
   std::string initial_data(const std::string& user) {

    std::cout <<"minta:"<< user <<std::endl;
    request.set_header_pesan(user);
    Status status = stub_->initial_data(&context,request,&reply );
    //qDebug()<<"pesan 0 user:"<<data_n[0].size()<<data_n[1].size()<<data_n[2].size()<<data_n[3].size();
    if (status.ok()) {
        std::cout<<"req: "<<user<< "|rep:"<<reply.header_pesan()<<std::endl;
        //qDebug()<<"pesan user:"<<data_n[0].size()<<data_n[1].size()<<data_n[2].size()<<data_n[3].size();
      return reply.header_pesan();
    } else {
      std::cout << status.error_code()
                << ": "
                << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

   void pesan_pertama(QStringList aset, QVector<int> data1, QVector<int> data2, QVector<int> data3, QVector<int> data4, QVector<int> data5){
       //qDebug()<<"pesan pertama"<<data2.size()<<data3.size()<<data4.size()<<data5.size();
       if(data1.size()!=0){
           for(int a=0; a<data1.size(); a++ ){
             QString ay = aset[a];
             request.mutable_aset()->Add(ay.toStdString());
             qDebug()<<ay<<
             "id_parm:"<<data1[a]<<
             "id_tip_parm:"<<data2[a]<<
             "id_rut:"<<data3[a]<<
             "time:"<<data4[a]<<
             "siklus"<<data5[a];
           }

           std::vector<int> id_param,id_tip_parm,id_rut,time,siklus;//(data_n[0], n);
           std::string list_aset;
           id_param    = data1.toStdVector();
           id_tip_parm = data2.toStdVector();
           id_rut      = data3.toStdVector();
           time        = data4.toStdVector();
           siklus      = data5.toStdVector();
           std::cout <<id_param.size() << id_tip_parm.size() << id_rut.size() << time.size() << siklus.size() <<std::endl;
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

           request.set_header_pesan("list_info");
           id_param.clear();
           id_tip_parm.clear();
           id_rut.clear();
           time.clear();
           siklus.clear();
           data1.clear();
           data2.clear();
           data3.clear();
           data4.clear();
           data5.clear();
       }
       else{
           qDebug()<<"tidak ada data client";
       }
   }

   void pesan_kedua(){
       for(int i=0; i<reply.aset_size(); i++){
           std::cout << reply.aset(i) << " "
                     << reply.id_param_lama(i) << " "
                     << reply.id_tipe_param(i)<< " "
                     << reply.id_rute_lama(i)<< " "
                     << reply.timestamp(i)<< " "
                     << reply.siklus(i)<< " "
                     << std::endl;
       }
       std::cout << "terima data yang belum ada di server: " <<reply.id_param_lama_size() << " "
           << reply.id_param_lama_size() << " "
           << reply.id_tipe_param_size() << " "
           << reply.id_rute_lama_size() << " "
           << reply.timestamp_size() << " "
           << reply.siklus_size() << " "
           << std::endl;
   }

 private:
  std::unique_ptr<protokol_1::Stub> stub_;
};

class GreeterClient2 : public controller{
 public:
    mes_client request;
    mes_server reply;
    ClientContext context;
    GreeterClient2(std::shared_ptr<Channel> channel)
      : stub_(protokol_2::NewStub(channel)) {}
   std::string kirim_data(const std::string& user) {
      request.set_header_pesan(user);
      Status status = stub_->kirim_data(&context,request,&reply );

      if (status.ok()) {
          std::cout<<"req: "<<user<< "|rep:"<<reply.header_pesan()<<std::endl;
        return reply.header_pesan();
      } else {
        std::cout << status.error_code()
                  << ": "
                  << status.error_message()
                  << std::endl;
        return "RPC failed";
      }
   }
 private:
    std::unique_ptr<protokol_2::Stub> stub_;
};

QString controller::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
//    nama_tabel.sprintf("data_%d_tipe", tipe);
    return nama_tabel;
}


void controller::cari_induk_paramm(int parameter, int tipe)
{
    int id_aset_induk;
    QSqlQuery Q2(db);
   // int id_parent_ku;
    QString qu;
    qu = QString("SELECT id_aset FROM parameter WHERE id=%1").arg(parameter);
    if(!Q2.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q2.lastError().text();
    else
    {
        while (Q2.next())
        {
         id_aset_induk = Q2.value("id_aset").toInt();
        // qDebug()<<"id_parent:"<<id_aset_induk;
         cari_induk(id_aset_induk);
      }
    }
}

void controller::cari_induk_param(int p_id_aset)
{
    //dia harus dipanggil di tree select ya
   QSqlQuery Q2( db );
    int id_aset_induk;

    QString qu;

    qu = QString("SELECT id_aset FROM parameter WHERE id=%1").arg(p_id_aset);
    if(!Q2.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q2.lastError().text();
    else
    {
        while (Q2.next())
        {
         id_aset_induk = Q2.value("id_aset").toInt();
      //   qDebug()<<"parent1:"<<id_aset_induk;
         cari_induk(id_aset_induk);
      }
   }

}

void controller::cari_induk(int p_id_aset)
{
    QSqlQuery Q3( db );
    QString nama;
    int id_parent_ku;
    QString qu;
    qu = QString("SELECT * FROM aset WHERE id=%1").arg(p_id_aset);
    if(!Q3.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q3.lastError().text();
    else{
     while(Q3.next()){
        id_parent_ku = Q3.value("id_parent").toInt();
        nama = Q3.value("name").toString();
      //  qDebug()<<"parent:"<<id_parent_ku << "|nama:"<<nama;
        nama+="/";
        initial_rute.prepend(nama);
        if(id_parent_ku!=0){
            cari_induk(id_parent_ku);
        }
        else{
            cacah_data_name.push_back(initial_rute);
        //    qDebug()<<"ini"<<initial_rute;
          //  ui->lineEdit->backspace();
          //  ui->lineEdit->setText(initial_rute);
            initial_rute.clear();
          //  qDebug()<<"emit";
        }
     }
   }
}

void controller::mulai_cari(QSqlQuery *query)
{
    for(int i=1; i<data_n->size(); i++){
        data_n[i].clear();
    }
    qDebug()<<"cek 0:"<<data_n[0].size() <<data_n[1].size()<<data_n[2].size()
            <<data_n[3].size()<<data_n[4].size()<<data_n[5].size();
//    conter_loop=+1;
    QVector<int> datax[4];
    QVector<int> data_[4];

    //mengecek keseluruhan data yang ada di data masuk
    QString qu;
            qu = QString("SELECT id,id_param,id_tipe_param,id_rute "
                 "FROM data_masuk"
                 " WHERE true");
    if(!query->exec(qu)){ qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();}
    else{while(query->next()){
//        qDebug()<<query->value("id").toInt()
//                <<query->value("id_param").toInt()
//                <<query->value("id_tipe_param").toInt()
//                <<query->value("id_rute").toInt();
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

//    qDebug()<<"conter: "<<conter_loop <<" cek semua data sementara"
//           <<data_[0].size()<<data_[1].size()<<data_[2].size()<<data_[3].size();

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
       // qDebug()<<"tiem:"<<query->value("data_timestamp").toInt();
        data_n[0].push_back(data_[0][i]);//id_rute lama
        data_n[1].push_back(data_[1][i]);//id_param
        data_n[2].push_back(data_[2][i]);//id_tipe_param
        data_n[3].push_back(data_[3][i]);//id_rute
        data_n[4].push_back(query->value("data_timestamp").toInt());
        if(data_[2][i]==3 || data_[2][i]==28 || data_[2][i]==2|| data_[2][i]==11){
        data_n[5].push_back(query->value("siklus").toInt());}
        else{
            data_n[5].push_back(0);
        }
     }}}
    qDebug()<<"cek semua data yang dikumpulkan"
           <<data_n[0].size()<<data_n[1].size()<<data_n[2].size()<<data_n[3].size()
             <<data_n[4].size()<<data_n[5].size();

    for(int i=0; i<data_n[0].size(); i++){
    qu = QString("SELECT nama_rute "
                "FROM rute"
                " WHERE id=%1").arg(QString::number(data_n[3][i]));
   if(!query->exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();
   else{while(query->next()){
        rute_baru.push_back(query->value("nama_rute").toString());
 //       qDebug()<<"rute:"<<query->value("nama_rute").toString();
//        QString list_nama_asetku;
//         list_nama_asetku+=query->value("nama_rute").toString();//rute[info_tipe_data[0][i]];
//         list_nama_asetku+="/";
//         list_nama_asetku+= QString::number(data_n[1][i]);
//         list1 = new QLabel(this);
//         box1->addWidget(list1);
//         list1->setText(list_nama_asetku);
    }}}

//--------------------mode cari aset start-----------------------------------------------//
for(int i=0; i<data_n[0].size(); i++){
    cari_induk_paramm(data_n[1][i], data_n[2][i]);
}
//--------------------mode cari aset end-----------------------------------------------//


    //cari data rute_isi yang mau dipindahkan berdasarkan data yang exist
    //tujuannya untuk efisiensi jumlah data yang mau ditambahkan ke rute_isi
    //sehingga tidak semua isi rute dipindahkan langsung.

    for(int i=0; i<data_n[0].size(); i++){
        qu = QString("SELECT param_setting "
                    "FROM rute_isi"
                    " WHERE id_rute=%1 AND id_param=%2").arg(QString::number(data_n[3][i]),QString::number(data_n[1][i]));
           if(!query->exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query->lastError().text();
           else{while(query->next()){
           //     qDebug()<<"list rute_isi"<<data_n[3][i]<<data_n[1][i]<<query->value("param_setting").toByteArray().size();
                all_rute_param.append(query->value("param_setting").toByteArray());
            }}
    }
    for(int i=0; i<data_->size(); i++){
        data_[i].clear();}
    for(int i=0; i<datax->size(); i++){
    datax[i].clear();}
    qDebug()<<"data size:"<<data_[0].size()<<data_[1].size()<<data_[2].size()<<data_[3].size();
}

void controller::CallServer(std::string pesan, int flag, std::string server_alamat)
{
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);
    GreeterClient greeter( grpc::CreateCustomChannel (server_alamat, grpc::InsecureChannelCredentials(), ch_args));
    std::cout <<"client:"<<pesan <<std::endl;
    if(flag_sukses==0)greeter.pesan_pertama(cacah_data_name,data_n[1],data_n[2],data_n[3],data_n[4],data_n[5]);
    std::string balasan = greeter.initial_data(pesan);
    qDebug()<<"---------------------------------------------------------------------KK"
            <<cacah_data_name.size()
            <<data_n[0].size()
              <<data_n[1].size()
                <<data_n[2].size()
                  <<data_n[3].size()
                    <<data_n[4].size()
                      <<data_n[5].size();
//    cacah_data_name.clear();
//    for(int i=0; i<cacah_data_name.size(); i++){
//        data_n[i].clear();
//        qDebug()<<"->data:"<<data_n[i].size();
//    }
    if(balasan=="balas"){
        flag_sukses=1;
        greeter.pesan_kedua();
        std::cout<< "------------balas"<<std::endl;
    }
//    else if(balasan=="balas2"){
//        GreeterClient2 greeter2( grpc::CreateCustomChannel (server_alamat, grpc::InsecureChannelCredentials(), ch_args));
//        std::string balasin = greeter2.kirim_data("oiiik");
//        std::cout <<"struct 2 server:"<<balasin <<std::endl;
//        flag_sukses=2;
//        std::cout<< "------------balas"<<std::endl;
//    }
//    else if(balasan=="sudah2"){
//        flag_sukses=3;
//        std::cout<< "------------sudah"<<std::endl;
//    }
//    else if(balasan=="finish2"){
//        flag_sukses=4;
//        std::cout<< "------------finish"<<std::endl;
//    }

}

void controller::initial_database()
{
    // flag_pengiriman=0;
     QString filename = "rotatinghal.dbb";
     QString con_name;
     con_name = QString("LOC_DB%1").arg(2);
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
