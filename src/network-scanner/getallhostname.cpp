#include "getallhostname.h"

GetAllHostName::GetAllHostName()
{

}

GetAllHostName::GetAllHostName(QVector<QString> allIp)
{
    // 注册自定义结构参数
    qRegisterMetaType< QPair<QString,QString> >("QPair<QString,QString>");

    allHostIp = allIp;
}

// 通过局域网内ip地址获取对应的主机名(通过winsock2)
QString GetAllHostName::getHostnameByIpStr(QString ipStr)
{
    struct hostent *host;
    struct in_addr addr;

    QByteArray bytearray = ipStr.toUtf8();
    char * ip = bytearray.data();

    addr.S_un.S_addr = inet_addr(ip);

    host = gethostbyaddr((char *)&addr,sizeof(addr),AF_INET);
    if(host != NULL){
        //printf("%s\n",host->h_name);
        return QString(host->h_name);
    }

    return "------";
}

void GetAllHostName::run()
{
    struct hostent *host;
    struct in_addr addr;

    QByteArray bytearray;
    char * ip;
    QString hostname;

    QVector<QString>::const_iterator iter = allHostIp.begin();
    while(iter != allHostIp.end()){
        // 采用局部变量方式
        bytearray = (*iter).toUtf8();
        ip = bytearray.data();
        addr.S_un.S_addr = inet_addr(ip);
        host = gethostbyaddr((char *)&addr,sizeof(addr),AF_INET);
        if(host != NULL){
            //printf("%s\n",host->h_name);
            hostname = QString(host->h_name);
        }
        else hostname = "------";

        // 采用调用函数方式
        //QString hostname = getHostnameByIpStr(*iter);
        QPair<QString,QString> info;
        info.first = *iter;
        info.second = hostname;
        emit getHostnameByIpStrUpdateSig(info);
        ++iter;
    }
    this->quit();
}
