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

    Reader r;

    QObject::connect(&w,SIGNAL(showreaderwin()),&r,SLOT(showwin()));


    //    New_user newacc;  //新用户注册界面
    //    newacc.show();
    //    Find_password  fpassword;
    //    fpassword.show();
   Administrator ad;
   ad.show();



    return a.exec();
}
