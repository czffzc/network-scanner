#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hostdetail.h"
#include "port.h"
#include "myping.h"
#include "osDetect.h"
#include "common.h"
#include "pingthread.h"
#include <QThreadPool>
#include "portscan.h"
int param=0;//combox配置参数的index
int sip,eip;//起始ip和结束ip
int sport,eport;//起始端口和结束端口
QString ip0;//端口扫描的ip
boolean if_cancel=false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("network scanner"));
//    hostScan* host;
//    connect(, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));

    ui->progressBar->hide();// 隐藏进度条
    hostdetail host;
    host.showSelfHostDetail(ui->tableWidget_selfhost);
    //注册线程间可传递参数类型
    qRegisterMetaType<QVector<QVector<QString>> >("QVector<QVector<QString>>");

    //主机扫描线程部分===========================================================



    //创建主机扫描子线程对象

    hostThread=new hostscan;
    connect(this,&MainWindow::sendInfo,hostThread,&hostscan::recvInfo);
    //启动子线程
//    connect(ui->pushButtonScan,&QPushButton::clicked,this,[=]()
//    {
//        emit sendInfo(num2ip(sip),num2ip(eip),param);
//        hostThread->start();
//    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
       hostThread->wait();
//       delete hostThread;
    });
    //接收主机扫描子线程发送的数据
    connect(hostThread,&hostscan::sendList,this,[=](QVector<QVector<QString>> list){
        qDebug()<<"连上了呀"<<list.size()<<endl;

        for(int i=0;i<list.size();i++){
            qDebug()<<"内容是："<<endl;
            for(int j=0;j<list[i].size();j++){
                qDebug()<<list[i][j];
            }
            qDebug()<<endl;
        }
    });
    connect(hostThread,SIGNAL(progressBarAdd()),this,SLOT(progressBarIncreament()));
    connect(hostThread,&hostscan::sendItem,this,[=](QVector<QString> it){
        qDebug()<<"连上了item"<<it<<endl;//
        //下面把穿回来的item显示在treewidget上
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);	//创建第一个父节点
        item->setText(0,it[0]);
        item->setText(1,it[1]);
        item->setText(2,it[2]);
        item->setText(3,it[3]);
        ui->textBrowser->append(it[0]);
    });

    connect(hostThread,SIGNAL(hostexit()),this,SLOT(quitHostThread()));

    /*********************************端口扫描部分*****************************************/
    //创建端口扫描子线程对象
//   QThreadPool threadPool = new QThreadPool(this);
//    threadPool->setMaxThreadCount(5);//线程池最多5个线程
//    QThreadPool::globalInstance()->setMaxThreadCount(301);
    //port=new class port[num];

//    portscan *p=new portscan;
    int num=500;


portThread =new portscan[num];
    //启动子线程
//    if(param==PortWithServiceScan){
        connect(ui->pushButtonScan,&QPushButton::clicked,this,[=]()
        {
            if(param==PortWithServiceScan)
            {

//                QThreadPool *pool=new QThreadPool;
//                pool->clear();
//                pool->setMaxThreadCount(301);
                emit sendInfo2(sport,eport,param,ip0);
//                QThreadPool::globalInstance()->clear();
                qDebug()<<"sdfasfa"<<endl;//
                for(int i=0;i<num;i++){
                    qDebug()<<"放入线程池";
//                    QThreadPool::globalInstance()->tryStart(portThread+i);
//                    pool->start(portThread+i);
                    (portThread+i)->start();
                    qDebug()<<"hhh";
        //                portThread[i].start();
                //portThread->start();
                }
            }

        });
        for(int i=0;i<num;i++){
            connect(portThread+i,SIGNAL(progressBarAdd()),this,SLOT(progressBarIncreament()));
                connect(this,&MainWindow::sendInfo2,portThread+i,&portscan::recvInfo2);
                connect(portThread+i,&portscan::sendItem2,this,[=](QVector<QString> it){
                    if(param==PortWithServiceScan){
                        qDebug()<<"连上了item2"<<it<<endl;//
                        //下面把穿回来的item显示在treewidget上
                        QTreeWidgetItem *item2 = new QTreeWidgetItem(ui->treeWidget_2);	//创建第一个父节点
                        item2->setText(0,it[0]);
                        item2->setText(1,it[1]);
                        item2->setText(2,it[2]);
                        qDebug()<<"扫到了端口"<<it[0]<<endl;
                        ui->textBrowser->append(it[0]);
                    }
                });
                //接收端口扫描子线程发送的数据
        }
        connect(portThread,&portscan::sendItem2,this,[=](QVector<QString> it){
            qDebug()<<"连上了item2"<<it<<endl;//
            //下面把穿回来的item显示在treewidget上
            QTreeWidgetItem *item2 = new QTreeWidgetItem(ui->treeWidget_2);	//创建第一个父节点
            item2->setText(0,it[0]);
            item2->setText(1,it[1]);
            item2->setText(2,it[2]);
            qDebug()<<"扫到了端口"<<it[0]<<endl;
            ui->textBrowser->append(it[0]);
        });

}
int useRow = 0;

