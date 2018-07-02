#ifndef LOGIN_H
#define LOGIN_H
#include "new_user.h"
#include "find_password.h"
#include "waitingwindow.h"
#include "backend/handle/constructer/userconstructer.h"
#include "fileHandler/confighandler.h"
#include "reader.h"
#include <QMainWindow>
#include <QString>
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    bool getIdentity();

    void initStyle();
    void setReader(Reader *reader);
signals:
    void showReaderwin(QString&,QString&,int,int);

    void showAdministratorwin(QString&,QString&,int,int);

private slots:

private:
    waitingWindow wait;
    void handleEvents(); // 信号槽事件处理
    Reader *reader=nullptr;
    Ui::Login *ui;
    Find_password find_password;
    configHandler config;
    bool success = false;
    bool pwdAutoLoad = false;
};

#endif // LOGIN_H
