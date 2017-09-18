//
// Created by thinkerleo on 17-9-16.
// 主窗体类
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data_packet_analyzer/AnalyzerMannger.h"
#include "data_packet_sniffer/FilterDataReceiver.h"
#include "data_packet_sniffer/DataReceiver.h"
#include "threadlisten.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    //激活监听线程
    void startThreadListen();

    //停止监听线程
    void stopThreadListen();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_comboBox_choose_protocol_currentIndexChanged(const QString &arg1);


private:

    //将捕获的包进行分析
    void anan_packet();

    //清空表格内容
    void newModel();

    //SHOW TABLE
    void show_table();

    //检查是否以root下运行
    bool check_if_root();

    std::vector<std::string> dev_description; //保存设备列表vector
    ThreadListen threadListen;  //监听线程
    Ui::MainWindow *ui; //UI
    DataReceiver *re; //抓包器
    AnalyzerMannger analyzer; //数据分析器
    std::vector<data_pack> data_buff_arp; //数据包缓存
    std::vector<data_pack> data_buff_udp; //数据包缓存
};

#endif // MAINWINDOW_H
