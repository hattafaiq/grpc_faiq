//The maximum size of a TCP packet is 64K (65535 bytes)
//masuk di array dulu saja
//note untuk authentication

#include "tampil.h"
#include "ui_tampil.h"
#include <QTreeView>
#include <QObject>
struct T dat;

class GreeterClient : public Tampil{
private:
//    extern struct T dat;
    pesan_client request;
    pesan_server reply;
    ClientContext context;
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(protokol_1::NewStub(channel)) {}
   std::string initial_data(const std::string& user) {
   // Tampil t_proses;

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

       counter_s+=1;

//    qDebug()<<"size info:"<<data_n->size()*8<<cacah_data_name.size();
     if(data_n[0].size()!=0){
        for(int a=0; a<data_n[0].size(); a++ ){
          QString ay = cacah_data_name[a];
          qDebug()<<ay<<
          "id_parm:"<<data_n[1][a]<<
          "id_tip_parm:"<<data_n[2][a]<<
          "id_rut:"<<data_n[3][a]<<
          "time:"<<data_n[4][a]<<
          "siklus"<<data_n[5][a];
        }
        std::vector<int> id_param,id_tip_parm,id_rut,time,siklus;//(data_n[0], n);
        id_param    = data_n[1].toStdVector();
        id_tip_parm = data_n[2].toStdVector();
        id_rut      = data_n[3].toStdVector();
        time        = data_n[4].toStdVector();
        siklus      = data_n[5].toStdVector();
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

        //sudah terkirim

        //lanjut ke pesan berikutnya
        request.set_header_pesan("list_info");
        id_param.clear();
        id_tip_parm.clear();
        id_rut.clear();
        time.clear();
        siklus.clear();
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
            if(reply.header_pesan()=="list_server"){
                qDebug()<<"hallo data yang tidak ada di server ini";
            }
            for(int i=0; i<data_n->size(); i++){
                data_n[i].clear();
            }
            all_rute_param.clear();
            cacah_data_name.clear();
            rute_baru.clear();
            all_data.clear();
            data_ini.clear();
            tampung_data.clear();
            list_rute.clear();
            conter_loop=0;


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

Tampil::Tampil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tampil)
{
    ui->setupUi(this);
    conter_loop=0;
    flag_kirim_ok=0;
    counter_s=0;
    this->setWindowTitle("Simulasi Upload Data");
    this->setMaximumSize(600,600);
    setup_tampil_hirarki_server();

    flag_kirim =0;
    show();
}

void Tampil::setup_tampil_hirarki_server()
{
    tree1 = new QStandardItemModel();
    this->load_aset(0, 0, 0);
    connect(ui->treeView,&TreeSubwin::emitEmulateDataByClick,this,&Tampil::on_treeView_clicked);
    ui->treeView->setModel( tree1 );
    this->ui->treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QModelIndex index = ui->treeView->model()->index(0,0);
    this->ui->treeView->setCurrentIndex(index);

    //---------------------mulai----------------------------------------//
}

void Tampil::cari_induk_paramm(int parameter, int tipe)
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
        // qDebug()<<"id_parent:"<<id_aset_induk;
         cari_induk(id_aset_induk);
      }
   }
}


void Tampil::mulai_cari(QSqlQuery *query)
{
    for(int i=1; i<data_n->size(); i++){
        data_n[i].clear();
    }
    qDebug()<<"cek 0:"<<data_n[0].size() <<data_n[1].size()<<data_n[2].size()
            <<data_n[3].size()<<data_n[4].size()<<data_n[5].size();
    conter_loop=+1;
    QVector<int> datax[4];
    QVector<int> data_[4];
    for(int i=0; i<data_->size(); i++){
        data_[i].clear();}
    for(int i=0; i<datax->size(); i++){
    datax[i].clear();}
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

    qDebug()<<"conter: "<<conter_loop <<" cek semua data sementara"
           <<data_[0].size()<<data_[1].size()<<data_[2].size()<<data_[3].size();

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
        data_n[5].push_back(query->value("siklus").toInt());
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
   // if(counter_s!=0){
     //    data_n->clear();
   // }
}


void Tampil::setup_tampil_hirarki_sofhaliza()
{

}

void Tampil::setup_tampil_hirarki_haliza()
{

}

Tampil::~Tampil()
{
    delete ui;
}

void Tampil::on_tableView_clicked(const QModelIndex &index)
{

}


