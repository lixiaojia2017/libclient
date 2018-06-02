#include "find_password.h"
#include "ui_find_password.h"

Find_password::Find_password(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Find_password)
{
    ui->setupUi(this);
}

Find_password::~Find_password()
{
    delete ui;
}
