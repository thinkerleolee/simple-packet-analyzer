//
// Created by thinkerleo on 17-9-16.
// 这个类负责了ARP数据包分析功能
//


#ifndef PCAP_TASK_ARPANALYZER_H
#define PCAP_TASK_ARPANALYZER_H

#include "PacketAnalyzer.h"

class ArpAnalyzer : public PacketAnalyzer {
    //ARP数据包解析函数
    void get_packet(std::vector <data_pack> &data_pack_buff);
};


#endif //PCAP_TASK_ARPANALYZER_H
