#ifndef GETALLHOSTNAME_H
#define GETALLHOSTNAME_H

#include <QThread>
#include <winsock2.h>
#include <QVector>
#include <QPair>

class GetAllHostName : public QThread
{
    Q_OBJECT

public:
    GetAllHostName();
    GetAllHostName(QVector<QString> allIp);
    // 通过局域网内ip地址获取对应的主机名(通过winsock2)
    QString getHostnameByIpStr(QString);
private:
    QVector<QString> allHostIp;
private:
    void run();
signals:
    void getHostnameByIpStrUpdateSig(QPair<QString,QString>);
};

#endif // GETALLHOSTNAME_H