void Tampil::on_tableView_2_pressed(const QModelIndex &index)
{
    int n_row = index.row();
    index_data_hapus = n_row;
}


void Tampil::on_treeView_clicked(QModelIndex index)
{
//    qDebug() <<__PRETTY_FUNCTION__
//            << "qmodelindex: "<< index.row()
//            << "parent id:"<<index.parent().data(ROLE_TREE_ASET_ID).toInt()
//            << "tree view anak ke1 diklik dengan index = " << index.row();
    index_tree_selected(index);

}

void Tampil::on_treeView_expanded(QModelIndex index)
{
    int n_row = index.row();
    index_data_hapus = n_row;
   // qDebug()<<"index="<<index;

}

void Tampil::on_treeView_activated(QModelIndex index)
{
    int n_row = index.row();
    index_data_hapus = n_row;
  //  qDebug()<<"index="<<index;
    //ui->lineEdit->clear();
}


QStandardItem* Tampil::assign_icon_x( QString name, int id_kind)
{
    QStandardItem* item;

    if (id_kind == ID_KIND_COMPANY)
        item = new QStandardItem( QIcon( ICON_COMPANY ), name);
    else if (id_kind == ID_KIND_DEPARTMENT)
        item = new QStandardItem( QIcon( ICON_DEPT ), name);
    else if (id_kind == ID_KIND_LOCATION)
        item = new QStandardItem( QIcon( ICON_LOCATION ), name);
    else if (id_kind == ID_KIND_GROUP)
        item = new QStandardItem( QIcon( ICON_GROUP ), name);
    else if (id_kind == ID_OFF_RUTE_ASET){
        item = new QStandardItem( QIcon( ICON_OFF_ROUTE_ASET), name);
        qDebug() << "(debug 16) aset merupakan off rute 2";
    }
    else if (id_kind == ID_KIND_RECIP_ENGINE)
        item = new QStandardItem( QIcon( ICON_RECIP_ENGINE ), name);
    else if (id_kind == ID_KIND_RECIP_COMPRESSOR)
        item = new QStandardItem( QIcon( ICON_RECIP_COMPRESSOR ), name);
    else if (id_kind == ID_KIND_ROTATING_MACHINE || id_kind == ID_KIND_ROTATING_EQUIP_V)
        item = new QStandardItem( QIcon( ICON_ROTATING_MACHINE ), name);
    else if (id_kind == ID_KIND_STRUCTURE)
        item = new QStandardItem( QIcon( ICON_STRUCTURE ), name);
    else if (id_kind == ID_KIND_PIPE)
        item = new QStandardItem( QIcon( ICON_PIPE ), name);
    else if (id_kind == ID_KIND_TANK)
        item = new QStandardItem( QIcon( ICON_TANK ), name);
    else if (id_kind == ID_KIND_ENGINE_CYL)
        item = new QStandardItem( QIcon( ICON_ENGINE_CYL ), name);
    else if (id_kind == ID_KIND_COMP_THROW)
        item = new QStandardItem( QIcon( ICON_COMP_THROW ), name);
    else if (id_kind == ID_KIND_COMP_VALVE)
        item = new QStandardItem( QIcon( ICON_COMP_VALVE ), name);
    else if (id_kind == ID_KIND_ROTATING_POINT)
        item = new QStandardItem( QIcon( ICON_ROTATING_POINT ), name);
    else if (id_kind == ID_KIND_STRUCTURE_POINT)
        item = new QStandardItem( QIcon( ICON_STRUCTURE_POINT ), name);
    else if (id_kind == ID_KIND_PIPE_POINT )
        item = new QStandardItem( QIcon( ICON_PIPE_POINT ), name);
    else if (id_kind == ID_KIND_EQUIPMENT_OTHER)
        item = new QStandardItem( QIcon( ICON_EQUIPMENT_OTHER ), name);
    else if (id_kind == ID_KIND_COMPONENT_OTHER )
        item = new QStandardItem( QIcon( ICON_COMPONENT_OTHER ), name);
    else
        item = new QStandardItem( QIcon( ICON_OTHER ), name);

    return item;
}


QStandardItem* Tampil::assign_icon(QStandardItemModel *tree, QString name, int id_kind, int id)
{
    QStandardItem* item;

    item = assign_icon_x( name, id_kind );

    tree->appendRow(item);
    QVariant v(id), L(id_kind);

    item->setData( v, ROLE_TREE_ASET_ID );
    item->setData( L, ROLE_TREE_ASET_KIND );

    item->setEditable( false );

    return item;
}

