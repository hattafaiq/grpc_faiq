
#include "controller.h"

controller::controller()
{

}

class GreeterClient{

 public:
    pesan_client request;
    pesan_server reply;
    ClientContext context;
    int alarm_pesan;
    QString s_pesan_alarm;
    QStringList list_data_tampil;
    QStringList list_rute;
    QVector<int> s_id_masuk;
    QVector<int> s_id_param_lama;
    QVector<int> s_tipe_param;
    QVector<int> s_id_rute_lama;
    QVector<int> s_time;
    QVector<int> s_siklus;


    GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(protokol_1::NewStub(channel)) {}
    std::string initial_data(const std::string& user) {
    std::cout <<"kirim request:"<< user <<std::endl;
    request.set_header_pesan(user);
    Status status = stub_->initial_data(&context,request,&reply );

    alarm_pesan=0;
    if (status.ok()) {
      //std::cout<<"req: "<<user<< "|rep:"<<reply.header_pesan()<<std::endl;
      alarm_pesan=0;
      return reply.header_pesan();
    } else {

      std::cout << status.error_code()<< ": "<< status.error_message()<< std::endl;
      alarm_pesan = (int) status.error_code();
      return "error- " + status.error_message();
    }
  }

   void pesan_pertama(int id_database, QStringList rute,QStringList aset, QVector<int> data0,QVector<int> data1, QVector<int> data2, QVector<int> data3, QVector<int> data4, QVector<int> data5){
       //qDebug()<<"pesan pertama"<<data2.size()<<data3.size()<<data4.size()<<data5.size();
       if(data1.size()!=0){
           for(int a=0; a<data1.size(); a++ ){
             QString ay = aset[a];
             QString rutes = (QString) rute[a];
             request.mutable_aset()->Add(ay.toStdString());
             request.mutable_rute()->Add(rutes.toStdString());
             qDebug()<<ay<<
             "id_parm:"<<data1[a]<<
             "id_tip_parm:"<<data2[a]<<
             "id_rut:"<<data3[a]<<
             "time:"<<data4[a]<<
             "siklus"<<data5[a]<<rutes;
           }

           std::vector<int> id_param,id_tip_parm,id_rut,time,siklus,id_masuk;//(data_n[0], n);
           std::string list_aset;
           id_masuk    = data0.toStdVector();
           id_param    = data1.toStdVector();
           id_tip_parm = data2.toStdVector();
           id_rut      = data3.toStdVector();
           time        = data4.toStdVector();
           siklus      = data5.toStdVector();
           std::cout <<id_masuk.size() <<id_param.size() << id_tip_parm.size() << id_rut.size() << time.size() << siklus.size() <<std::endl;
           google::protobuf::RepeatedField<int> id_masuk_s(id_masuk.begin(), id_masuk.end());
           google::protobuf::RepeatedField<int> id_param_s(id_param.begin(), id_param.end());
           google::protobuf::RepeatedField<int> id_tip_parm_s(id_tip_parm.begin(), id_tip_parm.end());
           google::protobuf::RepeatedField<int> id_rut_s(id_rut.begin(), id_rut.end());
           google::protobuf::RepeatedField<int> time_s(time.begin(), time.end());
           google::protobuf::RepeatedField<int> siklus_s(siklus.begin(), siklus.end());
           request.mutable_id_data_masuk()->Swap(&id_masuk_s);
           request.mutable_id_param_lama()->Swap(&id_param_s);
           request.mutable_id_tipe_param()->Swap(&id_tip_parm_s);
           request.mutable_id_rute_lama()->Swap(&id_rut_s);
           request.mutable_timestamp()->Swap(&time_s);
           request.mutable_siklus()->Swap(&siklus_s);

           request.set_id_database(id_database);
           request.set_header_pesan("list_info");
       }
       else{
           qDebug()<<"tidak ada data client";
       }
   }

