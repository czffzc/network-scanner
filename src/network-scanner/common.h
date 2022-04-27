// commom.h 存放公共函数
#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QStringList>

#define hostWithOsScan 0  //主机+操作系统扫描
#define hostOnlyScan 1 //仅主机扫描
#define PortWithServiceScan 2  // 端口+服务扫描

inline int ip2num(QString ip)
{
    bool ok;
    int lp[4];
    QStringList iplist=ip.split('.');
    for (int i=0;i<iplist.length();i++)
        lp[i]=iplist[i].toInt(&ok,10);
    return lp[0] << 24 | lp[1] << 16 | lp[2] << 8 | lp[3];
}

inline QString num2ip(int num)//:# int num to ip
{
    int ip[4];
    ip[3] = (num & 0xff);
    ip[2] = (num & 0xff00) >> 8;
    ip[1] = (num & 0xff0000) >> 16;
    ip[0] = (num & 0xff000000) >> 24;
    QString rip=QString("%1").arg(ip[0])+QString(".")+QString("%1").arg(ip[1])+QString(".")+QString("%1").arg(ip[2])+QString(".")+QString("%1").arg(ip[3]);
    return rip;
}

//检查ipv4地址是否合法
inline bool checkip(QString ip)
{
    QRegExp rx2("\\d+\\.\\d+\\.\\d+\\.\\d+");
     if( !rx2.exactMatch(ip) )
     {
           return false;
     }
     //qDebug()<<"check true";
     return true;
}

// QString转char*
inline char* qstring2charPointer(QString tmp)
{
    QByteArray text = tmp.toLocal8Bit();
    char * pCh = new char[text.size()+1];
    strcpy(pCh, text.data());
    return pCh;
}
#endif // COMMON_H