/* hanya merubah icon & text */
void Tampil::set_assign_icon_item(QStandardItem *tree, QString name, int id_kind, int id)
{
    qDebug("id = %d",id);
    tree->setText( name );

    if (id_kind == ID_KIND_COMPANY)
        tree->setIcon( QIcon( ICON_COMPANY ) );
    else if (id_kind == ID_KIND_DEPARTMENT)
        tree->setIcon( QIcon( ICON_DEPT ));
    else if (id_kind == ID_KIND_LOCATION)
        tree->setIcon( QIcon( ICON_LOCATION ));
    else if (id_kind == ID_KIND_GROUP)
        tree->setIcon( QIcon( ICON_GROUP ));
    else if (id_kind == ID_OFF_RUTE_ASET){
        tree->setIcon( QIcon( ICON_OFF_ROUTE_ASET ));
        qDebug() << "(debug 16) aset merupakan off rute 3";
    }
    else if (id_kind == ID_KIND_RECIP_ENGINE)
        tree->setIcon( QIcon( ICON_RECIP_ENGINE ));
    else if (id_kind == ID_KIND_RECIP_COMPRESSOR)
        tree->setIcon( QIcon( ICON_RECIP_COMPRESSOR ));
    else if (id_kind == ID_KIND_ROTATING_MACHINE)
        tree->setIcon( QIcon( ICON_ROTATING_MACHINE ));
    else if (id_kind == ID_KIND_STRUCTURE)
        tree->setIcon( QIcon( ICON_STRUCTURE ));
    else if (id_kind == ID_KIND_PIPE)
        tree->setIcon( QIcon( ICON_PIPE ));
    else if (id_kind == ID_KIND_TANK)
        tree->setIcon( QIcon( ICON_TANK ));
    else if (id_kind == ID_KIND_ENGINE_CYL)
        tree->setIcon( QIcon( ICON_ENGINE_CYL ));
    else if (id_kind == ID_KIND_COMP_THROW)
        tree->setIcon( QIcon( ICON_COMP_THROW ));
    else if (id_kind == ID_KIND_COMP_VALVE)
        tree->setIcon( QIcon( ICON_COMP_VALVE ));
    else if (id_kind == ID_KIND_ROTATING_POINT)
        tree->setIcon( QIcon( ICON_ROTATING_POINT ));
    else if (id_kind == ID_KIND_STRUCTURE_POINT)
        tree->setIcon( QIcon( ICON_STRUCTURE_POINT ));
    else if (id_kind == ID_KIND_PIPE_POINT )
        tree->setIcon( QIcon( ICON_PIPE_POINT ));
    else if (id_kind == ID_KIND_EQUIPMENT_OTHER)
        tree->setIcon( QIcon( ICON_EQUIPMENT_OTHER ));
    else if (id_kind == ID_KIND_COMPONENT_OTHER )
        tree->setIcon( QIcon( ICON_COMPONENT_OTHER ));
    else
        tree->setIcon( QIcon( ICON_OTHER ));
}

QStandardItem* Tampil::assign_icon_item(QStandardItem *tree, QString name, int id_kind, int id)
{
    QStandardItem* item;

    item = assign_icon_x( name, id_kind );

    tree->appendRow(item);
    QVariant v(id), L(id_kind);

    item->setData( v, ROLE_TREE_ASET_ID );
    item->setData( L, ROLE_TREE_ASET_KIND );

    item->setEditable( false );

    return item;
}
void Tampil::load_param(QStandardItem *si, int id_aset, int siapa)
{
   // qDebug() << __FUNCTION__ << "id_aset "<< id_aset<< "siapa"<<siapa;
    QString nama_param, qq;
    QSqlQuery Q( db );
    int id_s, id_tipe_param, urut;

    qq = QString("SELECT p.id, p.id_tipe_param, p.urut, tp.nama_param FROM parameter p JOIN tipe_param tp ON tp.id = p.id_tipe_param WHERE %1=%2").arg( (siapa)?"id_aset":"id").arg(id_aset);
    if(!Q.exec(qq)) qDebug() << __FUNCTION__ << __LINE__ << "ERROR : "<< Q.lastError().text();
    else {
        while(Q.next())
        {
            id_s = Q.value("id").toInt();
            id_tipe_param = Q.value("id_tipe_param").toInt();
            urut = Q.value("urut").toInt();
            nama_param = Q.value("nama_param").toString();

            if(urut>1) nama_param = QString("%1_%2").arg(nama_param).arg(urut);

            QVariant v(id_s), L( ID_KIND_PARAM );
            QStandardItem* item1;
            item1 = new QStandardItem(QIcon(":/images/param2.png"), nama_param );

            item1->setData( v, ROLE_TREE_ASET_ID );
            item1->setData( L, ROLE_TREE_ASET_KIND );
            item1->setData(id_tipe_param, ROLE_TREE_ASET_ID_TIPE_PARAM);
            item1->setData(id_s, ROLE_TREE_ASET_ID_PARAM);
            item1->setEditable( false );

            si->appendRow( item1 );
            QApplication::processEvents();

        }
    }
}

