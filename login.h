#ifndef LOGIN_H
#define LOGIN_H
#include"new_user.h"
#include"find_password.h"
#include "waitingwindow.h"
#include "backend/handle/constructer/userconstructer.h"
#include "fileHandler/confighandler.h"
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

signals:
    void showReaderwin(QString&);

    void showAdministratorwin(QString&);

private:
    waitingWindow wait;
    void handleEvents(); // 信号槽事件处理

    Ui::Login *ui;
    Find_password find_password;
    configHandler config;
    bool success = false;
    bool pwdAutoLoad = false;
};

#endif // LOGIN_H
