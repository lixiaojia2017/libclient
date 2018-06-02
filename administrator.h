#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QMainWindow>

namespace Ui {
class Administrator;
}

class Administrator : public QMainWindow
{
    Q_OBJECT


private slots:
    void showAdministratorwin();
    void closeAdministratorwin();

public:
    explicit Administrator(QWidget *parent = 0);
    ~Administrator();

private:
    Ui::Administrator *ui;
};

#endif // ADMINISTRATOR_H
