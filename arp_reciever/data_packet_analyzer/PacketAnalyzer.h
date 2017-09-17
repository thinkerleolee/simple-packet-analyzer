//
// Created by leo on 17-9-16.
//

#ifndef PCAP_TASK_PACKETANALYZER_H
#define PCAP_TASK_PACKETANALYZER_H

#define PCAP_BUF_SIZE   1024
#define PCAP_SRC_FILE   "temp.dat"
#define LINE_LEN 16

#include <iostream>
#include <pcap/pcap.h>
#include <pcap.h>
#include <ctime>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <vector>

/***************** 各个数据类型所占大小 *****************
 * ****************
 * 数据类型  字节数 *
 * u_char:     1  *
 * u_short:    2  *
 * u_int:      4  *
 * uint8_t     8  *
 * uint16_t    16 *
 * ***************/

/* 自定义数据包格式 */
typedef struct data_pack{
    char timestr[16];       //时间（Time）
    char protocol[16];      //协议类型(Type of Protocol)
    char length[10];        //数据包长度(Length of Packet)
    char info[128];         //数据包信息(Info of  Packet)
    u_char data[65535];     //数据包(DataPacket)
}data_pack;

/* 6字节的mac地址（硬件地址） */
typedef struct mac_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;
}mac_address;

/* 4字节的IP地址 */
typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

/***************** 各个网络协议的数据类型 *****************
/* 以太网首部 */
typedef struct ether_header{
    mac_address ether_dhost;    //以太网目的地址
    mac_address ether_shost;    //以太网源地址
    u_short ehter_type;         //帧类型
}ether_header;

/* ARP首部 */
typedef struct arp_header{
    u_short ar_hrd;   //硬件类型
    u_short ar_pro;   //协议类型
    u_char ar_hln;    //硬件地址长度
    u_char ar_pln;    //协议地址长度
    u_short ar_op;    //操作符
}arp_header;

/* ARP请求/应答包 */
typedef struct arp_packet{
    arp_header a_header;   //ARP首部
    mac_address arp_sha;   //发送者硬件地址
    ip_address arp_spa;    //发送者IP地址
    mac_address arp_tha;   //目的硬件地址
    ip_address arp_tpa;    //目的IP地址
}arp_packet;

/* RARP首部 */

/* ICMP首部 */

/* IGMP首部 */


/* IPv4 首部 */
typedef struct ip_header{
    u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)
    u_char  tos;            // 服务类型(Type of service)
    u_short tlen;           // 总长(Total length)
    u_short identification; // 标识(Identification)
    u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)
    u_char  ttl;            // 存活时间(Time to live)
    u_char  proto;          // 协议(Protocol)
    u_short crc;            // 首部校验和(Header checksum)
    ip_address  saddr;      // 源地址(Source address)
    ip_address  daddr;      // 目的地址(Destination address)
    u_int   op_pad;         // 选项与填充(Option + Padding)
}ip_header;

/* UDP 首部*/
typedef struct udp_header{
    u_short sport;          // 源端口(Source port)
    u_short dport;          // 目的端口(Destination port)
    u_short len;            // UDP数据包长度(Datagram length)
    u_short crc;            // 校验和(Checksum)
}udp_header;

class PacketAnalyzer {

protected:
    pcap_t *fp;
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    char source[PCAP_BUF_SIZE];
    struct pcap_pkthdr *header;
    const u_char *pkt_data;
    struct bpf_program fcode;//已经编译好的过滤器
    /* 我们假设一个C类的掩码 */
    u_int32_t netmask;

public:
    bool init_temp_file(char packet_filter[]);

    virtual void get_packet(std::vector<data_pack> &data_pack_buff){};
};



#endif //PCAP_TASK_PACKETANALYZER_H
