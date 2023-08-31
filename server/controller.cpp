#include "controller.h"

struct data data_base;
struct id_info_data info;

controller::controller()
{

}

int controller::save_data(QString  rute_baru,
                          QString cacah_data_name,
                          int id_data_masuk,
                          int id_last_param,
                          int tipe_param,
                          int id_rute,
                          int time,
                          int siklus,
                          int id_database,
                          QByteArray all_rute_param,
                          QByteArray all_data)
{
    //id_database=49965;
    QSqlQuery query(data_base.db);
    int id_param=0;
    id_data_info=0;
 //---------------------------------------------------------------------------------------------------//
    qDebug()<<"id paramnya size";
    id_param = simpan_aset(&query,
                rute_baru,
                cacah_data_name,
                id_data_masuk,
                id_last_param,
                tipe_param,
                id_rute,
                time, siklus,
                id_database,
                all_rute_param,
                all_data);

    int id_rute_baru=0;
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
    qDebug()<<"- jumlah data id_last_param:"<< id_last_param;//1
    qDebug()<<"- jumlah data tipe_param:"<< tipe_param;//2
    qDebug()<<"- jumlah data id_rute:"<<id_rute;//3
    qDebug()<<"- jumlah data time:"<<time;//4
    qDebug()<<"- jumlah data siklus:"<<siklus;//5
    qDebug()<<"----------------------------------------";

    //masukkan isi_rute dulu
//    if(siklus==1 || siklus==0){
//        //ini ditambahkan && tipe terkait
//        qu = QString("SELECT id FROM rute WHERE nama_rute='%1'").
//                arg(rute_baru);
//        if(!query.exec(qu)) {qDebug()<< "ERROR:: " <<query.lastError().text();}
//        else{while(query.next()){
//                 id_rute_baru=query.value("id").toInt();
//                 s_id_rute_baru=id_rute_baru;//new id rute
//                 qDebug()<<"id_rute:"<<id_rute_baru <<rute_baru;
//                 QString qa;
//                         qa.sprintf("INSERT INTO info_data (id_aset, id_last_param, id_tipe_param, id_last_date, id_last_data_masuk, kanal) "
//                                    "values(:id_aset, :id_last_param, :id_tipe_param, :id_last_date, :id_last_data_masuk, kanal)");
//                         query.exec("pragma synchronous = off;");
//                         query.prepare(qa);
//                         query.bindValue(":id_rute",id_rute_baru);
//                         query.bindValue(":id_aset",id_param);
//                         query.bindValue(":id_last_param",id_last_param);
//                         query.bindValue(":id_tipe_param",tipe_param);

//                         query.bindValue(":id_last_date",0);
//                         query.bindValue(":id_last_data_masuk",0);
//                         query.bindValue(":kanal",1);
//                         if(!query.exec()){

//                         }
//                         else{
//                           id_data_info= query.lastInsertId().toInt();
//                           last_data_info=id_data_info;
//                         }
//                }
//        }
//     }
////-------------------------------------------------------------------------------------------------------------------------------->>>>

    qu = QString("SELECT id FROM rute WHERE nama_rute='%1'").
            arg(rute_baru);
    if(!query.exec(qu)) {qDebug()<< "ERROR:: " <<query.lastError().text();}
    else{while(query.next()){
         id_rute_baru=query.value("id").toInt();
         s_id_rute_baru=id_rute_baru;//new id rute}
         qDebug()<<"tipe_data:"<<tipe_param;
         QString tipe_data = get_table_name(tipe_param);
         QString qa;

         if(siklus==1 || siklus==0){
             //ini ditambahkan && tipe terkait

              qa.sprintf("INSERT INTO info_data (id_rute, id_aset, id_last_param, id_tipe_param, id_last_date, id_last_data_masuk, kanal) "
                         "values(:id_rute, :id_aset, :id_last_param, :id_tipe_param, :id_last_date, :id_last_data_masuk, kanal)");
              query.exec("pragma synchronous = off;");
              query.prepare(qa);
              query.bindValue(":id_rute",id_rute_baru);
              query.bindValue(":id_aset",id_param);
              query.bindValue(":id_last_param",id_last_param);
              query.bindValue(":id_tipe_param",tipe_param);

              query.bindValue(":id_last_date",0);
              query.bindValue(":id_last_data_masuk",0);
              query.bindValue(":kanal",1);
              if(!query.exec()){}
              else{
                id_data_info= query.lastInsertId().toInt();
                info.id=id_data_info;
              }
          }

         if(tipe_param==410 || tipe_param==420 || tipe_param==430||
            tipe_param==41 || tipe_param==42 || tipe_param==43){
              qa.sprintf("INSERT INTO %s (id_info_data, data, set_param, siklus, data_timestamp, flag_set_param, info_rms, info_peak) "
                         "values(:id_info_data, :data, :set_param, :siklus, :data_timestamp, :flag_set_param, :info_rms, :info_peak)",
                            tipe_data.toUtf8().data());
                              query.exec("pragma synchronous = off;");
                              query.prepare(qa);
                              query.bindValue(":id_info_data",info.id);//id_info_data from last insert id info data
                              //query.bindValue(":id_rute",id_rute_baru);
                              query.bindValue(":data",all_data);
                              query.bindValue(":set_param",all_rute_param);
                              query.bindValue(":siklus",0);//jika dihapus lebih baik
                              query.bindValue(":data_timestamp",time);
                              query.bindValue(":flag_set_param",0); //ganti data asli ya nanti
                              query.bindValue(":info_rms",0.22);
                              query.bindValue(":info_peak",0.11);
                              //query.exec();
                              if(!query.exec())return 0;
                              else return 1;
             //---------------------------------------------------------------//
                              //metode nyimpennya minta di tread semua ya
                              //bisa contoh cara nyimpennya OVM
        }
        else if(tipe_param==28 || tipe_param==3 ||tipe_param==2 || tipe_param==11){

             qa.sprintf("INSERT INTO %s (id_info_data, data, set_param, siklus, data_timestamp, flag_set_param, info_rms, info_peak) "
                        "values(:id_info_data, :data, :set_param, :siklus, :data_timestamp, :flag_set_param, :info_rms, :info_peak)",
                           tipe_data.toUtf8().data());
                             query.exec("pragma synchronous = off;");
                             query.prepare(qa);
                             query.bindValue(":id_info_data",info.id);//id_info_data from last insert id info data
                             //query.bindValue(":id_rute",id_rute_baru);
                             query.bindValue(":data",all_data);
                             query.bindValue(":set_param",all_rute_param);
                             query.bindValue(":siklus",siklus);
                             query.bindValue(":data_timestamp",time);
                             query.bindValue(":flag_set_param",0); //ganti data asli ya nanti
                             query.bindValue(":info_rms",0.22);
                             query.bindValue(":info_peak",0.11);
                             //query.exec();
                             if(!query.exec())return 0;
                             else return 1;

             }
         }
    }
}

