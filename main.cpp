#include "pdfviewer/pdfreader.h"
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
    int nargs = argc + 1;
    char** args = new char*[nargs];
    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }
    args[argc] = (char*)"--disable-web-security";
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/image/icon.ico"));
    Login w; //登录界面
    Reader r;  //读者界面
    QObject::connect(&w,&Login::showReaderwin,&r,&Reader::showReaderwin);
    QObject::connect(&w,&Login::showAdministratorwin,&r,&Reader::showAdministratorwin);
    w.show();
    //w.close();
    //r.show();
    PDFReader pdf;
    pdf.show();
    int ret = a.exec();
    delete[] args;
    return ret;
}
