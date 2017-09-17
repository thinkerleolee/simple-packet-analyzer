//
// Created by root on 17-9-16.
//

#ifndef PCAP_TASK_UDPANALYZER_H
#define PCAP_TASK_UDPANALYZER_H

#include "PacketAnalyzer.h"

class UdpAnalyzer : public PacketAnalyzer {
    void get_packet(std::vector<data_pack> &data_pack_buff);
};


#endif //PCAP_TASK_UDPANALYZER_H
