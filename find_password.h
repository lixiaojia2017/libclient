#ifndef FIND_PASSWORD_H
#define FIND_PASSWORD_H

#include <QMainWindow>

namespace Ui {
class Find_password;
}

class Find_password : public QMainWindow
{
    Q_OBJECT

public:
    explicit Find_password(QWidget *parent = 0);
    ~Find_password();

private slots:
    void on_sentcode_clicked();

private:
    Ui::Find_password *ui;
};

#endif // FIND_PASSWORD_H