   void proses_eliminasi(){
       for(int i=0; i<reply.aset_size(); i++){
           list_rute.push_back(QString::fromStdString(reply.rute(i)));
           list_data_tampil.push_back(QString::fromStdString(reply.aset(i)));
           s_id_masuk.push_back(reply.id_data_masuk(i));
           s_id_param_lama.push_back(reply.id_param_lama(i));
           s_tipe_param.push_back(reply.id_tipe_param(i));
           s_id_rute_lama.push_back(reply.id_rute_lama(i));
           s_time.push_back(reply.timestamp(i));
           s_siklus.push_back(reply.siklus(i));
           std::cout << reply.aset(i) << " "
                     << reply.id_param_lama(i) << " "
                     << reply.id_data_masuk(i) << " "
                     << reply.id_tipe_param(i)<< " "
                     << reply.id_rute_lama(i)<< " "
                     << reply.timestamp(i)<< " "
                     << reply.siklus(i)<< " "
                     << reply.rute(i) << " "
                     << std::endl;
       }
       std::cout << "terima data yang belum ada di server: "
           << reply.id_param_lama_size() << " "
           << reply.id_data_masuk_size() << " "
           << reply.id_tipe_param_size() << " "
           << reply.id_rute_lama_size() << " "
           << reply.timestamp_size() << " "
           << reply.siklus_size() << " "
           << reply.rute_size() << " "
           << std::endl;
   }

 private:
  std::unique_ptr<protokol_1::Stub> stub_;
};

class GreeterClient2{
 public:
    mes_client request;
    mes_server reply;
    int alarm_pesan;
    ClientContext context;
    GreeterClient2(std::shared_ptr<Channel> channel)
      : stub_(protokol_2::NewStub(channel)) {}
   std::string kirim_data(const std::string& user,
                          int id_database,
                          QString asets,
                          QString rute,
                          int s_id_param_lama,
                          int s_tipe_param,
                          int s_id_rute_lama,
                          int s_time,
                          int s_siklus,
                          QByteArray param_set,
                          QByteArray data,
                          int counter
                          ) {

      request.set_id_database(id_database);
      request.set_header_pesan(user);
      request.set_pesan_ke(counter);
      request.set_aset(asets.toStdString());
      request.set_rute(rute.toStdString());
      request.set_id_param_lama(s_id_param_lama);
      request.set_id_tipe_param(s_tipe_param);
      request.set_id_rute_lama(s_id_rute_lama);
      request.set_timestamp(s_time);
      request.set_siklus(s_siklus);
      request.set_param(param_set.data(), param_set.size());
      request.set_data(data.data(), data.size());
      Status status = stub_->kirim_data(&context,request,&reply );

     // qDebug()<<"-counter"<<counter;
      if (status.ok()) {
       //   std::cout<<"req: "<<user<< "|rep:"<<reply.header_pesan()<<std::endl;
         // qDebug()<<"req counter:"<<counter;
         // std::cout <<"reply pesan:"<< reply.pesan_ke() << std::endl;
        return reply.header_pesan();
      } else {
        alarm_pesan = (int) status.error_code();
        std::cout << status.error_code()
                  << ": "
                  << status.error_message()
                  << std::endl;
        return "error - " + status.error_message();
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
         cari_induk(id_aset_induk);
      }
   }
}

void controller::emit_gas_kirim(int counter, int maks)
{
    std::string server_address("127.0.0.1:50051");
    if(counter>=maks){
        flag_emit_cukup=1;
    }
    else{
    CallServer("kirim_data",2,server_address,counter,maks);}
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
        data_n[0].push_back(data_[0][i]);//data masuk lama
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
    }}}

//--------------------mode cari aset start-----------------------------------------------//
for(int i=0; i<data_n[0].size(); i++){
    cari_induk_paramm(data_n[1][i], data_n[2][i]);
}
//--------------------mode cari aset end-----------------------------------------------//
    for(int i=0; i<data_->size(); i++){
        data_[i].clear();}
    for(int i=0; i<datax->size(); i++){
        datax[i].clear();}
    qDebug()<<"data size:"<<data_[0].size()<<data_[1].size()<<data_[2].size()<<data_[3].size();
}

