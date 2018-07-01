#include "reader.h"
#include "ui_reader.h"
#include<QIcon>
#include<QFont>
#include<QTableWidget>
#include<QPixmap>
#include<QLabel>
#include<QFrame>
#include<QDialog>

int Pages = 1;


#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

Reader::Reader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reader)
{
    ui->setupUi(this);
    handleEvents();

    this->setWindowTitle("图书管理");

    QIcon searchImage(":/image/search.png");
    ui->search->setIcon(searchImage);
    ui->search->setIconSize(QSize(85,46));
    ui->search->setFlat(true);
}

Reader::~Reader()
{
    delete ui;
}

void Reader::setServer(QString addr, int p)
{
  serverAddr = addr;
  serverport = p;
}

void Reader::showReaderwin(QString& t,QString& addr,int p)
{
    token = t;
    setServer(addr,p);
    ui->tabWidget->removeTab(5);
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);
    ui->tabWidget->removeTab(2);
    ui->deletebook_2->hide();
    ui->changebook_2->hide();
    ui->changebookgroup->hide();
    this->show();
}
void Reader::showAdministratorwin(QString& t,QString& addr,int p)
{
    token = t;
    setServer(addr,p);
    ui->appointborrow->hide();
    ui->appointreturn->hide();
    this->show();
}
//切换界面，仅仅ui使用
void Reader::switchPage(int i)
{
    switch(i)
    {
    case GOOD_FIND:
        ui->searchStackedWidget->setCurrentIndex(1);
        break;
    case _FIND:
        ui->searchStackedWidget->setCurrentIndex(0);
        break;
    case ADD_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(0);
        break;
    case DELETE_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(1);
        break;
    case MODIFY_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(2);
        break;
    case MODIFY_BOOK_GROUP:
        ui->OPERATEBOOK->setCurrentIndex(3);
        break;
    case ADD_READER:
        ui->readerStackedWidget->setCurrentIndex(0);
        break;
    case DELETE_READER:
        ui->readerStackedWidget->setCurrentIndex(1);
        break;
    case MODIFY_READER_GROUP:
        ui->readerStackedWidget->setCurrentIndex(2);
        break;
    case ADD_GROUP:
        ui->groupStackedWidget->setCurrentIndex(0);
        break;
    case DELETE_GROUP:
        ui->groupStackedWidget->setCurrentIndex(1);
        break;
    case MODIFY_GROUP:
        ui->groupStackedWidget->setCurrentIndex(2);
        break;
    case BORROW_BOOK:
        ui->brbookStackedWidget->setCurrentIndex(0);
        break;
    case RETURN_BOOK:
        ui->brbookStackedWidget->setCurrentIndex(1);
        break;
    }
}
//生成表格
void Reader::Result(QTableWidget* tab)
{

    //创建表中各项及初始化结果
    tab->setRowCount(10);
    //tab->horizontalHeader()->setDefaultSectionSize(150);//宽度//应该可以不用设置
    tab->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头颜色
    tab->horizontalHeader()->setFixedHeight(40);//表头高度固定
    tab->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    QStringList header;//表格标题
    if(tab==ui->searchResult || tab==ui->searchResult_2||tab==ui->searchResult_5)
    {
        tab->setColumnCount(14);//设置列数
        header<<tr("选择图书")<<tr("封面")<<tr("ID")<<tr("书名")<<tr("groupID")
             <<tr("作者")<<tr("出版社")<<tr("tags")<<tr("ISBN")<<tr("价格")<<tr("页数")
            <<tr("书架号")<<tr("入馆时间")<<tr("Available");
    }
    else if(tab==ui->searchResult_3||tab==ui->searchResult_4)//借还申请
    {
        tab->setColumnCount(15);//设置列数
        header<<tr("选择图书")<<tr("借阅编号")<<tr("封面")<<tr("ID")<<tr("书名")<<tr("groupID")
             <<tr("作者")<<tr("出版社")<<tr("tags")<<tr("ISBN")<<tr("价格")<<tr("页数")
            <<tr("书架号")<<tr("入馆时间")<<tr("Available");
    }
    else if(tab==ui->searchResult_6)//删除用户
    {
        tab->setColumnCount(18);//设置列数
        header<<tr("选择读者")<<tr("用户名")<<tr("userID")<<tr("groupID")
             <<tr("昵称")<<tr("性别")<<tr("手机")<<tr("邮箱");
    }
    else if(tab==ui->searchResult_7)//修改图书组
    {//内容自动获取，无需搜索添加
        tab->setColumnCount(12);//设置列数
        header<<tr("选择图书")<<tr("ID")<<tr("书名")<<tr("groupID")
             <<tr("作者")<<tr("出版社")<<tr("tags")<<tr("ISBN")<<tr("价格")<<tr("页数")
            <<tr("书架号")<<tr("入馆时间");
    }
    tab->setHorizontalHeaderLabels(header);  //标签
}

