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
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    handleEvents();
    //ui->centralWidget->setStyleSheet("background-color:white");
    initStyle();
}
Login::~Login()
{
    delete ui;

}

void Login::handleEvents() // 信号槽事件处理
{
    connect(ui->LI,&QPushButton::clicked,
            [=]()
    {
        ui->LI->setEnabled(false);
        UserRqt rqt("unknown");
        rqt.construct("login",ui->gridLayout);
        SocketThread thr("1.2.3.4",5678,rqt.getRequest());
        connect(&thr,&SocketThread::connectFailed,[&](){
            QMessageBox::about(this,"Login failed","connection timeout");
        });
        connect(&thr,&SocketThread::badResponse,[&](){
            QMessageBox::about(this,"Login failed","server error");
        });
        connect(&thr,&SocketThread::onSuccess,[&](QJsonObject* rsp)
        {
            ResponseHdl hdl(rsp);
            connect(&hdl,&ResponseHdl::onSuccess,[&](){
                if(getIdentity())
                {
                    emit showAdministratorwin();
                    emit closeReaderwin();
                }
                else
                {
                    emit showReaderwin();
                    emit closeAdministratorwin();
                }
                this->close();
            });
            connect(&hdl,&ResponseHdl::onFailed,[&](QString& info){
                QMessageBox::about(this,"Login failed",info);
            });
            hdl.deal();
        });
        thr.run();
        ui->LI->setEnabled(true);
    });


    connect(ui->new_2,&QPushButton::clicked,
            [=]()
    {
        this->newuser.show();
    });

    connect(ui->find_password,&QPushButton::clicked,
            [=]()
    {
        this->findPassword.show();
    });

    connect(ui->password, &QLineEdit::returnPressed, [this] {
        ui->LI->click();
    });
}
bool Login::login()
{
    /*QString str1 = ui->LE_username->text();
    QString str2 = ui->LE_password->text();
    if(str2 == "123")
    {
        return true;
    }
    else
    {
        return false;
    }*/
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
