#include "controller.h"

struct data data_base;

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
    int id_data_info=0;
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
    qDebug()<<"- jumlah data id_last_param:"<< id_last_param;//1
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
             QString qa;
                     qa.sprintf("INSERT INTO info_data (id_aset, id_last_param, id_tipe_param, info_rms, info_peak, id_last_date, id_last_data_masuk, kanal) "
                                "values(:id_aset, :id_last_param, :id_tipe_param, :info_rms, :info_peak, :id_last_date, :id_last_data_masuk, kanal)");
                     query.exec("pragma synchronous = off;");
                     query.prepare(qa);
                     query.bindValue(":id_aset",id_rute_baru);
                     query.bindValue(":id_last_param",id_last_param);
                     query.bindValue(":id_tipe_param",tipe_param);

                     query.bindValue(":info_rms",0.22);
                     query.bindValue(":info_peak",0.11);
                     query.bindValue(":id_last_date",0);
                     query.bindValue(":id_last_data_masuk",0);
                     query.bindValue(":kanal",1);

                     if(!query.exec()){

                     }
                     else{
                       id_data_info= query.lastInsertId().toInt();
                     }
                     //
            }
        }
//      qDebug()<<"rute baru cek"<<rute_baru;
//-------------------------------------------------------------------------------------------------------------------------------->>>>

    qu = QString("SELECT id FROM rute WHERE nama_rute='%1'").
            arg(rute_baru);
    if(!query.exec(qu)) {qDebug()<< "ERROR:: " <<query.lastError().text();}
    else{while(query.next()){
         id_rute_baru=query.value("id").toInt();
         s_id_rute_baru=id_rute_baru;//new id rute}
         qDebug()<<"tipe_data:"<<tipe_param;
         QString tipe_data = get_table_name(tipe_param);
         QString qa;
         if(tipe_param==410 || tipe_param==420 || tipe_param==430||
            tipe_param==41 || tipe_param==42 || tipe_param==43){
              qa.sprintf("INSERT INTO %s (id_info_data, id_rute, data, set_param, siklus, data_timestamp, flag_set_param) "
                         "values(:id_info_data, :id_rute, :data, :set_param, :siklus, :data_timestamp, :flag_set_param)",
                            tipe_data.toUtf8().data());
                              query.exec("pragma synchronous = off;");
                              query.prepare(qa);
                              query.bindValue(":id_info_data",id_data_info);//id_info_data from last insert id info data
                              query.bindValue(":id_rute",id_rute_baru);
                              query.bindValue(":data",all_data);
                              query.bindValue(":set_param",all_rute_param);
                              query.bindValue(":siklus",0);//jika dihapus lebih baik
                              query.bindValue(":data_timestamp",time);
                              query.bindValue(":flag_set_param",0); //ganti data asli ya nanti
                              //query.exec();
                              if(!query.exec())return 0;
                              else return 1;
             //---------------------------------------------------------------//
                              //metode nyimpennya minta di tread semua ya
                              //bisa contoh cara nyimpennya OVM
        }
        else if(tipe_param==28 || tipe_param==3 ||tipe_param==2 || tipe_param==11){

             qa.sprintf("INSERT INTO %s (id_info_data, id_rute, data, set_param, siklus, data_timestamp, flag_set_param) "
                        "values(:id_info_data, :id_rute, :data, :set_param, :siklus, :data_timestamp, :flag_set_param)",
                           tipe_data.toUtf8().data());
                             query.exec("pragma synchronous = off;");
                             query.prepare(qa);
                             query.bindValue(":id_info_data",id_data_info);//id_info_data from last insert id info data
                             query.bindValue(":id_rute",id_rute_baru);
                             query.bindValue(":data",all_data);
                             query.bindValue(":set_param",all_rute_param);
                             query.bindValue(":siklus",siklus);
                             query.bindValue(":data_timestamp",time);
                             query.bindValue(":flag_set_param",0); //ganti data asli ya nanti
                             //query.exec();
                             if(!query.exec())return 0;
                             else return 1;

             }
         }
    }
}

int controller::simpan_param(QSqlQuery *query, int id_paramnya, int flag_masukkan_param, int id_aset, int id_parent, QString rute_baru, QString cacah_data_name, int id_data_masuk, int id_param, int tipe_param, int id_rute, int time, int siklus, int id_database, QByteArray all_rute_param, QByteArray all_data)
{
    QString aa;
//    if(flag_masukkan_param==0){
//        //aa = QString("INSERT INTO parameter ( id_tipe_param, id_aset, urut) VALUES('%1',%2,%3)").arg(QString::number(data_new[2][a]),QString::number(id_parent),QString::number(1));
//        aa = QString("INSERT INTO parameter (id_tipe_param,id_aset,urut)"
//                     " SELECT %1,%2,%3 WHERE NOT EXISTS "
//                     "(SELECT id_tipe_param,id_aset,urut FROM parameter "
//                     "WHERE id_tipe_param=%4 AND id_aset=%5)").
//                     arg(QString::number(tipe_param),//id_tipe_param
//                         QString::number(id_parent),//id_aset
//                         QString::number(1),//urut
//                         QString::number(tipe_param),//id_tipe_param
//                         QString::number(id_parent));//id_aset
//        qDebug()<<id_parent<<"------<<>>";
//        id_paramnya=id_parent;
//        if(!query->exec(aa)){qDebug()<<"1gagal simpen"<<id_aset;}
//        else{while(query->next()){qDebug()<<"1sukses="<<id_aset;
//            id_paramnya=query->lastInsertId().toInt();
//           // flag_masuk_param1=1;
//            }}
//    }
//    else{
//   // aa = QString("INSERT INTO parameter ( id_tipe_param, id_aset, urut) VALUES('%1',%2,%3)").arg(QString::number(data_new[2][a]),QString::number(id_aset),QString::number(1));
//    aa = QString("INSERT INTO parameter (id_tipe_param, id_aset, urut)"
//                 " SELECT %1,%2,%3 WHERE NOT EXISTS "
//                 "(SELECT id_tipe_param,id_aset,urut FROM parameter "
//                 "WHERE id_tipe_param=%4 AND id_aset=%5)").
//            arg(QString::number(tipe_param),//id_tipe_param
//                QString::number(id_aset),//id_aset
//                QString::number(1),//urut
//                QString::number(tipe_param),//id_tipe_param
//                QString::number(id_aset));//id_aset
//    qDebug()<<aa;
//    if(!query->exec(aa)){qDebug()<<"1gagal simpen"<<id_aset;}
//    else{while(query->next()){qDebug()<<"1sukses="<<id_aset;
//        id_paramnya=query->lastInsertId().toInt();
//        //flag_masuk_param2=1;
//        }}
//   // flag_masukkan_param=0;
//    }
    id_param = id_paramnya;
    id_parent=0;
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

    id_param = simpan_param(query,
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
return id_param;
}

QString controller::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
    return nama_tabel;
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
