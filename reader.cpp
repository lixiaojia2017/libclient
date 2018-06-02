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
    connect(ui->switchtwo,&QPushButton::clicked,this,&Reader)

}

Reader::~Reader()
{
    delete ui;
}
void Reader::showwin()
{
    this->show();
}
