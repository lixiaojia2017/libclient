#ifndef LOGIN_H
#define LOGIN_H
#include"new_user.h"
#include"find_password.h"
#include <QMainWindow>

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
    void showReaderwin();
    void closeReaderwin();

    void showAdministratorwin();
    void closeAdministratorwin();

private:
    void handleEvents(); // 信号槽事件处理
    bool login();

    Ui::Login *ui;
    New_user newuser;
    Find_password findPassword;

    bool success = false;


};

#endif // LOGIN_H
