#include "service_compare.h"
extern struct data data_base;

service_compare::service_compare()
{

}

void service_compare::eliminasi_data(int id_database, QStringList rute, QStringList aset, QVector<int> id_data_masuk1, QVector<int> id_param1, QVector<int> tipe_param1, QVector<int> id_rute1, QVector<int> time1, QVector<int> siklus1)
{
    QVector<int> id_data_masuk = id_data_masuk1;
    QVector<int> id_param = id_param1;
    QVector<int> tipe_param = tipe_param1;
    QVector<int> id_rute = id_rute1;
    QVector<int> time = time1;
    QVector<int> siklus = siklus1;
    QStringList cacah_data_aset = aset;
//    QSqlDatabase db;

//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("127.0.0.1");//port 2121
//    db.setDatabaseName("test");
//    db.setUserName("root");
//    db.setPassword("password");

//    if (!db.open())
//    {
//      //data_base.counter+=1;
//      qDebug()<<"tidak bisa buka database???????----->";//<<data_base.counter;
//    }else{
//        qDebug()<<"bisa";
//    }

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

   // db.transaction();
    QSqlQuery query(data_base.db);
    int konter=0;
    QString qu;

//    qDebug()<<"-------------------------------clean dan detile-------------------------------------------------";
    //mungkin bisa disederhanakan lagi tapi masih belum tau caranya

    for(int i=0; i<id_param1.size(); i++){
        qu = QString("SELECT id_info_data "
                     "FROM %1 "
                     "WHERE data_timestamp=%2").arg(get_table_name(tipe_param1[i]),QString::number(time1[i]));
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
//    list_rute = rute;
//    list_aset = cacah_data_aset;
//    t_id_param_lama = id_param;
//    t_tipe_param = tipe_param;
//    t_id_rute = id_rute;
//    t_time = time;
//    t_siklus = siklus;
//    t_id_data_masuk = id_data_masuk;
}

QString service_compare::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
    return nama_tabel;
}
