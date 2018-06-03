#include "reader.h"
#include "ui_reader.h"
#include<QIcon>
Reader::Reader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reader)
{
    ui->setupUi(this);
    handleEvents();

    QIcon searchImage(":/image/search.jpg");
    ui->search->setIcon(searchImage);
    ui->search->setIconSize(QSize(85,46));
    ui->search->setFlat(true);;


}

Reader::~Reader()
{
    delete ui;
}


void Reader::showReaderwin()
{
    this->show();
}
void Reader::closeReaderwin()
{
    this->close();
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

void Reader::handleEvents()
{

    connect(ui->switchtwo,&QPushButton::clicked,this,&Reader::switchPage);
    connect(ui->goodfind,&QPushButton::clicked,this,&Reader::switchPage);


    connect(ui->search,&QPushButton::clicked,
            [=]()
    {
        ui->searchResult->setText("图书名称\n作者姓名\n出版社\n价格\n出版年份\n"
                                  "图书名称\n作者姓名\n出版社\n价格\n出版年份\n"
                                  "图书名称\n作者姓名\n出版社\n价格\n出版年份\n");
    });
}
