//
// Created by leo on 17-9-15.
//

#include "FilterDataReceiver.h"

void FilterDataReceiver::read_adapter(const int inum) {
    int i = 0;
    int res;
    struct pcap_pkthdr *header;
    time_t local_tv_sec;
    const u_char *pkt_data;
    selected_dev = locate_dev(inum);
    /* 打开设备 */
    if ( (adhandle = pcap_open_live(selected_dev->name,          // 设备名
                                   65536,            // 要捕捉的数据包的部分
            // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
                                   true,    // 混杂模式
                                   1000,             // 读取超时时间
                                   errbuf            // 错误缓冲池
    ) ) == NULL)
    {
        fprintf(stderr,"OPEN_DEV_ERROR: %s\n", errbuf);
        throw("OPEN_DEV_ERROR");
    }

    /* 释放设备列表 */
    pcap_freealldevs(alldevs);
}
void FilterDataReceiver::set_compile() {
    char packet_filter[] = "arp";
    //编译过滤器
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
    {
        fprintf(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        throw("COMPILE_ERROR");
    }

    //设置过滤器
    if (pcap_setfilter(adhandle, &fcode)<0)
    {
        fprintf(stderr,"\nError setting the filter.\n");
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        throw("SET_FILTER_ERROR");
    }
}

void FilterDataReceiver::set_filter() {
    if (pcap_setfilter(adhandle, &fcode)<0)
    {
        fprintf(stderr,"\nError setting the filter.\n");
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        throw("SET_FILTER_ERROR");
    }

}

void FilterDataReceiver::check_datalink() {
    /* 检查数据链路层，为了简单，我们只考虑以太网 */
    if(pcap_datalink(adhandle) != DLT_EN10MB)
    {
        fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        throw("NETWORK_MODE_ERROR");
    }
}

void FilterDataReceiver::start_listen() {
    printf("\nlistening on %s...\n", selected_dev->description);
    /* 开始捕捉 */
    pcap_loop(adhandle, 0, packet_handler_arp, NULL);
}


/* 回调函数，当收到每一个数据包时会被libpcap所调用 */
void FilterDataReceiver::packet_handler_ip(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    struct tm *ltime;
    char timestr[16];
    ip_header *ih;
    udp_header *uh;
    u_int ip_len;
    u_short sport,dport;
    time_t local_tv_sec;

    /* 将时间戳转换成可识别的格式 */
    local_tv_sec = header->ts.tv_sec;
    ltime=localtime(&local_tv_sec);
    strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);

    /* 打印数据包的时间戳和长度 */
    printf("%s.%.6d len:%d ", timestr, header->ts.tv_usec, header->len);

    /* 获得IP数据包头部的位置 */
    ih = (ip_header *) (pkt_data +
                        14); //以太网头部长度

    /* 获得UDP首部的位置 */
    ip_len = (ih->ver_ihl & 0xf) * 4;
    uh = (udp_header *) ((u_char*)ih + ip_len);

    /* 将网络字节序列转换成主机字节序列 */
    sport = ntohs( uh->sport );
    dport = ntohs( uh->dport );

    /* 打印IP地址和UDP端口 */
    printf("%d.%d.%d.%d.%d -> %d.%d.%d.%d.%d\n",
           ih->saddr.byte1,
           ih->saddr.byte2,
           ih->saddr.byte3,
           ih->saddr.byte4,
           sport,
           ih->daddr.byte1,
           ih->daddr.byte2,
           ih->daddr.byte3,
           ih->daddr.byte4,
           dport);
}

void FilterDataReceiver::packet_handler_arp(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    struct tm *ltime;
    char timestr[16];
    ether_header *eh;
    arp_packet *ap;
    time_t local_tv_sec;

    /* 将时间戳转换成可识别的格式 */
    local_tv_sec = header->ts.tv_sec;
    ltime=localtime(&local_tv_sec);
    strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);

    /* 打印数据包的时间戳和长度 */
    printf("%s.%.6d len:%d ", timestr, header->ts.tv_usec, header->len);


    /* 获得ARP首部的位置 */
    eh = (ether_header*)pkt_data;
    ap = (arp_packet *) ((u_char*)eh + 14);

    /* 打印IP地址和MAC地址 */
    printf("\nTargetIP: %d.%d.%d.%d",
           ap->arp_tpa.byte1,
           ap->arp_tpa.byte2,
           ap->arp_tpa.byte3,
           ap->arp_tpa.byte4);
    printf(" SourceIP: %d.%d.%d.%d\n",
           ap->arp_spa.byte1,
           ap->arp_spa.byte2,
           ap->arp_spa.byte3,
           ap->arp_spa.byte4);
    printf("TargetMAC: %x:%x:%x:%x:%x:%x",
           ap->arp_tha.byte1,
           ap->arp_tha.byte2,
           ap->arp_tha.byte3,
           ap->arp_tha.byte4,
           ap->arp_tha.byte5,
           ap->arp_tha.byte6);
    printf(" SourceMAC: %x:%x:%x:%x:%x:%x\n\n",
           ap->arp_sha.byte1,
           ap->arp_sha.byte2,
           ap->arp_sha.byte3,
           ap->arp_sha.byte4,
           ap->arp_sha.byte5,
           ap->arp_sha.byte6);
}