int controller::simpan_param(QSqlQuery *query, int id_paramnya, int flag_masukkan_param, int id_aset, int id_parent, QString rute_baru, QString cacah_data_name, int id_data_masuk, int id_param, int tipe_param, int id_rute, int time, int siklus, int id_database, QByteArray all_rute_param, QByteArray all_data)
{

    return id_param;
}

int controller::simpan_aset(QSqlQuery *query, QString rute_baru, QString cacah_data_name, int id_data_masuk, int id_param, int tipe_param, int id_rute, int time, int siklus, int id_database, QByteArray all_rute_param, QByteArray all_data)
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
    if(!flag_masukkan_param){
        id_param = id_parent;
    }
    else{
        id_param = id_aset;
    }

return id_param;
}

QString controller::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
    return nama_tabel;
}


void controller::eliminasi_data(int id_database, QStringList rute,QStringList aset, QVector<int> id_data_masuk1, QVector<int> id_param1, QVector<int> tipe_param1,QVector<int> id_rute1, QVector<int> time1, QVector<int> siklus1)
{
    QVector<int> id_data_masuk = id_data_masuk1;
    QVector<int> id_param = id_param1;
    QVector<int> tipe_param = tipe_param1;
    QVector<int> id_rute = id_rute1;
    QVector<int> time = time1;
    QVector<int> siklus = siklus1;
    QStringList cacah_data_aset = aset;


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
    controller *cc;
    cc = new controller;
    QSqlQuery query(data_base.db);
    int konter=0;
    QString qu;

//    qDebug()<<"-------------------------------clean dan detile-------------------------------------------------";
    //mungkin bisa disederhanakan lagi tapi masih belum tau caranya

    for(int i=0; i<id_param1.size(); i++){
        qu = QString("SELECT id_info_data "
                     "FROM %1 "
                     "WHERE data_timestamp=%2").arg(cc->get_table_name(tipe_param1[i]),QString::number(time1[i]));
                      //qDebug()<<qu;
                    if(!query.exec(qu)) {qDebug()<< "kenapa ERROR1:: " <<query.lastError().text();}
                    else{while(query.next()){
                            qu = QString("SELECT id_aset "
                                         "FROM info_data "
                                         "WHERE id=%1").arg(QString::number(query.value("id_info_data").toInt()));
                                      //  qDebug()<<qu;
                                        if(!query.exec(qu)) {qDebug()<< "kenapa ERROR2:: " <<query.lastError().text();}
                                        else{while(query.next()){
                                                qu = QString("SELECT id_database "
                                                             "FROM aset "
                                                             "WHERE id=%1").arg(QString::number(query.value("id_aset").toInt()));
                                                                if(!query.exec(qu)) {qDebug()<< "kenapa ERROR2:: " <<query.lastError().text();}
                                                                else{while(query.next()){
                                                                            if(query.value("id_database").toInt()==id_database){;
                                                                                rute.erase(rute.begin()+i-konter);
                                                                                id_data_masuk.erase(id_data_masuk.begin()+i-konter);
                                                                                id_param.erase(id_param.begin()+i-konter);
                                                                                tipe_param.erase(tipe_param.begin()+i-konter);
                                                                                id_rute.erase(id_rute.begin()+i-konter);
                                                                                time.erase(time.begin()+i-konter);
                                                                                siklus.erase(siklus.begin()+i-konter);
                                                                                cacah_data_aset.erase(cacah_data_aset.begin()+i-konter);
                                                                                konter+=1;
                                                                            }
                                                                }}
                                            }}
                        }}
    }

//    //ccek ulang yang tidak ada siapa aja
    qDebug()<<"------------cek sudah eliminasi data----------";
    qDebug()<<"- id database:"<<id_database;
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

void controller::database_connect()
{
    data_base.db = QSqlDatabase::addDatabase("QMYSQL");
    data_base.db.setHostName("127.0.0.1");//port 2121
    data_base.db.setDatabaseName("test");
    data_base.db.setUserName("root");
    data_base.db.setPassword("password");

    if (!data_base.db.open())
    {
      data_base.counter+=1;
      qDebug()<<"tidak bisa buka database???????----->"<<data_base.counter;
    }else{
        qDebug()<<"bisa";
    }
}
