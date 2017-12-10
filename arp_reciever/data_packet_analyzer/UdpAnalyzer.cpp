//
// Created by thinkerleo on 17-9-16.
//

#include "UdpAnalyzer.h"

void UdpAnalyzer::get_packet(std::vector <data_pack> &data_pack_buff) {
    int res;
    while ((res = pcap_next_ex(handle, &header, &pkt_data)) >= 0) {
        data_pack temp_packet;
        struct tm *ltime;
        char timestr[16];
        ip_header *ih;
        udp_header *uh;
        u_int ip_len;
        u_short sport, dport;
        time_t local_tv_sec;

        /* 将时间戳转换成可识别的格式 */
        local_tv_sec = header->ts.tv_sec;
        ltime = localtime(&local_tv_sec);
        strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

        /* 打印数据包的时间戳和长度 */
        char time_stamp[16];    //时间戳
        char len[10];           //数据包大小
        sprintf(time_stamp, "%s.%.6d", timestr, header->ts.tv_usec);
        sprintf(len, "%d ", header->len);
        //printf("%s len:%s", time_stamp, len);

        /* 获得IP数据包头部的位置 */
        ih = (ip_header *) (pkt_data +
                            14); //以太网头部长度

        /* 获得UDP首部的位置 */
        ip_len = (ih->ver_ihl & 0xf) * 4;
        uh = (udp_header *) ((u_char *) ih + ip_len);

        /* 将网络字节序列转换成主机字节序列 */
        sport = ntohs(uh->sport);
        dport = ntohs(uh->dport);
        char packet_info[128];

        /* 打印IP地址和UDP端口 */
        sprintf(packet_info, "%d.%d.%d.%d:%d -> %d.%d.%d.%d:%d\n",
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
        //printf("%s", temp_packet.info);

        memcpy(temp_packet.data, pkt_data, header->len);
        strcpy(temp_packet.info, packet_info);
        strcpy(temp_packet.length, len);
        strcpy(temp_packet.protocol, "UDP");
        strcpy(temp_packet.timestr, time_stamp);
        data_pack_buff.push_back(temp_packet);

        //回收内存
        delete ih;
        delete uh;
        delete ltime;
     }
}
