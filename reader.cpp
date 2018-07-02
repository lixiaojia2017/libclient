#include "reader.h"
#include "ui_reader.h"
#include<QIcon>
#include<QFont>
#include<QTableWidget>
#include<QPixmap>
#include<QLabel>
#include<QFrame>
#include<QDialog>
#include<QMessageBox>
#define RESTORE(b)   ui->b->setEnabled(true);\
    wait.close();
#include <QFileDialog>
#include<QFile>
#include<QDebug>
#include "backend/token.h"
#include "backend/handle/constructer/operateuserconstructer.h"
#include <QTime>
#include"backend/handle/constructer/appointconstructer.h"
#include "backend/handle/constructer/operategroupconstructer.h"
#include "backend/handle/constructer/operatebookconstructer.h"
int Pages = 1,Group = 0,Iden = 0;


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
    connect(ui->search,&QPushButton::clicked,this,&Reader::reset_page);
    connect(ui->pushButton_13,&QPushButton::clicked,this,&Reader::reset_page);
}

Reader::~Reader()
{
    delete ui;
}


void Reader::setUsername(const QString _username)
{
    username = _username;
}

void Reader::setServer(QString addr, int p)
{
    serverAddr = addr;
    serverport = p;
}

void Reader::showReaderwin(QString& t,QString& addr,int p,int ID)
{
    token = t;
    userID=ID;
    setServer(addr,p);
    ui->tabWidget->removeTab(7);
    ui->tabWidget->removeTab(5);
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);
    ui->tabWidget->removeTab(2);
    ui->deletebook_2->hide();
    ui->changebook_2->hide();
    ui->cover->hide();
    ui->changebookgroup->hide();
    Iden = READER_IDENTITY;
    this->show();
}
void Reader::showAdministratorwin(QString& t,QString& addr,int p,int ID)
{
    token = t;
    userID=ID;
    ui->tabWidget->removeTab(1);
    setServer(addr,p);
    ui->cover->hide();
    ui->appointborrowpushbutton->hide();
    Iden = STAFFS_IDENTITY;
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
    case MODIFY_BOOK:
        ui->OPERATEBOOK->setCurrentIndex(1);
        break;
    case MODIFY_BOOK_GROUP:
        ui->OPERATEBOOK->setCurrentIndex(2);
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
    if(tab==ui->searchResult)
    {
        tab->setColumnCount(14);//设置列数
        header<<tr("选择图书")<<tr("封面")<<tr("ID")<<tr("书名")<<tr("groupID")
             <<tr("作者")<<tr("出版社")<<tr("tags")<<tr("ISBN")<<tr("价格")<<tr("页数")
            <<tr("书架号")<<tr("入馆时间")<<tr("Available");
    }
    else if(tab==ui->searchResult_2)
    {
        tab->setColumnCount(7);//设置列数
        header<<tr("选择图书")<<tr("借阅编号")<<tr("读者编号")<<tr("图书编号")
             <<tr("借书时间")<<tr("归还期限")<<tr("可续借次数");
    }
    else if(tab==ui->searchResult_3)//借还申请
    {
        tab->setColumnCount(5);//设置列数
        header<<tr("选择图书")<<tr("ID")<<tr("读者编号")
             <<tr("图书编号")<<tr("预约时间");
    }
    else if(tab==ui->searchResult_4)
    {
        tab->setColumnCount(6);//设置列数
        header<<tr("选择图书")<<tr("ID")<<tr("读者编号")
             <<tr("图书编号")<<tr("预约时间")<<tr("借阅ID");
    }
    else if(tab==ui->searchResult_6)//删除用户
    {
        tab->setColumnCount(8);//设置列数
        header<<tr("选择读者")<<tr("用户名")<<tr("userID")<<tr("groupID")
             <<tr("昵称")<<tr("性别")<<tr("手机")<<tr("邮箱");
    }
    else if(tab==ui->searchResult_7)//修改图书组
    {//内容自动获取，无需搜索添加,与searchResult有关
        tab->setColumnCount(11);//设置列数
        header<<tr("ID")<<tr("书名")<<tr("groupID")
             <<tr("作者")<<tr("出版社")<<tr("tags")<<tr("ISBN")<<tr("价格")<<tr("页数")
            <<tr("书架号")<<tr("入馆时间");
    }
    else if(tab==ui->searchResult_8&&Group == BOOK_GROUP_SEARCH)
    {
        tab->setRowCount(1);
        tab->setColumnCount(3);//设置列数
        header<<tr("选择组")<<tr("组名")<<tr("最大借出时间");
    }
    else if(tab==ui->searchResult_8&&Group == READER_GROUP_SEARCH)
    {
        tab->setRowCount(1);
        tab->setColumnCount(4);//设置列数
        header<<tr("选择组")<<tr("组名")<<tr("可借书数量")<<tr("可借书时间")<<tr("可续借次数");
    }
    else if(tab==ui->searchResult_9)
    {//内容自动获取，无需添加
        tab->setColumnCount(7);
        header<<tr("用户名")<<tr("userID")<<tr("groupID")
             <<tr("昵称")<<tr("性别")<<tr("手机")<<tr("邮箱");
    }
    else if(tab==ui->searchResult_10)
    {
        tab->setColumnCount(4);
        tab->horizontalHeader()->resizeSection(0,100);
        tab->horizontalHeader()->resizeSection(1,200);
        tab->horizontalHeader()->resizeSection(2,500);
        tab->horizontalHeader()->resizeSection(3,300);
        header<<tr("ID")<<tr("类型")<<tr("内容")<<tr("时间");
    }
    tab->setHorizontalHeaderLabels(header);  //标签
}

