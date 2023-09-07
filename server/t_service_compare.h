#include <QtCore>
#include <service_compare.h>

#ifndef T_SERVICE_COMPARE_H
#define T_SERVICE_COMPARE_H


class t_service_compare : public QThread
{
public:
    t_service_compare();
    service_compare *saving;
    void run();
    int id_database;
    QStringList list_aset;
    QStringList list_rute;
    QVector<int> t_id_param_lama;
    QVector<int> t_id_data_masuk;
    QVector<int> t_tipe_param;
    QVector<int> t_id_rute;
    QVector<int> t_time;
    QVector<int> t_siklus;
};

#endif // T_SERVICE_COMPARE_H
