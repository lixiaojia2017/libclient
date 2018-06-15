#include "login.h"
#include "ui_login.h"
#include "new_user.h"
#include<QKeyEvent>
//#include<QDebug>
#include<QDialog>
#include<QLabel>
#include<QFrame>
#include<QHBoxLayout>
#include<QFile>
#include "backend/userrqt.h"
#include "backend/socketthread.h"
#include "backend/responsehdl.h"
#include "backend/loginhdl.h"
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    handleEvents();
    initStyle();
}
Login::~Login()
{
    delete ui;

}

void Login::handleEvents() // 信号槽事件处理
{
    connect(ui->logIn,&QPushButton::clicked,
            [=]()
    {
        ui->logIn->setEnabled(false);
        ui->logIn->setText("登录中...");
        UserRqt rqt("unknown");
        rqt.construct("login",ui->frame);
        SocketThread thr("inftyloop.tech",5678,rqt.getRequest());
        connect(&thr,&SocketThread::connectFailed,[&](){
            QMessageBox::about(this,"Login failed","connection timeout");
        });
        connect(&thr,&SocketThread::badResponse,[&](){
            QMessageBox::about(this,"Login failed","server error");
        });
        connect(&thr,&SocketThread::onSuccess,[&](QJsonObject* rsp)
        {
            LoginHdl hdl(rsp);
            connect(&hdl,&LoginHdl::onSuccess,[&](QString& token){
                if(getIdentity())
                {
                    emit showAdministratorwin(token);
                }
                else
                {
                    emit showReaderwin(token);
                }
                this->close();
            });
            connect(&hdl,&LoginHdl::onFailed,[&](QString& info){
                QMessageBox::about(this,"Login failed",info);
            });
            hdl.deal();
        });
        thr.run();
        ui->logIn->setEnabled(true);
        ui->logIn->setText("登录");
    });


    connect(ui->newReader,&QPushButton::clicked,
            [=]()
    {
        this->new_user.show();
    });

    connect(ui->findPassword,&QPushButton::clicked,
            [=]()
    {
        this->find_password.show();
    });

    connect(ui->password, &QLineEdit::returnPressed, [this] {
        ui->logIn->click();
    });
}

bool Login::getIdentity()
{
    if(ui->group->currentText() == "staff")
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Login::initStyle()
{
      //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