void Reader::ADDITEM(QTableWidget *tab,infoanalyser& hdl)
{
    int i=0;
    if(tab==ui->searchResult)
    {
        for(auto iter : hdl.info)
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);

            tab->setItem(i,2,new QTableWidgetItem(iter->take("ID").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("name").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("groupID").toString()));//添加内容
            tab->setItem(i,5,new QTableWidgetItem(iter->take("author").toString()));//添加内容
            tab->setItem(i,6,new QTableWidgetItem(iter->take("press").toString()));//添加内容

            QString tags;
            for(auto _take_tags : iter->take("tags").toList())
            {
                tags += (_take_tags.toString()+",");
            }
            tags=tags.left(tags.length()-1);

            tab->setItem(i,7,new QTableWidgetItem(tags));//添加内容
            tab->setItem(i,8,new QTableWidgetItem(iter->take("ISBN").toString()));//添加内容
            tab->setItem(i,9,new QTableWidgetItem(iter->take("price").toString()));//添加内容
            tab->setItem(i,10,new QTableWidgetItem(iter->take("pages").toString()));//添加内容
            tab->setItem(i,11,new QTableWidgetItem(iter->take("bookcase").toString()));//添加内容
            tab->setItem(i,12,new QTableWidgetItem(iter->take("inTime").toString()));//添加内容

            QTableWidgetItem *checkBox2 = new QTableWidgetItem();
            if(iter->take("available")==true)
            {
                checkBox2->setCheckState(Qt::Checked);
            }
            else{
                checkBox2->setCheckState(Qt::Unchecked);
            }
            checkBox2->setText("Available");
            tab->setItem(i, 13, checkBox2);
            i++;
        }
    }
    else if(tab==ui->searchResult_2){
        for(auto iter : hdl.info)
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);
            tab->setItem(i,1,new QTableWidgetItem(iter->take("ID").toString()));//添加内容
            tab->setItem(i,2,new QTableWidgetItem(iter->take("readerid").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("bookid").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("borrowtime").toString()));//添加内容
            tab->setItem(i,5,new QTableWidgetItem(iter->take("exptime").toString()));//添加内容
            tab->setItem(i,6,new QTableWidgetItem(iter->take("remaintime").toString()));//添
            i++;
        }
    }
    else if(tab==ui->searchResult_3)
    {
        for(auto iter : hdl.info)
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);

            tab->setItem(i,1,new QTableWidgetItem(iter->take("ID").toString()));//借阅编号
            qDebug() << iter->take("ID").toString();
            tab->setItem(i,2,new QTableWidgetItem(iter->take("readerid").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("bookid").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("appointtime").toString()));//添加内容
            i++;
        }
    }
    else if(tab==ui->searchResult_4){
        for(auto iter : hdl.info)
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);

            tab->setItem(i,1,new QTableWidgetItem(iter->take("ID").toString()));//借阅编号
            tab->setItem(i,2,new QTableWidgetItem(iter->take("readerid").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("bookid").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("appointtime").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("borrowid").toString()));//添加内容
            i++;
        }
    }
    else if(tab==ui->searchResult_6){
        for(auto iter : hdl.info)
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);
            tab->setItem(i,1,new QTableWidgetItem(iter->take("username").toString()));//添加内容
            tab->setItem(i,2,new QTableWidgetItem(iter->take("ID").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("groupid").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("name").toString()));//添加内容
            tab->setItem(i,5,new QTableWidgetItem(iter->take("sex").toString()));//添加内容
            tab->setItem(i,6,new QTableWidgetItem(iter->take("tel").toString()));//添加内容
            tab->setItem(i,7,new QTableWidgetItem(iter->take("email").toString()));//添加内容
            i++;
        }
    }
    else if(tab==ui->searchResult_8&&Group==BOOK_GROUP_SEARCH ){
        for(auto iter : hdl.info)//仅仅支持传入一个参数，即info中只有一条信息，下面一个与此相同
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);
            tab->setItem(i,1,new QTableWidgetItem(iter->take("name").toString()));//添加内容
            tab->setItem(i,2,new QTableWidgetItem(iter->take("max_time").toString()));//添加内容
            i++;
        }
    }
    else if(tab==ui->searchResult_8&&Group==READER_GROUP_SEARCH ){
        for(auto iter : hdl.info)
        {
            QTableWidgetItem *checkBox1 = new QTableWidgetItem();
            checkBox1->setCheckState(Qt::Unchecked);
            checkBox1->setText("勾选启用");
            tab->setItem(i, 0, checkBox1);
            tab->setItem(i,1,new QTableWidgetItem(iter->take("name").toString()));//添加内容
            tab->setItem(i,2,new QTableWidgetItem(iter->take("max_borrow_num").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("max_borrow_time").toString()));//添加内容
            tab->setItem(i,4,new QTableWidgetItem(iter->take("max_renew_time").toString()));//添加内容
            i++;
        }
    }
    else if(tab==ui->searchResult_10){
        for(auto iter : hdl.info)
        {
            tab->setItem(i,0,new QTableWidgetItem(iter->take("ID").toString()));//添加内容
            tab->setItem(i,1,new QTableWidgetItem(iter->take("type").toString()));//添加内容
            tab->setItem(i,2,new QTableWidgetItem(iter->take("content").toString()));//添加内容
            tab->setItem(i,3,new QTableWidgetItem(iter->take("time").toString()));//添加内容
            i++;
        }
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
        ui->searchLineedit->clear();
    });
    connect(ui->FIND,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(_FIND);
        ui->name->clear();
        ui->author->clear();
        ui->press->clear();
        ui->ISBN->clear();
        ui->ID->clear();
        ui->price->clear();
        ui->tags->clear();
        ui->bookcase->clear();
        ui->available->setCheckState(Qt::Unchecked);
        ui->checkif->setCheckState(Qt::Unchecked);


    });

    //book添加删除修改信息页面切换
    connect(ui->ADDBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_BOOK);
    });
    connect(ui->MODIFYBOOK,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_BOOK);
        ui->bookId->clear();
        ui->name_3->clear();
        ui->author_3->clear();
        ui->press_3->clear();
        ui->ISBN_3->clear();
        ui->pages_3->clear();
        ui->price_3->clear();
        ui->tags_3->clear();
        ui->groupid_3->clear();
        ui->bookcase_3->clear();
        ui->available_3->setCheckState(Qt::Unchecked);
    });
    connect(ui->MODIFYBOOKGROUP,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(MODIFY_BOOK_GROUP);
        Result(ui->searchResult_7);
        ui->searchResult_7->clear();
    });

    //reader添加删除修改信息页面切换
    connect(ui->ADDREADER,&QPushButton::clicked,
            [=]()
    {
        Reader::switchPage(ADD_READER);
        /*ui->groupid->clear();
        ui->groupid->addItem(tr("li"));*///给下拉框添加内容
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
        ui->bookGroupid->clear();
        ui->name_7->clear();
        ui->max_time_2->clear();
        ui->readerGroupid->clear();
        ui->name_8->clear();
        ui->max_borrow_num_2->clear();
        ui->max_borrow_time_2->clear();
        ui->max_renew_time_2->clear();
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
        //        ADDITEM(ui->searchResult,Pages);
    });
    //删除读者查询
    connect(ui->search_3,&QPushButton::clicked,
            [=]()
    {
        Result(ui->searchResult_6);
        Pages=1;
        //        ADDITEM(ui->searchResult_6,Pages);
    });
    //search界面更改图书信息按钮
    connect(ui->changebook_2,&QPushButton::clicked,
            [=]()
    {
        ui->tabWidget->setCurrentIndex(2);
        ui->OPERATEBOOK->setCurrentIndex(2);
        for(int i=0;i<10;i++)
        {
            if(ui->searchResult->item(i,0)->checkState()==Qt::Checked)
            {
                ui->bookId->setText(ui->searchResult->item(i,2)->text());
                ui->name_3->setText(ui->searchResult->item(i,3)->text());
                ui->author_3->setText(ui->searchResult->item(i,5)->text());
                ui->press_3->setText(ui->searchResult->item(i,6)->text());
                ui->ISBN_3->setText(ui->searchResult->item(i,8)->text());
                ui->pages_3->setText(ui->searchResult->item(i,10)->text());
                ui->price_3->setText(ui->searchResult->item(i,9)->text());
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
        ui->tabWidget->setCurrentIndex(2);
        ui->OPERATEBOOK->setCurrentIndex(3);
        Result(ui->searchResult_7);
        for(int i=0,k=0;i<10;i++)
        {
            if(ui->searchResult->item(i,0)!=nullptr && ui->searchResult->item(i,0)->checkState()==Qt::Checked)
            {

                for(int j=2;j<13;j++)
                {
                    ui->searchResult_7->setItem(k,j-2,new QTableWidgetItem(ui->searchResult->item(i,j)->text()));//添加内容
                }
                k++;
            }
        }
    });

    //查询读者组、查询图书组按钮
    connect(ui->searchBookgroup,&QPushButton::clicked,
            [=]()
    {
        Group = BOOK_GROUP_SEARCH;
        Result(ui->searchResult_8);

    });
    connect(ui->searchReadergroup,&QPushButton::clicked,
            [=]()
    {
        Group = READER_GROUP_SEARCH;
        Result(ui->searchResult_8);

    });
    //“删除组”按钮
    connect(ui->deleteGroup,&QPushButton::clicked,
            [=]()
    {
        //获取内容，发送删除信息
    });
    //修改组信息
    connect(ui->changeGroup,&QPushButton::clicked,
            [=]()
    {
        ui->groupStackedWidget->setCurrentIndex(2);
        if(ui->searchResult_8->item(0,0)!=nullptr&&ui->searchResult_8->item(0,0)->checkState()==Qt::Checked)
        {
            if(Group==BOOK_GROUP_SEARCH)
            {
                ui->bookGroupid->setText(ui->groupid_4->text());
                ui->name_7->setText(ui->searchResult_8->item(0,1)->text());
                ui->max_time_2->setText(ui->searchResult_8->item(0,2)->text());
            }
            else if(Group==READER_GROUP_SEARCH)
            {
                ui->readerGroupid->setText(ui->groupid_4->text());
                ui->name_8->setText(ui->searchResult_8->item(0,1)->text());
                ui->max_borrow_num_2->setText(ui->searchResult_8->item(0,2)->text());
                ui->max_borrow_time_2->setText(ui->searchResult_8->item(0,3)->text());
                ui->max_renew_time_2->setText(ui->searchResult_8->item(0,4)->text());
            }
        }
    });

    //修改读者组
    connect(ui->changeReadergroup,&QPushButton::clicked,
            [=]()
    {
        ui->readerStackedWidget->setCurrentIndex(2);
        Result(ui->searchResult_9);
        for(int i=0,k=0;i<10;i++)
        {
            if(ui->searchResult_6->item(i,0)!=nullptr && ui->searchResult_6->item(i,0)->checkState()==Qt::Checked)
            {

                for(int j=1; j<8; j++)
                {
                    ui->searchResult_9->setItem(k,j-1,new QTableWidgetItem(ui->searchResult_6->item(i,j)->text()));//添加内容
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
        //        ADDITEM(ui->searchResult,0);
        ui->searchLineedit->clear();
        ui->name->clear();
        ui->author->clear();
        ui->press->clear();
        ui->ISBN->clear();
        ui->ID->clear();
        ui->price->clear();
        ui->tags->clear();
        ui->bookcase->clear();
        ui->available->setCheckState(Qt::Unchecked);
        ui->checkif->setCheckState(Qt::Unchecked);
    }
    if(Iden == READER_IDENTITY)
    {
        if(index == 1)
        {
            const QString prefix = "$dbPrefix$";
            QString sql="SELECT "+prefix+"currborrow.ID,"+prefix+"currborrow.readerid,"+prefix+"currborrow.bookid,"\
                +prefix+"currborrow.borrowtime,"+prefix+"currborrow.exptime,"+prefix+"currborrow.remaintime,"\
                +prefix+"books.name FROM "+prefix+"currborrow,"+prefix+"books WHERE "+prefix+"currborrow.bookid="\
                +prefix+"books.ID AND"+prefix+"currborrow.readerid=";
            // need limit here
            queryinfo rqt(sql,token);
            SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
            connect(thr,&SocketThread::connectFailed,this,[&](){
                QMessageBox::about(this,"Failed","Connection failed. Unable to fetch user info");
            });
            connect(thr,&SocketThread::badResponse,this,[&](){
                QMessageBox::about(this,"Failed","Server error. Unable to fetch user info");
            });
            connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
            {
                infoanalyser hdl(*rsp);
                if(hdl.result)
                {
                    requested = true;
                    for(auto iter: hdl.info)
                    {
                        ui->label_18->setText(iter->take("username").toString());
                        ui->name_4->setText(iter->take("name").toString());
                        ui->email->setText(iter->take("email").toString());
                        ui->sex->setCurrentText(iter->take("sex").toString());
                        ui->tel->setText(iter->take("tel").toString());
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Warning","Unable to get user info. Maybe user is not properly set?");
                }
                // get result
            });
            thr->start();
            Result(ui->searchResult_2);//已借阅图书-初始化时的内容即为其真实内容
        }//else if(index==3)
        //{
        //    Result(ui->searchResult_10);
        //}
        else if(index== 2)
        {
            if(!requested)
            {
                queryinfo rqt({"ID"},1,1,"readers","username='"+username+"'",token);
                SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
                connect(thr,&SocketThread::connectFailed,this,[&](){
                    QMessageBox::about(this,"Failed","Connection failed. Unable to fetch user info");
                });
                connect(thr,&SocketThread::badResponse,this,[&](){
                    QMessageBox::about(this,"Failed","Server error. Unable to fetch user info");
                });
                connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
                {
                    infoanalyser hdl(*rsp);
                    if(hdl.result && !hdl.info.isEmpty())
                    {
                        requested = true;
                        for(auto iter: hdl.info)
                        {
                            ui->label_18->setText(iter->take("username").toString());
                            ui->name_4->setText(iter->take("name").toString());
                            ui->email->setText(iter->take("email").toString());
                            ui->sex->setCurrentText(iter->take("sex").toString());
                            ui->tel->setText(iter->take("tel").toString());
                        }
                    }
                    else
                    {
                        QMessageBox::warning(this,"Warning","Unable to get user info. Maybe user is not properly set?");
                    }
                    // get result
                });
                thr->start();
            }
        }
    }
    else if(Iden == STAFFS_IDENTITY)
    {
        if(index == 1)
        {
            Pages = 1;
            if(ui->brbookStackedWidget->currentIndex() == 0)
            {
                Result(ui->searchResult_3);//借阅申请—初始化时的内容即为其真实内容
                queryinfo rqt1({"ID"}, 10, 1, "currappoint", "type = 'borrow'", token);
                SocketThread* sktBorrow = new SocketThread(serverAddr,serverport, rqt1.GetReturn());
                connect(sktBorrow,&SocketThread::connectFailed,this,[&](){
                    QMessageBox::about(this,"Failed","Connection failed. Unable to fetch user info");
                });
                connect(sktBorrow,&SocketThread::badResponse,this,[&](){
                    QMessageBox::about(this,"Failed","Server error. Unable to fetch user info");
                });
                connect(sktBorrow,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
                {
                    infoanalyser hdl(*rsp);
                    if(hdl.result)
                    {
                        ADDITEM(ui->searchResult_3, hdl);
                    }
                    else
                    {
                        QMessageBox::warning(this,"Warning","Unable to get the info. Maybe user is not properly set?");
                    }
                });
                sktBorrow->start();
            }
            else
            {
                Result(ui->searchResult_4);//归还申请-初始化时的内容即为其真实内容
                queryinfo rqt2({"ID"}, 10, 1, "currappoint", "type = 'return'", token);
                SocketThread* sktReturn = new SocketThread(serverAddr,serverport, rqt2.GetReturn());
                connect(sktReturn,&SocketThread::connectFailed,this,[&](){
                    QMessageBox::about(this,"Failed","Connection failed. Unable to fetch user info");
                });
                connect(sktReturn,&SocketThread::badResponse,this,[&](){
                    QMessageBox::about(this,"Failed","Server error. Unable to fetch user info");
                });
                connect(sktReturn,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
                {
                    infoanalyser hdl(*rsp);
                    if(hdl.result)
                    {
                        ADDITEM(ui->searchResult_4, hdl);
                    }
                    else
                    {
                        QMessageBox::warning(this,"Warning","Unable to get the info. Maybe user is not properly set?");
                    }
                });
                sktReturn->start();
            }
        }
        else if(index == 2)
        {
            ui->searchResult_7->clear();
            ui->bookId->clear();
            ui->name_3->clear();
            ui->author_3->clear();
            ui->press_3->clear();
            ui->ISBN_3->clear();
            ui->pages_3->clear();
            ui->price_3->clear();
            ui->tags_3->clear();
            ui->groupid_3->clear();
            ui->bookcase_3->clear();
            ui->available_3->setCheckState(Qt::Unchecked);
        }
        else if(index == 4)
        {
            ui->bookGroupid->clear();
            ui->name_7->clear();
            ui->max_time_2->clear();
            ui->readerGroupid->clear();
            ui->name_8->clear();
            ui->max_borrow_num_2->clear();
            ui->max_borrow_time_2->clear();
            ui->max_renew_time_2->clear();
        }
        else if(index == 5)
        {
            if(!requested)
            {
                queryinfo rqt({"ID"},1,1,"staffs","username='"+username+"'",token);
                SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
                connect(thr,&SocketThread::connectFailed,this,[&](){
                    QMessageBox::about(this,"Failed","Connection failed. Unable to fetch user info");
                });
                connect(thr,&SocketThread::badResponse,this,[&](){
                    QMessageBox::about(this,"Failed","Server error. Unable to fetch user info");
                });
                connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
                {
                    infoanalyser hdl(*rsp);
                    if(hdl.result && !hdl.info.isEmpty())
                    {
                        requested = true;
                        for(auto iter: hdl.info)
                        {
                            ui->label_18->setText(iter->take("username").toString());
                            ui->name_4->setText(iter->take("name").toString());
                            ui->email->setText(iter->take("email").toString());
                            ui->sex->setCurrentText(iter->take("sex").toString());
                            ui->tel->setText(iter->take("tel").toString());
                        }
                    }
                    else
                    {
                        QMessageBox::warning(this,"Warning","Unable to get user info. Maybe user is not properly set?");
                    }
                    // get result
                });
                thr->start();
            }
        }
        else if(index == 6)
        {
            Result(ui->searchResult_10);
        }
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
    if(column==1&&ui->searchResult->item(row,column)==nullptr&&Iden==STAFFS_IDENTITY)
    {
        //定义文件对话框类
        QFileDialog *fileDialog = new QFileDialog(this);
        //定义文件对话框标题
        fileDialog->setWindowTitle(tr("打开图片"));
        //设置默认文件路径
        fileDialog->setDirectory(".");
        //设置文件过滤器
        fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
        //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
        fileDialog->setFileMode(QFileDialog::ExistingFiles);
        //设置视图模式
        fileDialog->setViewMode(QFileDialog::Detail);
        //打印所有选择的文件的路径
        QString fileNames;
        if(fileDialog->exec())
        {
            fileNames = fileDialog->selectedFiles().join("");
        }
        ui->cover->show();//上传封面按钮
        QLabel *coverground=new QLabel("");
        coverground->setPixmap(QPixmap(fileNames).scaled(138,200));
        ui->searchResult->setCellWidget(row,column,coverground);
    }
    else if(ui->searchResult->item(row,column)!=nullptr){
        ui->searchResult->item(row,2)->text();
        pdfreader = new PDFReader;
        pdfreader->resize(1161,893);
        pdfreader->show();
    }
}

void Reader::on_search_clicked()
{
    ui->searchResult->clear();
    Result(ui->searchResult);
    ui->search->setEnabled(false);
    wait.show();
    QList<QVariant> ord={"ID"};
    querybook rqt("intelligentsearch",ord,10,Pages,ui->searchLineedit->text(),token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(search)
                QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(search)
                QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(search)
                    ADDITEM(ui->searchResult,hdl);
        }
        else
        {
            RESTORE(search)
                    QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}

void Reader::on_last_clicked()
{
    if(Pages>1){
        Pages--;
    }
    if(ui->searchStackedWidget->currentIndex()==0)
        on_search_clicked();
    else
        on_pushButton_13_clicked();
}

void Reader::on_next_clicked()
{
    Pages++;
    if(ui->searchStackedWidget->currentIndex()==0)
        on_search_clicked();
    else
        on_pushButton_13_clicked();
}
#define TEXT(a)   ui->a->text()
#define IFNE(a) if(ui->a->text()!="")
#define NE(a) (ui->a->text()!="")
void Reader::on_pushButton_13_clicked()
{
    ui->searchResult->clear();
    Result(ui->searchResult);
    ui->pushButton_13->setEnabled(false);
    wait.show();
    QString rule=ui->checkif->checkState()?"completesearch":"fuzzysearch";
    QMap<QString,QVariant> info;
    IFNE(name)info["name"]=TEXT(name);
    IFNE(author)info["author"]=TEXT(author);
    IFNE(press)info["press"]=TEXT(press);
    IFNE(ISBN)info["ISBN"]=TEXT(ISBN);
    IFNE(ID)info["ID"]=TEXT(ID);
    if(ui->tags->text()!=""){
        QString TAG=TEXT(tags);
        QStringList tgs=TAG.split(',');
        info["tags"]=tgs;
    }
    info["available"]=ui->available->checkState();
    QList<QVariant> ord={"ID"};
    querybook rqt(rule,ord,10,Pages,info,token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(pushButton_13)
                QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(pushButton_13)
                QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(pushButton_13)
                    ADDITEM(ui->searchResult,hdl);
        }
        else
        {
            RESTORE(pushButton_13)
                    QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}

void Reader::reset_page(){
    Pages=1;
}

void Reader::on_ngetnewr_clicked()
{
    if(TEXT(pwd)!=TEXT(pwd2)){
        QMessageBox::about(this,"Failed","two passwords do not match");
        return;
    }
    ui->ngetnewr->setEnabled(false);
    wait.show();
        if(!(NE(username_0)&&NE(name_2)&&NE(tel_2)&&NE(email_2)&&NE(pwd))){
        QMessageBox::about(this,"Failed","用户信息不完整");
        RESTORE(ngetnewr)
        return;
    }
        if(!(NE(username_0)&&NE(name_2)&&NE(tel_2)&&NE(email_2)&&NE(pwd))){
        QMessageBox::about(this,"Failed","用户信息不完整");
        RESTORE(ngetnewr)
        return;
    }
    QMap<QString,QVariant> info;
    info["name"]=TEXT(name_2);
    info["username"]=TEXT(username_0);
    info["tel"]=TEXT(tel_2);
    info["email"]=TEXT(email_2);
    info["password"]=token::getMD5(TEXT(pwd));
    info["groupid"]=ui->groupid->currentText().toInt();
    createuser rqt(info,token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(ngetnewr)
                QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(ngetnewr)
                QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(ngetnewr)
                    QMessageBox::about(this,"Success","successfully added");
        }
        else
        {
            RESTORE(ngetnewr)
                    QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}

void Reader::on_changepwd_clicked()
{
    if(TEXT(newpwd)!=TEXT(newpwd2)){
        QMessageBox::about(this,"Failed","two passwords do not match");
        return;
    }
    ui->changepwd->setEnabled(false);
    wait.show();
    userchangepwd rqt(token::getMD5(TEXT(oldpwd)),token::getMD5(TEXT(newpwd)),token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(changepwd)
                QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(changepwd)
                QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(changepwd)
                    QMessageBox::about(this,"Success","password has been changed.\nlogin with new password next time");
        }
        else
        {
            RESTORE(changepwd)
                    QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}

void Reader::on_pushButton_5_clicked()
{
    ui->pushButton_5->setEnabled(false);
    wait.show();
        if(!(NE(name_4)&&NE(tel)&&NE(email))){
        QMessageBox::about(this,"Failed","用户信息不完整");
        RESTORE(pushButton_5)
        return;
    }
    QMap<QString,QVariant> info;
    info["name"]=TEXT(name_4);
    info["sex"]=ui->sex->currentText();
    info["tel"]=TEXT(tel);
    info["email"]=TEXT(email);
    userupdateinfo rqt(info,token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(pushButton_5)
                QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(pushButton_5)
                QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(pushButton_5)
                    QMessageBox::about(this,"Success","info updated");
        }
        else
        {
            RESTORE(pushButton_5)
                    QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}

void Reader::on_pushButton_6_clicked()
{

}


void Reader::on_deletebook_2_clicked()
{
    QList<QVariant> bookid;
    for(int i = 0; i < 10; i++)
    {
        if(ui->searchResult->item(i,0)!=nullptr && ui->searchResult->item(i,0)->checkState()==Qt::Checked)
        {
            bookid.append(ui->searchResult->item(i, 2)->text().toInt());
        }
    }
    if(!bookid.isEmpty())
    {
        deletebook rqt(bookid, token);
        SocketThread *skt= new SocketThread(serverAddr,serverport,rqt.GetReturn());
        connect(skt,&SocketThread::connectFailed,this,[&](){
            QMessageBox::about(this,"Failed","Connection failed. Unable to fetch user info");
        });
        connect(skt,&SocketThread::badResponse,this,[&](){
            QMessageBox::about(this,"Failed","Server error. Unable to fetch user info");
        });
        connect(skt,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
        {
            infoanalyser hdl(*rsp);
            if(hdl.result)
            {
                if(ui->searchStackedWidget->currentIndex() == 0)
                {
                    on_search_clicked();
                }
                else
                {
                    on_pushButton_13_clicked();
                }
            }
            else
            {
                QMessageBox::warning(this,"Warning","Unable to delete the books. Maybe they are not properly set?");
            }
        });
        skt->start();
    }
}

//预约借书槽函数
void Reader::on_appointborrowpushbutton_clicked()
{
    ui->appointborrowpushbutton->setEnabled(false);
    wait.show();
    QString BID;
    bool flag=false;
    for(int i=0;i<10;i++)
    {
        if(ui->searchResult->item(i,0)!=nullptr&&ui->searchResult->item(i,0)->checkState()==Qt::Checked)
        {
            flag=true;
            BID=ui->searchResult->item(i,2)->text();
            appointborrow rqt(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),BID.toInt(),token);
            SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
            connect(thr,&SocketThread::connectFailed,this,[&](){
                RESTORE(appointborrowpushbutton);
                QMessageBox::about(this,"Failed","connection timeout");
            });
            connect(thr,&SocketThread::badResponse,this,[&](){
                RESTORE(appointborrowpushbutton);
                QMessageBox::about(this,"Failed","server error");
            });
            connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
            {
                RESTORE(appointborrowpushbutton);
                infoanalyser hdl(*rsp);
                if(hdl.result){
                    QMessageBox::about(this,"Success","book appointed");
                }
                else
                {
                    QMessageBox::about(this,"Failed",hdl.detail);
                }
            });
            thr->start();
        }
    }
    appointborrow rqt(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),BID.toInt(),token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(appointborrowpushbutton)
        QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(appointborrowpushbutton)
        QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        RESTORE(appointborrowpushbutton)
        QMessageBox::about(this,"Success","The application has been successful!");
    });
    thr->start();
    if (!flag){
        QMessageBox::about(this,"Error","you have not chosen any book yet");
    }
}
//预约还书槽函数
void Reader::on_appointreturnpushbutton_clicked()
{
    ui->appointreturnpushbutton->setEnabled(false);
    wait.show();
    QString BID;
    bool flag=false;
    for(int i=0;i<10;i++)
    {
        if(ui->searchResult_2->item(i,0)!=nullptr&&ui->searchResult->item(i,0)->checkState()==Qt::Checked)
        {
            flag=true;
            BID=ui->searchResult->item(i,2)->text();
            appointreturn rqt(BID.toInt(),token);
            SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
            connect(thr,&SocketThread::connectFailed,this,[&](){
                RESTORE(appointreturnpushbutton);
                QMessageBox::about(this,"Failed","connection timeout");
            });
            connect(thr,&SocketThread::badResponse,this,[&](){
                RESTORE(appointreturnpushbutton);
                QMessageBox::about(this,"Failed","server error");
            });
            connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
            {
                RESTORE(appointreturnpushbutton)
                infoanalyser hdl(*rsp);
                if(hdl.result){
                    QMessageBox::about(this,"Success","book appointed");
                }
                else
                {
                    QMessageBox::about(this,"Failed",hdl.detail);
                }
            });
            thr->start();
        }
    }
    appointreturn rqt(BID.toInt(),token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(appointreturnpushbutton)
        QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(appointreturnpushbutton)
        QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        RESTORE(appointreturnpushbutton)
        QMessageBox::about(this,"Success","The application has been successful!");
    });
    thr->start();
    if (!flag){
        QMessageBox::about(this,"Error","you have not chosen any book yet");
    }
}

//添加图书组
void Reader::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    wait.show();
    if(!(NE(name_5)&&NE(max_borrow_num)&&NE(max_borrow_time)&&NE(max_renew_time))){
        QMessageBox::about(this,"Failed","组信息不完整");
        RESTORE(pushButton)
        return;
    }
    QMap<QString,QVariant> info;
    info["name"]=TEXT(name_5);
    info["max_borrow_num"]=TEXT(max_borrow_num).toInt();
    info["max_borrow_time"]=TEXT(max_borrow_time).toInt();
    info["max_renew_time"]=TEXT(max_renew_time).toInt();
    creategroup rqt("user",info,token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(pushButton)
        QMessageBox::about(this,"Failed","connection timeout");
        qDebug()<<1;
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(pushButton)
        QMessageBox::about(this,"Failed","server error");
        qDebug()<<2;
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(pushButton)
            QMessageBox::about(this,"Success","successfully added");
            qDebug()<<3;
        }
        else
        {
            RESTORE(pushButton)
            QMessageBox::about(this,"Failed",hdl.detail);
            qDebug()<<4;
        }
    });
    thr->start();
}
//create book
void Reader::on_createbook_clicked()
{
    ui->createbook->setEnabled(false);
    wait.show();
    if(!(NE(name_1)&&NE(press_2)&&NE(author_2)&&NE(ISBN)&&NE(pages)&&NE(piece)&&NE(tags_2)&&NE(groupID)&&NE(bookcase))){
        QMessageBox::about(this,"Failed","图书信息不完整");
        RESTORE(createbook)
        return;
    }
    QMap<QString,QVariant> info;
    info["name"]=TEXT(name_1);
    info["press"]=TEXT(press_2);
    info["author"]=TEXT(author_2);
    info["ISBN"]=TEXT(ISBN);
    info["price"]=ui->piece->text().toFloat();
    info["groupID"]=ui->groupID->text().toInt();
    info["pages"]=ui->pages->text().toInt();
    info["bookcase"]=ui->bookcase->text().toInt();
    info["available"]=ui->checkBox->checkState();
    QString TAG=TEXT(tags);
    QStringList tgs=TAG.split(',');
    info["tags"]=tgs;
    createbook rqt(info,token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        RESTORE(createbook)
        QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        RESTORE(createbook)
        QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            RESTORE(createbook)
            QMessageBox::about(this,"Success","successfully added");
        }
        else
        {
            RESTORE(createbook)
            QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}
//change book
void Reader::on_changebook_clicked()
{
    ui->changebook->setEnabled(false);
    wait.show();
    if((!(NE(name_3)&&NE(press_3)&&NE(author_3)&&NE(ISBN_3)&&NE(pages_3)&&NE(price_3)&&NE(tags_3)&&NE(groupid_3)&&NE(bookcase_3)))||ui->bookId->text()==""){
        QMessageBox::about(this,"Failed","图书信息不完整");
        ui->changebook->setEnabled(true);
        wait.close();
        return;
    }
    QMap<QString,QVariant> info;
    info["name"]=TEXT(name_3);
    info["press"]=TEXT(press_3);
    info["author"]=TEXT(author_3);
    info["ISBN"]=TEXT(ISBN_3);
    info["price"]=ui->price_3->text().toFloat();
    info["groupID"]=ui->groupid_3->text().toInt();
    info["pages"]=ui->pages_3->text().toInt();
    info["bookcase"]=ui->bookcase_3->text().toInt();
    info["available"]=ui->available_3->checkState();
    QString TAG=TEXT(tags_3);
    QStringList tgs=TAG.split(',');
    info["tags"]=tgs;
    changebook rqt(ui->bookId->text().toInt(),info,token);
    SocketThread *thr= new SocketThread(serverAddr,serverport,rqt.GetReturn());
    connect(thr,&SocketThread::connectFailed,this,[&](){
        ui->changebook->setEnabled(true);
        wait.close();
        QMessageBox::about(this,"Failed","connection timeout");
    });
    connect(thr,&SocketThread::badResponse,this,[&](){
        ui->changebook->setEnabled(true);
        wait.close();
        QMessageBox::about(this,"Failed","server error");
    });
    connect(thr,&SocketThread::onSuccess,this,[&](QJsonObject* rsp)
    {
        infoanalyser hdl(*rsp);
        if(hdl.result){
            ui->changebook->setEnabled(true);
            wait.close();
            QMessageBox::about(this,"Success","successfully added");
        }
        else
        {
            ui->changebook->setEnabled(true);
            wait.close();
            QMessageBox::about(this,"Failed",hdl.detail);
        }
    });
    thr->start();
}
