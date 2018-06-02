#include "login.h"
#include "reader.h"
#include"new_user.h"
#include"find_password.h"
#include"administrator.h"
#include <QApplication>
//#include<QDialog>
//#include<QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w; //登录界面
    w.show();
    Reader r;  //读者界面
    Administrator ad; //管理员界面

    QObject::connect(&w,SIGNAL(showReaderwin()),&r,SLOT(showReaderwin()));
    QObject::connect(&w,SIGNAL(closeReaderwin()),&r,SLOT(closeReaderwin()));
    QObject::connect(&w,SIGNAL(showAdministratorwin()),&ad,SLOT(showAdministratorwin()));
    QObject::connect(&w,SIGNAL(closeAdministratorwin()),&ad,SLOT(closeAdministratorwin()));


    return a.exec();
}
