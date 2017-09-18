//
// Created by thinkerleo on 17-9-16.
// 这个类负责了数据包分析的配置和调用功能
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
    PacketAnalyzer *analyzer;
public:
    //配置待分析协议的协议类型，如”arp“， ”udp“等
    void setPortocol(std::string pro) {
        protocol = pro;
        if (this->protocol == "arp") {
            analyzer = new ArpAnalyzer;
            try {
                analyzer->init_temp_file("arp");
            }
            catch (char *e) {
                throw (e);
            }
        } else if (this->protocol == "udp") {
            analyzer = new UdpAnalyzer;
            try {
                analyzer->init_temp_file("udp");
            }
            catch (char *e) {
                throw (e);
            }
        }
    }

    //过滤并分析已选协议的数据包
    void get_packet(std::vector <data_pack> &data_pack_buff) {
        analyzer->get_packet(data_pack_buff);
    }

    //析构函数
    ~AnalyzerMannger() {
        delete analyzer;
    }

};


#endif //PCAP_TASK_ANALYZERMANNGER_H
