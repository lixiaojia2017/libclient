#include "login.h"
#include "reader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

//    Reader r;
//    r.show();

    return a.exec();
}