void controller::CallServer(std::string header, int flag, std::string server_alamat, int counter, int jumlah)
{
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

//    qDebug()<<"cek dulu----"
//           <<cacah_data_name.size()
//            <<data_n[0].size()
//              <<data_n[1].size()
//                <<data_n[2].size()
//                  <<data_n[3].size()
//                    <<data_n[4].size()
//                      <<data_n[5].size()
//                     <<"----";
 if(flag ==1){
    GreeterClient greeter( grpc::CreateCustomChannel (server_alamat, grpc::InsecureChannelCredentials(), ch_args));
    std::cout <<"client:"<<header <<std::endl;
    qDebug()<<rute_baru.size();//note c_rute masih kosong
    if(flag_sukses==0)greeter.pesan_pertama(id_database, rute_baru,cacah_data_name,data_n[0],data_n[1],data_n[2],data_n[3],data_n[4],data_n[5]);
    std::string balasan = greeter.initial_data(header);
    alarm_message=0;
    alarm_message_data=0;
    if(greeter.alarm_pesan!=0){
        alarm_message = greeter.alarm_pesan;
        isi_pesan();
    }

    if(balasan=="balas"){
        counter_pesan=0;
        counter_reload=0;
        flag_sukses=1;

        //ini maksudnya mengumpulkan data yang sudah di eliminasi server
        //atau data yang tidak ada diserver
        greeter.proses_eliminasi();

        //dipindah data yang sudah dikumpulkan dari balasan server
        c_rute = greeter.list_rute;
        aset_info_server = greeter.list_data_tampil;
        c_id_param_lama = greeter.s_id_param_lama;
        c_tipe_param = greeter.s_tipe_param;
        c_id_rute_lama = greeter.s_id_rute_lama;
        c_time = greeter.s_time;
        c_siklus = greeter.s_siklus;
        c_id_masuk_lama = greeter.s_id_masuk;

        //cari setting param
        QSqlQuery query(db);
        for(int i=0; i<c_id_rute_lama.size(); i++){
            QString qu;
            qu = QString("SELECT param_setting FROM rute_isi"
                        " WHERE id_rute=%1 AND id_param=%2").arg(QString::number(c_id_rute_lama[i]),QString::number(c_id_param_lama[i]));
               if(!query.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query.lastError().text();
               else{while(query.next()){
                    c_all_rute_param.append(query.value("param_setting").toByteArray());
                }}

            qu = QString("SELECT data FROM %1 WHERE id_param=%2 AND id_data_masuk=%3")
                           .arg(get_table_name(c_tipe_param[i]),QString::number(c_id_param_lama[i]),QString::number(c_id_masuk_lama[i]));

              if(!query.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<query.lastError().text();
              else{while(query.next()){
                   c_all_data.append(query.value("data").toByteArray());
                  }}
          }
        qDebug()<<"cek size setelah eliminasi:"<<
                 c_rute.size()<<
                 aset_info_server.size()<<
                 c_id_param_lama.size()<<
                 c_tipe_param.size()<<
                 c_id_rute_lama.size()<<
                 c_time.size()<<
                 c_siklus.size()<<
                 c_id_masuk_lama.size()<<
                 c_all_data.size()<<
                 c_all_rute_param.size();

        //proses seleksi nama per siklus menjadi 1 silinder saja
        QString nama_aset;
        for(int i=0; i<greeter.list_data_tampil.size(); i++){
            qDebug()<< (QString) greeter.list_data_tampil[i];
            QString nama = (QString) greeter.list_data_tampil[i];
            if(nama!=nama_aset){
            aset_info_tampil.push_back(nama);}
            nama_aset= (QString) greeter.list_data_tampil[i];
        }
        std::cout<< "------------balas"<<std::endl;
    }
 }
 else if(flag == 2){
     //int count=0;
     GreeterClient2 greeter( grpc::CreateCustomChannel (server_alamat, grpc::InsecureChannelCredentials(), ch_args));
     std::string balasan;

     if(greeter.alarm_pesan!=0){
         alarm_message = greeter.alarm_pesan;
         isi_pesan();
     }

     balasan = greeter.kirim_data(header,
                                  id_database,
                                 (QString) aset_info_server[counter_pesan],
                                  (QString) c_rute[counter_pesan],
                                   c_id_param_lama[counter_pesan],
                                    c_tipe_param[counter_pesan],
                                     c_id_rute_lama[counter_pesan],
                                      c_time[counter_pesan],
                                       c_siklus[counter_pesan],
                                         c_all_rute_param[counter_pesan],
                                          c_all_data[counter_pesan],
                                          counter_pesan
                                   );
     std::cout <<"reply dari server:->"<< balasan << std::endl;
     if(balasan=="terima_data"){//lanjutkan kirim data loop
        qDebug()<<"- setelah direply server, lanjut kirim data ke-->"<<counter_pesan << c_all_rute_param[counter_pesan].size() << c_all_data[counter_pesan].size();
        counter_reload=0;
        flag_sukses=1;
        counter_pesan += 1;
        last_conter = counter_pesan;
        if(!flag_emit_cukup)emit_gas_kirim(counter_pesan,c_id_param_lama.size());
        else{
            qDebug()<<"sudah selesai upload semua data sejumlah="<<c_id_param_lama.size();
        }
     }
     else if(balasan=="reload") {
         qDebug()<<"- setelah direply server, lanjut kirim data ke-->"<<last_conter << c_all_rute_param[last_conter].size() << c_all_data[counter_pesan].size();
         flag_sukses=1;
         counter_reload+=1;
         std::string server_address("127.0.0.1:50051");
         if(counter_reload==1) qDebug()<<"sudah client stop dulu!!!";//CallServer("kirim_data",3,server_address,0,0);
//         if(!flag_emit_cukup)emit_gas_kirim(last_conter,c_id_param_lama.size());
//         else{
//             qDebug()<<"sudah selesai upload semua data sejumlah="<<c_id_param_lama.size();
//         }
     }
 }
}

void controller::isi_pesan()
{
    switch (alarm_message){
        case GRPC_STATUS_CANCELLED:
            pesan_alarm = "GRPC_STATUS_CANCELLED";//
            qDebug()<<"GRPC_STATUS_CANCELLED";
            break;
        case GRPC_STATUS_UNKNOWN:
            pesan_alarm ="GRPC_STATUS_UNKNOWN";//tanpa respon
            qDebug()<<"GRPC_STATUS_UNKNOWN";
            break;
        case GRPC_STATUS_INVALID_ARGUMENT:
            pesan_alarm ="GRPC_STATUS_INVALID_ARGUMENT";
            qDebug()<<"GRPC_STATUS_INVALID_ARGUMENT";
            break;
        case GRPC_STATUS_DEADLINE_EXCEEDED:
            pesan_alarm ="GRPC_STATUS_DEADLINE_EXCEEDED";//timeout
            qDebug()<<"GRPC_STATUS_DEADLINE_EXCEEDED";
            break;
        case GRPC_STATUS_NOT_FOUND:
            pesan_alarm ="GRPC_STATUS_NOT_FOUND";
            qDebug()<<"GRPC_STATUS_NOT_FOUND";
            break;
        case GRPC_STATUS_ALREADY_EXISTS:
            pesan_alarm ="GRPC_STATUS_ALREADY_EXISTS";
            qDebug()<<"GRPC_STATUS_ALREADY_EXISTS";
            break;
        case GRPC_STATUS_PERMISSION_DENIED:
            pesan_alarm ="GRPC_STATUS_PERMISSION_DENIED";
            qDebug()<<"GRPC_STATUS_PERMISSION_DENIED";
            break;
        case GRPC_STATUS_UNAUTHENTICATED:
            pesan_alarm ="GRPC_STATUS_UNAUTHENTICATED";
            qDebug()<<"GRPC_STATUS_UNAUTHENTICATED";
            break;
        case GRPC_STATUS_RESOURCE_EXHAUSTED:
            pesan_alarm ="GRPC_STATUS_RESOURCE_EXHAUSTED";
            qDebug()<<"GRPC_STATUS_RESOURCE_EXHAUSTED";
            break;
        case GRPC_STATUS_FAILED_PRECONDITION:
            pesan_alarm ="GRPC_STATUS_FAILED_PRECONDITION";
            qDebug()<<"GRPC_STATUS_FAILED_PRECONDITION";
            break;
        case GRPC_STATUS_ABORTED:
            pesan_alarm ="GRPC_STATUS_ABORTED";
            qDebug()<<"GRPC_STATUS_ABORTED";
            break;
        case GRPC_STATUS_OUT_OF_RANGE:
            pesan_alarm ="GRPC_STATUS_OUT_OF_RANGE";
            qDebug()<<"GRPC_STATUS_OUT_OF_RANGE";
            break;
        case GRPC_STATUS_UNIMPLEMENTED:
            pesan_alarm ="GRPC_STATUS_UNIMPLEMENTED";
            qDebug()<<"GRPC_STATUS_UNIMPLEMENTED";
            break;
        case GRPC_STATUS_INTERNAL:
            pesan_alarm ="GRPC_STATUS_INTERNAL";
            qDebug()<<"GRPC_STATUS_INTERNAL";
            break;
        case GRPC_STATUS_UNAVAILABLE:
            pesan_alarm ="GRPC_STATUS_UNAVAILABLE";//alamat tidak ditemukan
            qDebug()<<"GRPC_STATUS_UNAVAILABLE";
            break;
        case 15:
            pesan_alarm ="GRPC_STATUS_DATA_LOSS";
            qDebug()<<"GRPC_STATUS_DATA_LOSS";
            break;
        default:
            qDebug()<<"GRPC STATUS OK == terkirim";
    }
}

void controller::initial_database()
{
    // flag_pengiriman=0;
     QString filename = "rotatinghal.dbb";
//    QString filename = "QC_custom.dbb";

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