void Tampil::load_aset(QStandardItem *si, int id, int siapa)
{
    //qDebug("%s() <== id=%d, siapa = %d",__FUNCTION__,id,siapa);// << "(debug 10) masuk ke void load_aset";
    QSqlQuery Q2( db );
    QString nama;
    int id_kind;
    int id_aset;
    int id_parent;
    int jum_aset = 0;

    QString qu;

    qu = QString("SELECT * FROM aset WHERE id_parent=%1").arg(id);
    if(!Q2.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q2.lastError().text();
    else
    {
        while (Q2.next())
        {
            jum_aset++;
            nama = Q2.value("name").toString();
            id_aset = Q2.value("id").toInt();
            id_kind = Q2.value("id_kind").toInt();
            id_parent = Q2.value("id_parent").toInt();
          //  qDebug("id_aset : %d, id_kind : %d, id_parent : %d",id_aset,id_kind, id_parent);
            QStandardItem* item0;

            item0 = (id==0)? assign_icon(this->tree1, nama, id_kind, id_aset) :assign_icon_item( si, nama, id_kind, id_aset);

            load_aset(item0, id_aset, 1);
            load_param(item0, id_aset,1);

        }
        /// sorting dibuat hanya untuk id_kind == 5200 || 5300  RECIP_COMPRESSOR

        if(id_kind == ID_KIND_RECIP_COMPRESSOR)/*|| id_kind == ID_KIND_COMP_VALVE*/// )
            tree1->sort(0, Qt::AscendingOrder);

        if(id==0)
            this->sudah_ada_aset++;
    }
    if((siapa==0)&& (jum_aset==0))
        this->sudah_ada_aset=0;

}

void Tampil::index_tree_selected(QModelIndex index){


    qDebug(">> masuk fungsi %s()",__PRETTY_FUNCTION__);
    int p_id_aset;
    int p_id_kind;
    int p_id_tipe_param;
    int idParentSelect;
    idParentSelect=index.parent().data(ROLE_TREE_ASET_ID).toInt();

    QStandardItem *sd = tree1->itemFromIndex(index);

    //mencari semua anak dari tree yang dipilih
    QModelIndexList llist;
    getAllChildren(index, llist);
    onRouteChildTree.clear();
    for(int i=0; i< llist.size(); i++)
    {
        int idKind =llist.value(i).data(ROLE_TREE_ASET_KIND).toInt();
        if(idKind!= ID_KIND_PARAM ){
            int idAset = llist.value(i).data(ROLE_TREE_ASET_ID).toInt();
            onRouteChildTree.push_back(idAset);
        }
    }

    p_id_aset = sd->data( ROLE_TREE_ASET_ID ).toInt();
    p_id_kind = sd->data( ROLE_TREE_ASET_KIND ).toInt();
    p_id_tipe_param= sd->data(ROLE_TREE_ASET_ID_TIPE_PARAM).toInt();

    if (sd->hasChildren())
    {
        qDebug("Punya Anak %d", sd->rowCount());
    }
//    qDebug()<<"anaknya:"<<onRouteChildTree;
//    qDebug()<<"param:"<<p_id_aset;
//    qDebug()<<"tipe data:"<<p_id_tipe_param;
    //ui->lineEdit->clear();
    //initial_rute.clear();
    cari_induk_param(p_id_aset);
 //   qDebug()<<initial_rute.split('/');
    QStringList dataList = initial_rute.split('/');
    data_ini = dataList;
//    QDataStream dataStreamWrite(&data_utama, QIODevice::WriteOnly);
//    dataStreamWrite << data_ini;
//   // QStringList appNameList = appName.split("U");

//   //qDebug()<<"size nama=>"<<sizeof(data_ini)
//   // susun_data(p_id_aset,p_id_tipe_param);
//    data_utama.clear();
}

QString Tampil::get_table_name(int tipe)
{
    QString nama_tabel = QString("data_%1_tipe").arg(tipe);
//    nama_tabel.sprintf("data_%d_tipe", tipe);
    return nama_tabel;
}

void Tampil::tambah_aset(int parent, QString aset){

}

void Tampil::kirim_data(int id_param, int tipe_data, QByteArray data){

}



void Tampil::susun_data(int id_param, int tipe_data){
    qDebug()<<"mulai susun data:";
    QSqlQuery Q3( db );
    QString nama_tipe_data = get_table_name(tipe_data);
    qDebug() << nama_tipe_data;
    QString qu;
    qu = QString("SELECT * FROM %1 WHERE id_param=%2").arg(nama_tipe_data.toUtf8().data()).arg(id_param);
    if(!Q3.exec(qu)) qDebug()<< __FUNCTION__ << __LINE__ << "ERROR : "<<Q3.lastError().text();
    else{
     while(Q3.next()){
        QByteArray data = Q3.value("data").toByteArray();
    //    qDebug()<<"size:"<<data.size();
        kirim_data(id_param, tipe_data, data);
     }
   }
}

void Tampil::cari_induk_param(int p_id_aset){

    QSqlQuery Q2( db );
    QSqlQuery Q3( db );
    QString nama;
    int id_aset_induk;
    int id_parent_ku;

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

void Tampil::cari_induk(int p_id_aset){

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

void Tampil::getAllChildren(QModelIndex idx, QModelIndexList &list)
{
    list.push_back(idx);
    for (int i=0; i!= tree1->rowCount(idx);i++)
    {
        getAllChildren(idx.child(i,0), list);
    }
}




void Tampil::kirim1_info()
{
//    qDebug()<<"size info:"<<data_n->size()*8<<cacah_data_name.size();
//    for(int a=0; a<data_n[0].size(); a++ ){
//        QString ay = cacah_data_name[a];
//              qDebug()<<ay<<
//              "id_parm:"<<data_n[1][a]<<
//              "id_tip_parm:"<<data_n[2][a]<<
//              "id_rut:"<<data_n[3][a]<<
//              "time:"<<data_n[4][a]<<
//              "siklus"<<data_n[5][a];
//    }
}

void Tampil::terima_data_proses()
{
    qDebug()<<"tampil";
}


void Tampil::on_PB_connect_clicked()
{

}


void Tampil::on_PB_kirim_clicked()
{
    //simulasi mengirim data satuan
}


void Tampil::on_PB_compare_clicked()
{
    if(!flag_kirim_ok){
    std::string server_address("127.0.0.1:50051");
    grpc::ChannelArguments ch_args;
    ch_args.SetMaxReceiveMessageSize(-1);

    GreeterClient greeter( grpc::CreateCustomChannel (server_address, grpc::InsecureChannelCredentials(), ch_args));

    std::string user("world");
    std::string reply = greeter.initial_data(user);

    std::cout << "Greeter received: " << reply << std::endl;
    flag_kirim_ok=1;
    for(int i=1; i<data_n->size(); i++){
        data_n[i].clear();
    }
    all_rute_param.clear();
    cacah_data_name.clear();
    rute_baru.clear();
    all_data.clear();
    data_ini.clear();
    tampung_data.clear();
    list_rute.clear();
    qDebug()<<"cek 1:"<<data_n[0].size() <<data_n[1].size()<<data_n[2].size()
            <<data_n[3].size()<<data_n[4].size()<<data_n[5].size();
    }
    else{
        qDebug()<<"sudah dkirim tadi";
        for(int i=0; i<data_n->size(); i++){
            data_n[i].clear();
        }
        all_rute_param.clear();
        cacah_data_name.clear();
        rute_baru.clear();
        all_data.clear();
        data_ini.clear();
        tampung_data.clear();
        list_rute.clear();
        flag_kirim_ok=0;
        qDebug()<<"cek 2:"<<data_n[0].size() <<data_n[1].size()<<data_n[2].size()
                <<data_n[3].size()<<data_n[4].size()<<data_n[5].size();
    }
}


void Tampil::on_PB_synchron_clicked()
{

}

