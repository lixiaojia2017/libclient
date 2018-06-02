#include "reader.h"
#include "ui_reader.h"
#include<QScrollArea>
#include<QPushButton>
#include<QTextBrowser>
Reader::Reader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reader)
{
    ui->setupUi(this);
    connect(ui->switchtwo,&QPushButton::clicked,this,&Reader::switchPage);
    connect(ui->goodfind,&QPushButton::clicked,this,&Reader::switchPage);
}

Reader::~Reader()
{
    delete ui;
}
void Reader::showwin()
{
    this->show();
}
void Reader::switchPage()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
    }

}
