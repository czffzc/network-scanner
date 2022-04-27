#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <qdebug.h>
#include <QHostInfo>
#include <QSysInfo>
#include <port.h>
#include <QProcess>
#include "hostscan.h"
#include "portscan.h"
#include <qdatetime.h>
#include <qmessagebox.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonScan_clicked();
    void lookUp(const QHostInfo &host);

    void on_pushButton_clearLog_clicked();

    void on_pushButton_2_clicked();


    void on_actionEixt_triggered();

    void on_actionCompile_triggered();

    void on_actionabout_triggered();

    void progressBarIncreament();//进度条推进

    void quitHostThread();


signals:
    void sendInfo(QString sip,QString eip,int p);
    void sendInfo2(int sport, int eport,int p,QString ip0);


private:
    hostscan* hostThread;
    portscan* portThread;
    bool threadisrunnig;
    port *port;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
