#ifndef OSDETECT_H
#define OSDETECT_H
//操作系统检测
//通过 ttl判断对方的操作系统
#include<QString>

inline QString ttlDetectOs(unsigned char t){
    QString os="windows10";
//    return os;

    int ttl=int(t);
//    if(ttl==128)
//        os="12888888";
//    else
//        os="00000000";
    if(ttl<=0){
        os="无法判断";
        return os;
    }
    if(ttl<=32){
        os="Windows 95/98/Me";
    }
    else{
        if(ttl<=64){
            os="Linux";
        }
        else{
            if(ttl<=128){
                os="windows 10/Server 2008/7/Vista/2003/XP/2000/NT";
//                os="Windows NT/2000/XP/2003/Vista/7/Server 2008/10";
            }
            else{
                os="Unix";
            }
        }
    }
    return os;
}

#endif // OSDETECT_H
