#ifndef TAMPILSERVER_H
#define TAMPILSERVER_H

#include <QMainWindow>

namespace Ui {
class TampilServer;
}

class TampilServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TampilServer(QWidget *parent = nullptr);
    ~TampilServer();
    void RunServer();

private:
    Ui::TampilServer *ui;
};

#endif // TAMPILSERVER_H
