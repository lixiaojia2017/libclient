#include "login.h"
#include "reader.h"
#include"new_user.h"
#include"find_password.h"
#include <QApplication>
//#include<QDialog>
//#include<QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w; //登录界面
    w.show();
    Reader r;  //读者界面

    QObject::connect(&w,SIGNAL(showReaderwin()),&r,SLOT(showReaderwin()));
    QObject::connect(&w,SIGNAL(showAdministratorwin()),&r,SLOT(showAdministratorwin()));


    return a.exec();
}
