#include <QApplication>
#include "bisa.h"
//#include "tampilserver.h"

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  bisa ku;
//  ku.
  ku.RunServer();
  return a.exec();
}
