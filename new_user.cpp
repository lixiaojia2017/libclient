#include "new_user.h"
#include "ui_new_user.h"

New_user::New_user(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::New_user)
{
    ui->setupUi(this);
}

New_user::~New_user()
{
    delete ui;
}

void New_user::on_ngetnewr_clicked()
{

}
