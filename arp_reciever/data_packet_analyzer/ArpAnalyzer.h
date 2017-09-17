//
// Created by root on 17-9-16.
//

#ifndef PCAP_TASK_ARPANALYZER_H
#define PCAP_TASK_ARPANALYZER_H

#include "PacketAnalyzer.h"

class ArpAnalyzer: public PacketAnalyzer{
    void get_packet(std::vector<data_pack> &data_pack_buff);
};


#endif //PCAP_TASK_ARPANALYZER_H
