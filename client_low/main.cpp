#include <QCoreApplication>
#include "data_proses.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    data_proses h;
    h.kirim();
    return a.exec();
}
