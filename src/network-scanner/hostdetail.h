#ifndef HOSTDETAIL_H
#define HOSTDETAIL_H

#include <QTableWidget>
#include <QSysInfo>
#include <QDebug>
#include <QHeaderView>
class hostdetail
{
public:
    hostdetail();
    void showSelfHostDetail(QTableWidget*);
};

#endif // HOSTDETAIL_H
