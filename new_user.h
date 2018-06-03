#ifndef NEW_USER_H
#define NEW_USER_H

#include <QMainWindow>

namespace Ui {
class New_user;
}

class New_user : public QMainWindow
{
    Q_OBJECT

public:
    explicit New_user(QWidget *parent = 0);
    ~New_user();

private:
    Ui::New_user *ui;
};

#endif // NEW_USER_H
