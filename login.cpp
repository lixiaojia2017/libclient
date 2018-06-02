#include "login.h"
#include "ui_login.h"
#include "new_user.h"
#include<QKeyEvent>
//#include<QDebug>
#include<QDialog>
#include<QLabel>
//#include"new_user.h"
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    handleEvents();
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
        success = this->login();
            if(success == true)
            {
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

            }
            else
            {
               QDialog error_dlg;
               error_dlg.resize(400,300);

               QLabel error_to_log(&error_dlg,Qt::Widget);
               error_to_log.resize(300,300);
               error_to_log.show();
               error_to_log.setText("<center><h1>密码错误</h1></center>");

               error_to_log.setStyleSheet("QLabel{color:rgb(200,45,100);"  //前景色
                                          "background-color:rgb(150,35,150);" //背景颜色
                                          "border-image:url(:/image/logo.png);"//背景图
                                          "}");

               error_dlg.exec();

            }
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

    connect(ui->LE_password, &QLineEdit::returnPressed, [this] {
        ui->LI->click();
    });
}
bool Login::login()
{
    QString str1 = ui->LE_username->text();
    QString str2 = ui->LE_password->text();
    if(str2 == "123")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Login::getIdentity()
{
    if(ui->identity->currentText() == "Administrator")
    {
        return true;
    }
    else
    {
        return false;
    }
}
