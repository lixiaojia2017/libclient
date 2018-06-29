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
    ui(new Ui::Find_password)
{
    ui->setupUi(this);
}

Find_password::~Find_password()
{
    delete ui;
}



void Find_password::on_sentcode_clicked()
{
    UserRqt rqt("unknown");
    rqt.construct("forget",ui->frame->children()[1]);
    SocketThread thr("127.0.0.1",5678,rqt.getRequest());//inftyloop.tech101.5.131.23724af0492ac247055ce9bd959fa26185f
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
