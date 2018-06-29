#include "find_password.h"
#include "ui_find_password.h"
#include<QDialog>
#include<QLabel>
#include<QFrame>
#include<QHBoxLayout>
#include<QFile>
#include "backend/userrqt.h"
#include "backend/socketthread.h"
#include "backend/responsehdl.h"
#include <QMessageBox>
Find_password::Find_password(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Find_password),
    serverport(-1)
{
    ui->setupUi(this);
}

Find_password::~Find_password()
{
    delete ui;
}

void Find_password::setServer(QString addr, int p)
{
  serverAddr = addr;
  serverport = p;
}

void Find_password::on_sentcode_clicked()
{
    UserRqt rqt("unknown");
    rqt.construct("forget",ui->frame->children()[1]);
    if(serverport==-1 || serverAddr.isEmpty())
      {
        QMessageBox::about(this,"Error","Server address or port not set");
        return;
      }
    SocketThread thr(serverAddr,serverport,rqt.getRequest());
    connect(&thr,&SocketThread::connectFailed,[&](){
        QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(&thr,&SocketThread::badResponse,[&](){
        QMessageBox::about(this,"Failed","server error");
    });
    connect(&thr,&SocketThread::onSuccess,[&](QJsonObject* rsp)
    {
        ResponseHdl hdl(rsp);
        connect(&hdl,&ResponseHdl::onSuccess,[&](){
            QMessageBox::about(this,"Success","reset password has been sent to email");
        });
        connect(&hdl,&ResponseHdl::onFailed,[&](QString& info){
            QMessageBox::about(this,"Failed",info);
        });
        hdl.deal();
    });
    thr.run();
}
