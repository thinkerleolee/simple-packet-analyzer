//
// Created by thinkerleo on 17-9-16.
//

#include "ArpAnalyzer.h"

void ArpAnalyzer::get_packet(std::vector <data_pack> &data_pack_buff) {
    //捕获数据包
    int res;
    while ((res = pcap_next_ex(handle, &header, &pkt_data)) >= 0) {
        data_pack temp_packet;
        struct tm *ltime;
        char timestr[16];
        ether_header *eh;
        arp_packet *ap;
        time_t local_tv_sec;

        /* 将时间戳转换成可识别的格式 */
        local_tv_sec = header->ts.tv_sec;
        ltime = localtime(&local_tv_sec);
        strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

        /* 打印数据包的时间戳和长度 */
        char time_stamp[16];    //时间戳
        char len[10];           //数据包大小
        sprintf(time_stamp, "%s.%.6d", timestr, header->ts.tv_usec);
        sprintf(len, "%d", header->len);
        printf("%d ", header->len);
        //printf("%s len:%s", time_stamp, len);


        /* 获得ARP首部的位置 */
        eh = (ether_header *) pkt_data;
        ap = (arp_packet *) ((u_char *) eh + 14);

        char target_ip_str[20];
        char target_mac_str[20];
        char source_ip_str[20];
        char source_mac_str[20];

        /* 打印IP地址和MAC地址 */
        sprintf(target_ip_str, "TargetIP: %3d.%3d.%3d.%3d",
                ap->arp_tpa.byte1,
                ap->arp_tpa.byte2,
                ap->arp_tpa.byte3,
                ap->arp_tpa.byte4);
        sprintf(source_ip_str, " SourceIP: %3d.%3d.%3d.%3d  ",
                ap->arp_spa.byte1,
                ap->arp_spa.byte2,
                ap->arp_spa.byte3,
                ap->arp_spa.byte4);
        sprintf(target_mac_str, " TargetMAC: %2x:%2x:%2x:%2x:%2x:%2x",
                ap->arp_tha.byte1,
                ap->arp_tha.byte2,
                ap->arp_tha.byte3,
                ap->arp_tha.byte4,
                ap->arp_tha.byte5,
                ap->arp_tha.byte6);
        sprintf(source_mac_str, " SourceMAC: %2x:%2x:%2x:%2x:%2x:%2x\n",
                ap->arp_sha.byte1,
                ap->arp_sha.byte2,
                ap->arp_sha.byte3,
                ap->arp_sha.byte4,
                ap->arp_sha.byte5,
                ap->arp_sha.byte6);
        char packet_info[128];
        sprintf(packet_info, "%s%s%s%s", target_ip_str, source_ip_str, target_mac_str, source_mac_str);

        /* 添加数据到缓存 */
        memcpy(temp_packet.data, pkt_data, header->len);
        strcpy(temp_packet.info, packet_info);
        strcpy(temp_packet.length, "42");
        strcpy(temp_packet.protocol, "ARP");
        strcpy(temp_packet.timestr, time_stamp);
        data_pack_buff.push_back(temp_packet);
    }

}
