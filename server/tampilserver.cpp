#include "tampilserver.h"
#include "ui_tampilserver.h"

TampilServer::TampilServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TampilServer)
{
    ui->setupUi(this);
    //RunServer();

}

TampilServer::~TampilServer()
{
    delete ui;
}

void TampilServer::RunServer()
{
    this->setWindowTitle("GRPC Server");
    //cek_data(0, 0, 0, 0);
    this->setMinimumSize(350,350);
    this->setMaximumSize(350,350);
   // show();
}
