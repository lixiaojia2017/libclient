#include "administrator.h"
#include "ui_administrator.h"

Administrator::Administrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Administrator)
{
    ui->setupUi(this);
}

Administrator::~Administrator()
{
    delete ui;
}
void Administrator::showAdministratorwin()
{
    this->show();
}

void Administrator::closeAdministratorwin()
{
    this->close();
}
