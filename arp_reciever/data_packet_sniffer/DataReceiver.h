//
// Created by leo on 17-9-14.
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
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_dumper_t *dumpfile;
public:
    void find_all_devs();

    void get_all_devs(std::vector<std::string> &dev_description);

    virtual void listen(int inum){};
};


#endif //PCAP_TASK_DATARECEIVER_H
