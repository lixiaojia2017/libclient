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

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

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
  // load server addr from config
  QString &&server = config.getServerAddr();
  if(server.isEmpty())
    {
      ui->serveraddr->setFocus();
    }
  else ui->serveraddr->setText(config.getServerAddr());
  // read pwd from storage when username input finished
  connect(ui->username,&QLineEdit::editingFinished,[&]()
  {
      QString user = ui->username->text();
      QString pwd = config.getPassword(user);
      if(!pwd.isEmpty())
        {
          ui->password->setText(pwd);
          ui->remPassword->setCheckState(Qt::Checked);
          pwdAutoLoad = true;
        }
    });
  // turn off pwdAutoLoad if manually edited the pwd
  connect(ui->password,&QLineEdit::textChanged,[&]()
  {
      pwdAutoLoad = false;
    });
  // start login procedure
    connect(ui->logIn,&QPushButton::clicked,
            [&]()
    {
        if(!pwdAutoLoad)
        {
            ui->password->setText(token::getMD5(ui->password->text()));
        }
        ui->logIn->setEnabled(false);
        ui->logIn->setText("登录中...");
        UserRqt rqt("unknown");
        rqt.construct("login",ui->frame);
        // server addr detection
        QString server = ui->serveraddr->text();
        if(server.isEmpty())
          {
            QMessageBox::about(this,"Error","Server address cannot be empty");
            ui->logIn->setEnabled(true);
            ui->logIn->setText("登录");
            ui->password->setText("");
            return;
          }
        QStringList serverlist = server.split(':');
        if(serverlist.size()==1)
          {
            QMessageBox::about(this,"Error","Please specify a port for the server");
            ui->logIn->setEnabled(true);
            ui->logIn->setText("登录");
            ui->password->setText("");
            return;
          }
        // check username and password not empty
        if(ui->username->text().isEmpty())
          {
            QMessageBox::about(this,"Error","Username cannot be empty");
            ui->logIn->setEnabled(true);
            ui->logIn->setText("登录");
            ui->password->setText("");
            return;
          }
        if(ui->password->text().isEmpty())
          {
            QMessageBox::about(this,"Error","Password cannot be empty");
            ui->logIn->setEnabled(true);
            ui->logIn->setText("登录");
            ui->password->setText("");
            return;
          }
        SocketThread *thr= new SocketThread(serverlist[0],serverlist[1].toUInt(),rqt.getRequest());
        connect(thr,&SocketThread::connectFailed,this,[&](){
            wait.close();
            QMessageBox::about(this,"Login failed","connection timeout");
            ui->logIn->setEnabled(true);
            ui->logIn->setText("登录");
            ui->password->setText("");
        });
        connect(thr,&SocketThread::badResponse,this,[&](){
            wait.close();
            QMessageBox::about(this,"Login failed","server error");
            ui->logIn->setEnabled(true);
            ui->logIn->setText("登录");
            ui->password->setText("");
        });
        connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
        {
          wait.close();
          // remember password & server addr
          config.setServerAddr(ui->serveraddr->text());
          if(!ui->remPassword->isChecked())
          // remember to remove the pwd if the checkbox is unchecked
            {
              config.removePassword(ui->username->text());
            }
          // connect success, handle the login request
            LoginHdl hdl(rsp);
            connect(&hdl,&LoginHdl::onSuccess,[&](QString& token){
              if(ui->remPassword->isChecked())
              {
                config.setPassword(ui->username->text(),ui->password->text());
              }
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
                ui->logIn->setEnabled(true);
                ui->logIn->setText("登录");
                ui->password->setText("");
            });
            hdl.deal();
        });
        thr->start();
        wait.show();
    });
    connect(ui->findPassword,&QPushButton::clicked,
            [=]()
    {
        QString && str = this->ui->serveraddr->text();
        QStringList && list = str.split(':');
        if(str.isEmpty() || list.size()==1)
          {
            QMessageBox::about(this,"Error","Server address or port not set");
            return;
          }
        find_password.setServer(list[0],list[1].toInt());
        this->find_password.show();
    });

    connect(ui->password, &QLineEdit::returnPressed, [this] {
        ui->logIn->click();
    });
}

bool Login::getIdentity()
{
    if(ui->group->currentText() == "staffs")
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
