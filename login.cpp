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
}

Login::~Login()
{
    delete ui;
}
void Login::on_LI_clicked()
{
    QString str = "123456";
    if(ui->LE_password->text()==str)
    {
        emit showreaderwin();
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
//       error_to_log.setStyleSheet("color:rgb(255,0,0)");

       error_to_log.setStyleSheet("QLabel{color:rgb(200,45,100);"  //前景色
                                  "background-color:rgb(150,35,150);" //背景颜色
                                  "border-image:url(:/image/logo.png);"//背景图
                                  "}");

       error_dlg.exec();

    }
}

void Login::on_new_2_clicked()
{
//    New_user newuser;
    newuser.show();
}
void Login::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter)
    {

    }
}
