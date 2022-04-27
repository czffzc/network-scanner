#include "hostdetail.h"

/*
qsysinfo 文档详见 https://doc.qt.io/qt-5/qsysinfo-obsolete.html
*/
hostdetail::hostdetail()
{

}

void hostdetail::showSelfHostDetail(QTableWidget *tablewidget)
{
    int countRow=0;
    //设置列数
    tablewidget->setColumnCount(2);

    //设置行数
    tablewidget->setRowCount(10);

    QStringList headerText;
    headerText<<"类别"<<"详细信息";
    tablewidget->setHorizontalHeaderLabels(headerText);
    tablewidget->verticalHeader()->setVisible(false);//不显示默认行号
//    tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch)
//    tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    tablewidget>header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //    qDebug() << "建构buildAbi : " << QSysInfo::buildAbi();
//        qDebug() << "currentCpuArchitecture : " << QSysInfo::currentCpuArchitecture();
//        qDebug() << "kernelType : " << QSysInfo::kernelType();
//        qDebug() << "kernelVersion : " << QSysInfo::kernelVersion();
//        qDebug() << "prettyProductName : " << QSysInfo::prettyProductName();
//        qDebug() << "productType : " << QSysInfo::productType();
//        qDebug() << "kernelType : " << QSysInfo::kernelType();
//        qDebug() << "productVersion : " << QSysInfo::productVersion();
//        qDebug()<<"windows版本："<<QSysInfo::WindowsVersion;


        tablewidget->setItem(0,0,new QTableWidgetItem("架构信息"));
        tablewidget->setItem(0,1,new QTableWidgetItem(QSysInfo::buildAbi()));

        tablewidget->setItem(1,0,new QTableWidgetItem("内核类型"));
        tablewidget->setItem(1,1,new QTableWidgetItem(QSysInfo::kernelType()));

        tablewidget->setItem(2,0,new QTableWidgetItem("内核版本"));
        tablewidget->setItem(2,1,new QTableWidgetItem(QSysInfo::kernelVersion()));

        tablewidget->setItem(3,0,new QTableWidgetItem("机器主机名"));
        tablewidget->setItem(3,1,new QTableWidgetItem(QSysInfo::machineHostName()));

        tablewidget->setItem(4,0,new QTableWidgetItem("操作系统类型"));
        tablewidget->setItem(4,1,new QTableWidgetItem(QSysInfo::productType()));

        tablewidget->setItem(5,0,new QTableWidgetItem("操作系统名称"));
        tablewidget->setItem(5,1,new QTableWidgetItem(QSysInfo::prettyProductName()));

        tablewidget->setItem(6,0,new QTableWidgetItem("操作系统版本"));
        tablewidget->setItem(6,1,new QTableWidgetItem(QSysInfo::productVersion()));


//        QTableWidgetItem *structName = new QTableWidgetItem;//架构信息
//        structName->setText(QString("架构"));
//        tablewidget->setItem(countRow,0,structName);
//        QTableWidgetItem *structContent = new QTableWidgetItem;
//        structContent->setText(QSysInfo::buildAbi());
//        tablewidget->setItem(countRow,1,structContent);
//        countRow++;

//        QTableWidgetItem *cpuStructure = new QTableWidgetItem;//架构信息
//        cpuStructure->setText(QString("CPU架构"));
//        tablewidget->setItem(countRow,0,cpuStructure);
//        QTableWidgetItem *cpuStructureContent = new QTableWidgetItem;
//        cpuStructureContent->setText(QSysInfo::buildCpuArchitecture());
//        tablewidget->setItem(countRow,1,cpuStructureContent);
//        countRow++;

//        QTableWidgetItem *kernelType = new QTableWidgetItem;
//        cpuStructure->setText(QString("内核类型"));
//        tablewidget->setItem(countRow,0,kernelType);
//        QTableWidgetItem *kernelTypeContent = new QTableWidgetItem;
//        cpuStructureContent->setText(QSysInfo::kernelType());
//        tablewidget->setItem(countRow,1,kernelTypeContent);
//        countRow++;

//        QTableWidgetItem *kernelVersion = new QTableWidgetItem;
//        cpuStructure->setText(QString("内核版本"));
//        tablewidget->setItem(countRow,0,kernelVersion);
//        QTableWidgetItem *kernelVersionContent = new QTableWidgetItem;
//        cpuStructureContent->setText(QSysInfo::kernelVersion());
//        tablewidget->setItem(countRow,1,kernelVersionContent);
//        countRow++;


        tablewidget->resizeColumnsToContents();//自动调整表格列宽



        //    QTableWidgetItem *ipItem = new QTableWidgetItem;
    //    ipItem->setText(host.addresses()[0].toString());
        //    ui->tableWidget->setItem(useRow, Col1, ipItem);

}
