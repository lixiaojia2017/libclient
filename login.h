#ifndef LOGIN_H
#define LOGIN_H
#include"new_user.h"
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
protected:

    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_LI_clicked();

    void on_new_2_clicked();

signals:
    void showreaderwin();

private:
    Ui::Login *ui;
    New_user newuser;



};

#endif // LOGIN_H