bool iprange(QString ip1,QString ip2)
{
    int num1 = ip2num(ip1);
    int num2 = ip2num(ip2);
    sip=num1;
    eip=num2;
    int tmp = num2 - num1;
    if(tmp < 0)
        return false;
    else
        return true;
}

int staport,endport;
//按scan按钮 开始扫描
void MainWindow::on_pushButtonScan_clicked()
{

    QDateTime curDateTime=QDateTime::currentDateTime();
    ui->textBrowser->append((curDateTime.toString("yyyy-MM-dd hh:mm:ss")));
    ui->textBrowser->append("开始扫描......");
    if_cancel=false;
    param=ui->comboBox->currentIndex();
    qDebug()<<"配置项为："<<param<<endl;
    sport=ui->startSpinBox->value();
    eport=ui->endSpinBox->value();
    ip0=ui->lineEditTargetchoosip->text();
    qDebug()<<"开始端口为："<<staport<<endl;
    qDebug()<<"结束段口为："<<endport<<endl;
//    QString target=ui->lineEditTarget->text();//获取目标
//    qDebug()<<target<<endl;
    ui->treeWidget->clear();
    ui->treeWidget->expandAll();
    QStringList hraders;
    hraders<<"主机ip"<<"主机名"<<"ttl"<<"操作系统";
    ui->treeWidget->setHeaderLabels(hraders);		//添加树表的表头
            // TreeWidget 自动列宽
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QString s=ui->lineEditTargetBeginIp->text();
    QString e=ui->lineEditTargetEndIp->text();

//页面初始跳转

    if(param==PortWithServiceScan){//端口和服务扫描
        ui->tabWidget->setCurrentIndex(2);
        //判断输入是否正确
        if(sport<1||sport>65535||eport<1||eport>65535){
            ui->textBrowser->append(QString("端口范围错误！正确范围是1~65535"));
            return;
        }
        else if(sport>eport){
            ui->textBrowser->append(QString("起始端口不能大于结束端口"));
            return;
        }
    }
    else{//主机扫描
        //判断输入是否正确
        if(!checkip(s))
        {
            ui->textBrowser->append(QString("起始ip 地址错误"));
            return ;
        }
        if(!checkip(e))
        {
            ui->textBrowser->append(QString("结束ip 地址错误"));
            return ;
        }
        if(!iprange(s,e)){
            ui->textBrowser->append(QString("结束ip不能小于起始ip!"));
            return;
        }
        ui->tabWidget->setCurrentIndex(0);
        emit sendInfo(num2ip(sip),num2ip(eip),param);
        hostThread->start();//启动主机扫描子线程
    }

//    iprange
    sip=ip2num(s);
    eip=ip2num(e);
    //之后改用多线程写了
    if(param==PortWithServiceScan){//开始端口和服务扫描
        ui->treeWidget_2->clear();
        ui->progressBar->show();
        ui->progressBar->setValue(0);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(eport-sport+1);
    }
    else{//主机扫描、操作系统扫描
        ui->progressBar->show();
        ui->progressBar->setValue(0);
        ui->progressBar->setMinimum(0);
//        ui->progressBar->setMaximum(ui->endSpinBox->value()-ui->startSpinBox->value()+1);
        ui->progressBar->setMaximum(eip-sip+1);
    }
}

