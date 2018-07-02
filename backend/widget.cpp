#include "widget.h"
#include "ui_widget.h"
#include "requestconstructor.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    RequestConstructor rc(ui->frame);
    QJsonDocument js=*(rc.getResult());
    QString jstr=js.toJson();
    ui->label->setText(jstr);
}
