#include "portscan.h"
#include "common.h"
#include <qtreewidget.h>
#include <QFile>
#include <QThread>
int nowport;
portscan::portscan(QObject *parent) : QThread(parent)
{
//    setAutoDelete(true);
}
//主线程传递给端口扫描线程的参数
void portscan::recvInfo2(int sport, int eport,int p,QString ip0)
{
    nowport=sport;
    s=sport;
    e=eport;
    param=p;
    ip=ip0;
}

void portscan::run()
{
    if(param!=PortWithServiceScan)//如果是端口和服务扫描，则不用运行该线程
        return;


//    if(nowport==e){
//        mutex.unlock();
//        return;
//    }

    for(;nowport<=e;){
            mutex.lock();
            int temport=nowport++;
            mutex.unlock();
            lookUp(temport,ip);
            emit progressBarAdd();
            qDebug() << "目前端口"<<temport<< " 结束端口："<<e;
    }
}

void portscan::lookUp(int port,QString ip)
{
    //qDebug() << "执行到了1";
    QVector<QString> item(3);//端口号 状态 服务
    QTcpSocket socket(0);
    socket.abort();
    socket.connectToHost(ip,port);
    //qDebug() << "执行到了2";
    if(socket.waitForConnected(1000))
     {
        qDebug() << "执行到了3";
        QString service="";
        service=showservice(QString::number(port));

        item[0]=QString::number(port);
        item[1]="open";
        item[2]=service;

        emit sendItem2(item);
        list2.append(item);
    }

    else
        ;


}
QString portscan::showservice(QString portnum)
{
    //qDebug() << "进入";
    QString result="";
    QString a="";
    QString b="";
    int i=0;
    //QFile file("C://network scanner//network-scanner//nmap-services.txt");
    QFile file(":/new/prefix1/nmap-services.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
            //qDebug() << "文件打开成功";
             while (!file.atEnd())
             {
                 //qDebug() << "开始";
                 QByteArray line = file.readLine();
                 QString str(line);
                 //qDebug() << str;
                 for(i=0;str[i]>='a'&&str[i]<='z';i++)
                 {
                    a=a+str[i];
                 }
                 while(!((str[i]>='0')&&(str[i]<='9')))
                 {
                       i++;
                 }
                 for(;str[i]>='0'&&str[i]<='9';i++)
                 {
                    b=b+str[i];
                 }
                 if(portnum==b)
                 {
                     result=a;
                     a="";
                     b="";
                     break;
                 }
                 a="";
                 b="";

             }
             file.close();

         }
    //qDebug() << result;
    return result;
}