void Reader::ADDITEM(QTableWidget *tab, int)
{
    if(tab==ui->searchResult)
    {
        for(int i=0;i<10;i++)
        {

            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);

            tab->setItem(i,2,new QTableWidgetItem("36"));//添加内容
            tab->setItem(i,3,new QTableWidgetItem("《藏地密码》"));//添加内容
            tab->setItem(i,4,new QTableWidgetItem("6"));//添加内容
            tab->setItem(i,5,new QTableWidgetItem("何马"));//添加内容
            tab->setItem(i,6,new QTableWidgetItem("……出版社"));//添加内容
            tab->setItem(i,7,new QTableWidgetItem("……tags"));//添加内容
            tab->setItem(i,8,new QTableWidgetItem("……IBSN"));//添加内容
            tab->setItem(i,9,new QTableWidgetItem("299.98"));//添加内容
            tab->setItem(i,10,new QTableWidgetItem("1099"));//添加内容
            tab->setItem(i,11,new QTableWidgetItem("1-23"));//添加内容
            tab->setItem(i,12,new QTableWidgetItem("2010-1-1"));//添加内容

            QTableWidgetItem *checkBox2 = new QTableWidgetItem();
            checkBox2->setCheckState(Qt::Checked);
            checkBox2->setText("Available");
            tab->setItem(i, 13, checkBox2);
        }
    }
    if(tab==ui->searchResult)
    {

    }
}




