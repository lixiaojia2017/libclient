#include "login.h"
#include "ui_login.h"
#include "new_user.h"
#include<QKeyEvent>
//#include<QDebug>
#include<QDialog>
#include<QLabel>
#include<QFrame>
#include<QHBoxLayout>
#include<QFile>
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    handleEvents();
    //ui->centralWidget->setStyleSheet("background-color:white");
    initStyle();
}
Login::~Login()
{
    delete ui;

}

void Login::handleEvents() // 信号槽事件处理
{
    connect(ui->LI,&QPushButton::clicked,
            [=]()
    {
        success = this->login();
            if(success == true)
            {
                if(getIdentity())
                {
                    emit showAdministratorwin();
                    emit closeReaderwin();
                }
                else
                {
                    emit showReaderwin();
                    emit closeAdministratorwin();
                }
                this->close();

            }
            else
            {
                QMessageBox::about(this,"Login failed","Wrong password");
            }
    });


    connect(ui->new_2,&QPushButton::clicked,
            [=]()
    {
        this->newuser.show();
    });

    connect(ui->find_password,&QPushButton::clicked,
            [=]()
    {
        this->findPassword.show();
    });

    connect(ui->LE_password, &QLineEdit::returnPressed, [this] {
        ui->LI->click();
    });
}
bool Login::login()
{
    QString str1 = ui->LE_username->text();
    QString str2 = ui->LE_password->text();
    if(str2 == "123")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Login::getIdentity()
{
    if(ui->identity->currentText() == "Administrator")
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Login::initStyle()
{
      //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
