//
// Created by root on 17-9-16.
//

#ifndef PCAP_TASK_ANALYZERMANNGER_H
#define PCAP_TASK_ANALYZERMANNGER_H

#include <zconf.h>
#include <vector>
#include "PacketAnalyzer.h"
#include "ArpAnalyzer.h"
#include "UdpAnalyzer.h"

class AnalyzerMannger {
private:
    std::string protocol;
    PacketAnalyzer* analyzer;
public:
    void setPortocol(std::string pro)
    {
        protocol = pro;
        if(this->protocol == "arp")
        {
            analyzer = new ArpAnalyzer;
            try
            {
              analyzer->init_temp_file("arp");
            }
            catch(char* e)
            {
              throw(e);
            }
        } else if(this->protocol == "udp")
        {
            analyzer = new UdpAnalyzer;
            try
            {
              analyzer->init_temp_file("udp");
            }
            catch(char* e)
            {
              throw(e);
            }
        }
    }
    void get_packet(std::vector<data_pack> &data_pack_buff)
    {
        analyzer->get_packet(data_pack_buff);
    }
    ~AnalyzerMannger(){
        delete(analyzer);
    }

};


#endif //PCAP_TASK_ANALYZERMANNGER_H