//事件处理函数重载
void Reader::handleEvents()
{
    //search切换
    connect(ui->GOODFIND,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(GOOD_FIND);
    });
    connect(ui->FIND,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(_FIND);
    });

    //book添加删除修改信息页面切换
    connect(ui->ADDBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_BOOK);
    });
    connect(ui->DELETEBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(DELETE_BOOK);
        Result(ui->searchResult_5);//删除图书界面操作
    });
    connect(ui->MODIFYBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_BOOK);
    });
    connect(ui->MODIFYBOOKGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_BOOK_GROUP);
        Result(ui->searchResult_7);
    });

    //reader添加删除修改信息页面切换
    connect(ui->ADDREADER,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_READER);
        ui->groupid->clear();
        ui->groupid->addItem(tr("li"));//给下拉框添加内容
        ui->groupid->addItem(tr("li"));
    });
    connect(ui->DELETEREADER,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(DELETE_READER);
        Result(ui->searchResult_6);//读者界面初始化-显示所有读者信息
    });
    connect(ui->MODIFYREADERGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_READER_GROUP);
    });

    //group添加删除修改信息页面切换
    connect(ui->ADDGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_GROUP);
    });
    connect(ui->DELETEGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(DELETE_GROUP);
    });
    connect(ui->MODIFYGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_GROUP);
    });

    //借还管理界面切换
    connect(ui->BORROWBOOK,&QPushButton::clicked,
    [=]()
    {
        Reader::switchPage(BORROW_BOOK);
    });
    connect(ui->RETURNBOOK,&QPushButton::clicked,
    [=]()
    {
        Reader::switchPage(RETURN_BOOK);
    });
    //查询按钮
    //图书查询
    connect(ui->search,&QPushButton::clicked,
            [=]()
    {
        Result(ui->searchResult);
        Pages=1;
        ADDITEM(ui->searchResult,Pages);
    });
    //删除图书查询
    connect(ui->search_2,&QPushButton::clicked,
            [=]()
    {       
        Result(ui->searchResult_5);
        Pages=1;
        ADDITEM(ui->searchResult_5,Pages);
    });
    //删除读者查询
    connect(ui->search_3,&QPushButton::clicked,
            [=]()
    {
        Result(ui->searchResult_6);
        Pages=1;
        ADDITEM(ui->searchResult_6,Pages);
    });

    connect(ui->BACK,&QPushButton::clicked,
            [=]()
    {
        ui->BOOKVIEW->setCurrentIndex(0);
    });


    connect(ui->changebook_2,&QPushButton::clicked,
            [=]()
    {
        ui->tabWidget->setCurrentIndex(3);
        ui->OPERATEBOOK->setCurrentIndex(2);
        for(int i=0;i<10;i++)
        {
            if(ui->searchResult->item(i,0)->checkState()==Qt::Checked)
            {
                ui->name_3->setText(ui->searchResult->item(i,3)->text());
                ui->author_3->setText(ui->searchResult->item(i,5)->text());
                ui->press_3->setText(ui->searchResult->item(i,6)->text());
                ui->ISBN_3->setText(ui->searchResult->item(i,8)->text());
                ui->pages_3->setText(ui->searchResult->item(i,10)->text());
                ui->piece_3->setText(ui->searchResult->item(i,9)->text());
                ui->tags_3->setText(ui->searchResult->item(i,7)->text());
                ui->groupid_3->setText(ui->searchResult->item(i,4)->text());
                ui->bookcase_3->setText(ui->searchResult->item(i,11)->text());
                if(ui->searchResult->item(i,13)->checkState()==Qt::Checked)
                {
                    ui->available_3->setCheckState(Qt::Checked);
                }
                break;
            }
        }
    });
    connect(ui->changebookgroup,&QPushButton::clicked,
            [=]()
    {
        ui->tabWidget->setCurrentIndex(3);
        ui->OPERATEBOOK->setCurrentIndex(3);
        Result(ui->searchResult_7);
        for(int i=0,k=0;i<10;i++)
        {
            if(ui->searchResult->item(i,0)!=nullptr && ui->searchResult->item(i,0)->checkState()==Qt::Checked)
            {
                QTableWidgetItem *checkBox = new QTableWidgetItem();
                checkBox->setCheckState(Qt::Unchecked);
                checkBox->setText("是否删除");
                ui->searchResult_7->setItem(k, 0, checkBox);

                for(int j=2;j<13;j++)
                {
                     ui->searchResult_7->setItem(k,j-1,new QTableWidgetItem(ui->searchResult->item(i,j)->text()));//添加内容
                }
                k++;
            }
        }
    });

}


//槽函数
void Reader::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0)
    {
        Result(ui->searchResult);//初始化为数据库前十本书
        ADDITEM(ui->searchResult,0);
    }
    else if(index == 1)
    {
        Result(ui->searchResult_2);//已借阅图书-初始化时的内容即为其真实内容
        ADDITEM(ui->searchResult_2,0);
    }
    else if(index == 2)
    {
        Result(ui->searchResult_3);//借阅申请—初始化时的内容即为其真实内容
        ADDITEM(ui->searchResult_3,0);
        Result(ui->searchResult_4);//归还申请-初始化时的内容即为其真实内容
        ADDITEM(ui->searchResult_4,0);
    }
}


void Reader::on_logout_clicked()
{
    ui->logout->setEnabled(false);
    userlogout rqt(token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        this->close();
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        this->close();
    });
    connect(thr,&SocketThread::onSuccess,this,[&]()
    {
        this->close();
    });
    thr->start();
}

void Reader::on_searchResult_cellDoubleClicked(int row, int column)
{
     ui->BOOKVIEW->setCurrentIndex(1);
}