void MainWindow::lookUp(const QHostInfo &host)
{
    if(host.error() != QHostInfo::NoError){
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }
    if(host.addresses()[0].toString() == host.hostName())
        return;
    qDebug()<<QString("look up")<<endl;
    if(!QString(host.addresses()[0].toString()).isEmpty()){
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget,QStringList(QString(host.addresses()[0].toString())));	//创建第一个父节点
//        QTreeWidgetItem *item1=new QTreeWidgetItem(ui->treeWidget);
//        item1->setText(0,QString("111"));
//        item->setCheckState(0, Qt::CheckState::Unchecked);
        item->setText(0,host.addresses()[0].toString());
        item->setText(1,host.hostName());
        item->setCheckState(0,item->checkState(0));

        if(param==hostWithOsScan){//全局扫描
            unsigned char ttl;
            ping(qstring2charPointer(host.addresses()[0].toString()),ttl);
            qDebug()<<"主页ttl"<<ttl<<endl;
            item->setText(2,QString::number(ttl));
            qDebug()<<ttlDetectOs(ttl)<<endl;
            item->setText(3,ttlDetectOs(ttl));
            Sleep(500);
        }

//        ip=host.addresses()[0].toString();
//        qDebug()<<ip<<endl;
//        //ui->progressBar->setRange(0,0);
//         //ip=desip;
//         //staport=ui->spinBox->value();
//         //endport=ui->spinBox_2->value();
//         staport=1;//先给一个确定的值
//         endport=65535;//先给一个确定的值
//         nowport=staport;
//         result=ui->textEdit;
//         result->clear();
//         //qDebug()<<staport<<endport<<nowport;
//         //int num=ui->spinBox_3->value();
//         int num=300;//先给一个确定的值
//         port=new class port[num];
//         //ui->progressBar->setRange(staport,endport);

//        ui->pushButton_2->setVisible(true);
//         for(int i=0;i<num;i++)
//         {
//             port[i].start();
//             threadisrunnig=true;
//             port[i].exit(0);
//             //delete port[i];
//             //connect(port+i,SIGNAL(sentnowport(int)),this,SLOT(setBar(int)));
//         }
    //这部分是端口扫描
    }

    useRow++;
}


MainWindow::~MainWindow()
{
    delete hostThread;
    delete [] portThread;
    delete ui;
}
//清空程序的输出日志
void MainWindow::on_pushButton_clearLog_clicked()
{
    ui->textBrowser->clear();
}

//取消按钮
void MainWindow::on_pushButton_2_clicked()
{
    if_cancel=true;//
    ui->textBrowser->append("程序已终止\n");
}

//程序退出
void MainWindow::on_actionEixt_triggered()
{
    this->close();
}

void MainWindow::on_actionCompile_triggered()
{
    ui->pushButtonScan->click();
}

void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("About Network Scanner"),
                tr("<p> <b>网络扫描器</b>描述  <br>" \
                   "主机扫描<br>"\
                   "操作系统扫描<br>"\
                   "端口扫描<br>"\
                   "服务扫描<br>"\
                   "by 1851463 封作铖 and 1951575 徐天翊.</p>"));
}

void MainWindow::progressBarIncreament()
{
    qDebug()<<"进度条推进"<<endl;
    ui->progressBar->setValue(ui->progressBar->value()+1);
    if(ui->progressBar->value()==ui->progressBar->maximum()){
        ui->progressBar->hide();
    }
}

void MainWindow::quitHostThread()
{
    hostThread->wait();  //必须等待线程结束
    hostThread->quit();
}
