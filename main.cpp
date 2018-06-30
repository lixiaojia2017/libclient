#include "login.h"
#include "reader.h"
#include "new_user.h"
#include "find_password.h"
#include "waitingwindow.h"
#include <QApplication>
//#include<QDialog>
//#include<QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w; //登录界面
    w.show();
    //w.close();
    Reader r;  //读者界面
    //r.show();
    QObject::connect(&w,&Login::showReaderwin,&r,&Reader::showReaderwin);
    QObject::connect(&w,&Login::showAdministratorwin,&r,&Reader::showAdministratorwin);


    return a.exec();
}
