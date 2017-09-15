//
// Created by leo on 17-9-14.
//

#include "DataReceiver.h"


void DataReceiver::find_all_devs() {
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        throw "PCAP_FINDALLDEVS_ERROR";
    }
}

void DataReceiver::get_all_devs(std::vector<std::string> &dev_description) {
    int i = 0;
    pcap_if_t *d;
    std::string temp;
    for(d=alldevs; d; d=d->next)
    {
        temp = d->name;
        temp += ":";
        if (d->description)
        {
            temp += d->description;
            dev_description.push_back(temp);
        }

        else
            temp += "No description available";
        dev_description.push_back(temp);
    }

}

void DataReceiver::release_all_devs() {
    pcap_freealldevs(alldevs);
}



pcap_if_t *DataReceiver::locate_dev(const int inum) {
    int i;
    pcap_if_t *d;
    for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);
    return d;
}
