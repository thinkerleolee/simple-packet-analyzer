//
// Created by thinkerleo on 17-9-16.
// 这个类负责提供数据包捕获接收的接口
//

#ifndef PCAP_TASK_DATARECEIVER_H
#define PCAP_TASK_DATARECEIVER_H

#include <iostream>
#include <pcap.h>
#include <ctime>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <map>
#include <vector>

class DataReceiver {
protected:
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE]; //错误缓冲池
    pcap_dumper_t *dumpfile; //堆文件指针
public:
    //查找所有网络设备
    void find_all_devs();

    //得到所有网络设备
    void get_all_devs(std::vector <std::string> &dev_description);

    //开始监听
    virtual void listen(int inum) {};
};


#endif //PCAP_TASK_DATARECEIVER_H
