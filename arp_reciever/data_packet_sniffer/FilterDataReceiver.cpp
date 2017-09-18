//
// Created by thinkerleo on 17-9-16.
//


#include "FilterDataReceiver.h"

void FilterDataReceiver::read_adapter(const int inum) {
    int res;
    struct pcap_pkthdr *header;
    time_t local_tv_sec;
    const u_char *pkt_data;
    selected_dev = locate_dev(inum);
    /* 打开设备 */
    if ((adhandle = pcap_open_live(selected_dev->name,          // 设备名
                                   65536,            // 要捕捉的数据包的部分
            // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
                                   true,    // 混杂模式
                                   1000,             // 读取超时时间
                                   errbuf            // 错误缓冲池
    )) == NULL) {
        fprintf(stderr, "OPEN_DEV_ERROR: %s\n", errbuf);
        throw ("OPEN_DEV_ERROR");
    }
}

void FilterDataReceiver::set_file() {
    dumpfile = pcap_dump_open(adhandle, FILENAME);
    if (dumpfile == NULL) {
        fprintf(stderr, "\nError opening output file\n");
        throw ("OPEN_FILE_ERROR");
    }
}

void FilterDataReceiver::start_listen() {
    printf("\nlistening on %s...\n", selected_dev->name);
    pcap_freealldevs(alldevs);
    /* 开始捕捉 */
    pcap_loop(adhandle, 0, packet_handler, (unsigned char *) dumpfile);
}

pcap_if_t *FilterDataReceiver::locate_dev(const int inum) {
    int i;
    pcap_if_t *d;
    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);
    return d;
}
