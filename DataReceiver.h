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
#include <map>
#include <vector>


class DataReceiver {
protected:
    const std::string FILENAME = "temp.dat";
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_dumper_t *dumpfile;


public:
    void find_all_devs();

    void get_all_devs(std::vector<std::string> &dev_description);

    void release_all_devs();

    pcap_if_t* locate_dev(const int inum);

    //virtual void listen_filter(const char *);
};


#endif //PCAP_TASK_DATARECEIVER_H
