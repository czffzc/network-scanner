#include "hostscan.h"
#include "common.h"
#include <qtreewidget.h>

#include "myping.h"
#include "osDetect.h"
hostscan::hostscan(QObject *parent) : QThread(parent)
{

}

//主线程传递给主机扫描线程的参数
void hostscan::recvInfo(QString sip, QString eip,int p)
{
    s=sip;
    e=eip;
    param=p;

}

void hostscan::run()
{
    if(param==PortWithServiceScan)//如果是端口和服务扫描，则不用运行该线程
        return;
    qDebug()<<"当前主机扫描线程地址："<<QThread::currentThread();
    qDebug()<<"主机扫描线程 开始ip："<<s<<endl;
    qDebug()<<"主机扫描线程 结束ip："<<e<<endl;
    for(int i=ip2num(s);i<=ip2num(e);i++){
        //qDebug()<<num2ip(i)<<endl;

        QHostInfo::lookupHost(num2ip(i), this, SLOT(lookUp(QHostInfo)));
//         QCoreApplication::processEvents();
    }
    emit hostexit();
    qDebug()<<"主机扫描线程list大小："<<list.size()<<endl;
    emit sendList(list);
}
void hostscan::lookUp(const QHostInfo &host)
{

    qDebug()<<"主机扫描进度条++"<<endl;
    emit progressBarAdd();

    QVector<QString> item(4);//ip 主机名 ttl 操作系统
    if(host.error() != QHostInfo::NoError){
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    if(host.addresses()[0].toString() == host.hostName())
        return;
    qDebug()<<QString("多线程look up")<<endl;
    if(!QString(host.addresses()[0].toString()).isEmpty()){
//        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget,QStringList(QString(host.addresses()[0].toString())));	//创建第一个父节点

        //        QTreeWidgetItem *item1=new QTreeWidgetItem(ui->treeWidget);
//        item1->setText(0,QString("111"));
//        item->setCheckState(0, Qt::CheckState::Unchecked);
//        item->setText(0,host.addresses()[0].toString());
//        item->setText(1,host.hostName());
//        item->setCheckState(0,item->checkState(0));
        item[0]=host.addresses()[0].toString();
        qDebug()<<"线程"<<host.addresses()[0].toString()<<endl;;
        item[1]=host.hostName();

        if(param==hostWithOsScan){//主机+操作系统扫描
            unsigned char ttl;
            ping(qstring2charPointer(host.addresses()[0].toString()),ttl);
            qDebug()<<"主页ttl"<<ttl<<endl;
//            item->setText(5,QString::number(ttl));
            item[2]=QString::number(ttl);
            qDebug()<<ttlDetectOs(ttl)<<endl;
//            item->setText(6,ttlDetectOs(ttl));
            item[3]=ttlDetectOs(ttl);
//            Sleep(500);
        }
        qDebug()<<"线程item："<<item<<endl;
        emit sendItem(item);
        list.append(item);
        qDebug()<<"线程item："<<list[0][0]<<endl;
        qDebug()<<"list大小"<<list.size()<<endl;
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
    //    QTableWidgetItem *ipItem = new QTableWidgetItem;
//    ipItem->setText(host.addresses()[0].toString());
//    QTableWidgetItem *hostItem = new QTableWidgetItem;
//    hostItem->setText(host.hostName());

//    if(ipItem->text() != hostItem->text()){

//        ipItem->setTextColor(QColor(Qt::red));
//        hostItem->setTextColor(QColor(Qt::red));
//    }
//    ui->tableWidget->setItem(useRow, Col1, ipItem);
//    ui->tableWidget->setItem(useRow, Col2, hostItem);
    rowcount++;
}
