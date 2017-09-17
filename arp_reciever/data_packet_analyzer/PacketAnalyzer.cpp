//
// Created by leo on 17-9-16.
//remp

#include "PacketAnalyzer.h"

bool PacketAnalyzer::init_temp_file(char *packet_filter) {
    netmask=0xffffff;
    /* open file */
    if ( (handle = pcap_open_offline (PCAP_SRC_FILE,  // 我们要打开的文件
                                      errbuf          // 错误缓冲区
    ) ) == NULL)
    {
        fprintf(stderr,"\nError creating a source string\n");
        return false;
    }
    pcap_compile(handle,&fcode,packet_filter,1,netmask);
    //设置过滤器
    if (pcap_setfilter(handle, &fcode)<0)
    {
        fprintf(stderr,"\nError setting the filter.\n");
    }
}
