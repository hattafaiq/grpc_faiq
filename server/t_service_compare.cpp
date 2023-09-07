#include "t_service_compare.h"

extern struct data data_base;

t_service_compare::t_service_compare()
{

}

void t_service_compare::run()
{
    saving->eliminasi_data(id_database,
            list_aset,
            list_rute,
            t_id_param_lama,
            t_id_data_masuk,
            t_tipe_param,
            t_id_rute,
            t_time,
            t_siklus);
}
