//
// Created by leo on 17-9-15.
//

#ifndef PCAP_TASK_FILTERDATARECEIVER_H
#define PCAP_TASK_FILTERDATARECEIVER_H

#include "DataReceiver.h"

const char FILENAME[]= "temp.dat";

class FilterDataReceiver:public DataReceiver {
private:
    pcap_if_t *selected_dev{};
    pcap_t *adhandle;
    pcap_dumper_t *dumpfile;
public:
    //
    void listen(int inum){
        read_adapter(inum);
        set_file();
        start_listen();
    }

    //打开适配器
    void read_adapter(const int inum);

    //配置堆文件
    void set_file();

    //开始抓包
    void start_listen();

    //定位设备
    pcap_if_t* locate_dev(const int inum);

    /* 回调函数，当收到每一个数据包时会被libpcap所调用 */

};

/* 回调函数，用来处理数据包 */
static void packet_handler(u_char *dumpfile, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    /* 保存数据包到堆文件 */
    pcap_dump(dumpfile, header, pkt_data);
}

#endif //PCAP_TASK_FILTERDATARECEIVER_H
