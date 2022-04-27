#ifndef HOSTSCAN_H
#define HOSTSCAN_H
#include <QHostInfo>
#include <QThread>
#include <QVector>
// 主机扫描线程类
class hostscan : public QThread
{
    Q_OBJECT
public:
    explicit hostscan(QObject *parent = nullptr);

    void recvInfo(QString sip,QString eip,int p);

    int rowcount=0;
    QVector<QVector<QString>> list;

protected:
    void run() override;

signals:
    void sendList(QVector<QVector<QString>> list);
    void sendItem(QVector<QString> item);
    void progressBarAdd();//进度条增加进度信号
    void hostexit();//主机扫描结束信号

private:
    QString s;//起始ip
    QString e;//结束ip
    int param;//参数选项

private slots:
    void lookUp(const QHostInfo &host);

};

#endif // HOSTSCAN_H
