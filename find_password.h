#ifndef FIND_PASSWORD_H
#define FIND_PASSWORD_H

#include <QMainWindow>
#include "waitingwindow.h"
#include "backend/handle/constructer/userconstructer.h"
namespace Ui {
class Find_password;
}

class Find_password : public QMainWindow
{
    Q_OBJECT

public:
    explicit Find_password(QWidget *parent = 0);
    void setServer(QString addr, int p);
    ~Find_password();

private slots:
    void on_sentcode_clicked();

private:
    waitingWindow wait;
    Ui::Find_password *ui;
    QString serverAddr;
    int serverport;
};

#endif // FIND_PASSWORD_H
