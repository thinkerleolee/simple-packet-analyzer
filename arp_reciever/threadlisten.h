//
// Created by thinkerleo on 17-9-16.
// 抓包线程类
//

#ifndef THREADLISTEN_H
#define THREADLISTEN_H

#include <QThread>
#include <QDebug>
#include <memory>

#include "data_packet_sniffer/FilterDataReceiver.h"
#include "data_packet_sniffer/DataReceiver.h"

class ThreadListen : public QThread
{
    Q_OBJECT
public:
    ThreadListen();

    //设置待监听设备
    void set_dev(int inum)
    {
      dev_num = inum;
    }

    ~ThreadListen(){}

    void stop();
protected:
    //运行抓包
    virtual void run();

private:
    volatile bool stopped;
    int dev_num;  //设备序号
    std::shared_ptr<DataReceiver> re;

};

#endif // THREADLISTEN_H
