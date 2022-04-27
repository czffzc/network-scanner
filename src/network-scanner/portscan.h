#ifndef PORTSCAN_H
#define PORTSCAN_H
#include<QMutex>
#include<QThread>
#include<QProgressBar>
#include <QGraphicsItem>
#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>
#include <QTcpSocket>
#include <QTextEdit>
#include <QVector>
#include <QHostInfo>
#include <QThread>
#include <QObject>
#include <QRunnable>
#include <QMutex>

class portscan : public QThread
{
    Q_OBJECT
public:
    explicit portscan(QObject *parent = nullptr);
    void recvInfo2(int sport,int eport,int p,QString ip);
    QVector<QVector<QString>> list2;
    QString showservice(QString portnum);//显示端口对应的服务
    QMutex mutex;


    void run() override;
signals:
    void sendItem2(QVector<QString> item);
    void progressBarAdd();//进度条增加进度信号

private:
    int s;//起始port
    int e;//结束port
    int param;//参数选项
    QString ip;//对应ip
private slots:
    void lookUp(int port,QString ip);
};
#endif // PORTSCAN_H
