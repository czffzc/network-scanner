#ifndef PORT_H
#define PORT_H

#include<QMutex>
#include<QThread>
#include<QProgressBar>
#include <QGraphicsItem>
#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>
#include <QTcpSocket>
#include <QTextEdit>
class port:public QThread
{
public:
    port();
    void run();//不多说，自己Google
    void stop();//实现线程安全停止，用Terminate是不安全的
    void quit();//
    void portcanner(QString ip,int startport,int endport);
private:
     volatile bool stopped;
};

#endif // PORT_H
