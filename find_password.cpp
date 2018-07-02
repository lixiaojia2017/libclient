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

#define RESTORE   ui->sentcode->setEnabled(true);\
                  wait.close();

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
    ui->sentcode->setEnabled(false);
    wait.show();
    userforget rqt(ui->username->text(),ui->group->currentText(),ui->auth->text());
    if(serverport==-1 || serverAddr.isEmpty())
      {
        RESTORE
        QMessageBox::about(this,"Error","Server address or port not set");
        return;
      }

    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE
        QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE
        QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        ResponseHdl hdl(rsp);
        connect(&hdl,&ResponseHdl::onSuccess,this,[&](){
            RESTORE
            QMessageBox::about(this,"Success","reset password has been sent to email");
        });
        connect(&hdl,&ResponseHdl::onFailed,this,[&](QString& info){
            RESTORE
            QMessageBox::about(this,"Failed",info);
        });
        hdl.deal();
    });
    thr->start();
}
