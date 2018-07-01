#include "pdfviewer/pdfreader.h"
#include "login.h"
#include "reader.h"
#include "new_user.h"
#include "find_password.h"
#include "waitingwindow.h"
#include "fileHandler/fileloader.h"
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
    /// loading from enrypted data, example
    PDFReader pdf(&w);
    fileLoader loader;
    waitingWindow wait2;
    wait2.setMax(100);
    wait2.setText("Loading, please wait...");
    loader.setPath("./encrypted.dat");
    QObject::connect(&loader,&fileLoader::process,&wait2,[&](int num)
    {
        wait2.setCurr(num);
      });
    QObject::connect(&loader,&fileLoader::onFinish,&pdf,[&](const QByteArray data)
    {
        pdf.loadData(data);
        wait2.close();
        pdf.show();
      });
    wait2.show();
    loader.load();
    ////
    int ret = a.exec();
    delete[] args;
    return ret;
}
