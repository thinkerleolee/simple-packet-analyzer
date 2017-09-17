#ifndef THREADLISTEN_H
#define THREADLISTEN_H

#include <QThread>
#include <QDebug>
#include "data_packet_sniffer/FilterDataReceiver.h"
#include "data_packet_sniffer/DataReceiver.h"

class ThreadListen : public QThread
{
    Q_OBJECT
public:
    ThreadListen();
    void set_dev(int inum)
    {
      dev_num = inum;
    }

    void stop();
protected:
    virtual void run();

private:
    volatile bool stopped;
    int dev_num;
    DataReceiver *re;

};

#endif // THREADLISTEN_H
