//The maximum size of a TCP packet is 64K (65535 bytes)
//masuk di array dulu saja
//note untuk authentication

//komunikasi masih belum bisa stabil, coba dicari data yang kemaren
//untuk balas balasan 1 sama lain dan tidak terikat 1 loop atau membahayakan

//tanggal 24 agustus update pak jono todo list
//tampilan centang untuk data siklus dijadikan 1 data saja agar centangnya per silinder
//ketika upload sudah jadi membandingkan data yang ada di server namun belum ada di local

#include "tampil.h"
#include "ui_tampil.h"
#include <QTreeView>
#include <QObject>
struct T dat;

Tampil::Tampil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tampil)
{
    ui->setupUi(this);
    this->setWindowTitle("Simulasi Upload Data");
    this->setMaximumSize(600,600);
    setup_tampil_hirarki_server();
    box2 = new QVBoxLayout(this);
    list_check = new QListWidget;
    ui->verticalLayout_2->addLayout(box2);
    show();
}

void Tampil::setup_tampil_hirarki_server()
{
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

}

void Tampil::getAllChildren(QModelIndex idx, QModelIndexList &list)
{
    list.push_back(idx);
    for (int i=0; i!= tree1->rowCount(idx);i++)
    {
        getAllChildren(idx.child(i,0), list);
    }
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
    std::string server_address("127.0.0.1:50051");
    cc = new controller();
    cc->initial_database();
    cc->flag_sukses=0;
    cc->CallServer("list_info",1,server_address,0,0);
    if(flag_compare==1)list_check->clear();
    list_check->addItems(cc->aset_info_tampil);
    QListWidgetItem* list_item = 0;
    for(int i=0; i<list_check->count(); i++){
        list_item = list_check->item(i);
        list_item->setFlags(list_item->flags() | Qt::ItemIsUserCheckable);
        list_item->setCheckState(Qt::Checked);
    }
    box2->addWidget(list_check);
    QObject::connect(list_check, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(highlightChecked(QListWidgetItem*)));
    qDebug()<<"nomor status pesan"<<cc->alarm_message;
    if(cc->alarm_message!=0){
       QMessageBox::warning(this, "Error ("+QString::number(cc->alarm_message)+")", "Error ("+cc->pesan_alarm+")");
       //QMessageBox::information(this,"informasi","tidak ada data update");
    }
    else{
       QMessageBox::information(this,"informasi","compare data server sukses");
    }
    flag_compare=1;

}

void Tampil::highlightChecked(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked)
            item->setBackgroundColor(QColor("#ffffb2"));
        else
            item->setBackgroundColor(QColor("#ffffff"));
}


void Tampil::on_PB_synchron_clicked()
{
    cc->flag_emit_cukup=0;
    if(flag_compare!=1){
        QMessageBox::information(this,"informasi","lakukan compare terlebih dahulu");
    }
    else{
        if(cc->alarm_message!=0){
           QMessageBox::warning(this, "Error ("+QString::number(cc->alarm_message)+")", "Error ("+cc->pesan_alarm+")");
           //QMessageBox::information(this,"informasi","tidak ada data update");
        }
        QStringList coba = cc->aset_info_server;//jadi yang menjadi rotasi tidak boleh terpengaruh dengan apapun
        if(cc->aset_info_server.size()!=0){
            QListWidgetItem* list_item = 0;
            int konter=0;
            for(int i=0; i<list_check->count(); i++){
                list_item = list_check->item(i);
                qDebug()<<"status "<<i<<list_item->checkState();
                QString cek_aset = (QString) cc->aset_info_tampil[i];
                if(list_item->checkState()==false){
                    qDebug()<<"ukuran"<<cc->aset_info_server.size();
                    for(int k=0; k<coba.size(); k++){
                        //-----------------------------------------------------------------------//
                        //disederhanakan!!!!
                        if(cek_aset==coba[k]){
                           cc->aset_info_server.erase(cc->aset_info_server.begin()+k-konter);
                           cc->c_id_param_lama.erase(cc->c_id_param_lama.begin()+k-konter);
                           cc->c_tipe_param.erase(cc->c_tipe_param.begin()+k-konter);
                           cc->c_id_rute_lama.erase(cc->c_id_rute_lama.begin()+k-konter);
                           cc->c_time.erase(cc->c_time.begin()+k-konter);
                           cc->c_siklus.erase(cc->c_siklus.begin()+k-konter);
                           //diisi list data yang mau persiapan dikirm
                           konter+=1;
                        }
                    }
                }
            }
             //flag 2 khusus untuk sychronize

            //QMessageBox::information(this,"informasi","update data server sukses");
            flag_compare=0;
//            qDebug()<<"- data yang dikirim balik dari server----------------------------->";
//            for(int i=0; i<cc->aset_info_server.size(); i++){
//                qDebug()<<"-"<<cc->aset_info_server[i]
//                          <<cc->c_id_param_lama[i]
//                            <<cc->c_tipe_param[i]
//                              <<cc->c_id_rute_lama[i]
//                                <<cc->c_time[i]
//                                  <<cc->c_siklus[i];
//            }
//            qDebug()<<"--------------------------------------------------------------->";
            //mulai kirim ke server sesuai urutan harus sembari ada feedback
            //--------------------------------------------------//
            cc->flag_sukses=0;
            std::string server_address("127.0.0.1:50051");
            cc->CallServer("kirim_data",2,server_address,0,0);
            if(cc->alarm_message_data!=0)
                QMessageBox::warning(this, "Kirim Data Error ("+QString::number(cc->alarm_message_data)+")", "Error ("+cc->pesan_alarm+")"+
                                     "data ke:"+QString::number(cc->counter_pesan));

        }
        else{
            QMessageBox::information(this,"informasi","tidak ada data yang terupdate");
        }
    }
}



