#include <stdlib.h>
#include <stdio.h>

#include <pcap.h>

 int main(int argc, char **argv)
{
pcap_t *fp;
char errbuf[PCAP_ERRBUF_SIZE];
u_char packet[100];
int i;

    /* 检查命令行参数的合法性 */
    if (argc != 2)
    {
        printf("usage: %s interface (e.g. 'rpcap://eth0')\n", argv[0]);
        exit(2);
    }

    /* 打开输出设备 */
    if ( (fp= pcap_open_live(argv[1],            // 设备名
                        100,                // 要捕获的部分 (只捕获前100个字节)
                        true,  // 混杂模式
                        1000,               // 读超时时间
                        errbuf              // 错误缓冲
                        ) ) == NULL)
    {
        fprintf(stderr,"\nUnable to open the adapter. %s is not supported by LibPcap\n", argv[1]);
        exit(-2);
    }

    /* 假设在以太网上，设置MAC的目的地址为 1:1:1:1:1:1 */
    packet[0]=1;
    packet[1]=1;
    packet[2]=1;
    packet[3]=1;
    packet[4]=1;
    packet[5]=1;

    /* 设置MAC源地址为 2:2:2:2:2:2 */
    packet[6]=2;
    packet[7]=2;
    packet[8]=2;
    packet[9]=2;
    packet[10]=2;
    packet[11]=2;

    /* 填充剩下的内容 */
    for(i=12;i<100;i++)
    {
        packet[i]=i%256;
    }

    /* 发送数据包 */
    if (pcap_sendpacket(fp, packet, 100 /* size */) != 0)
    {
        fprintf(stderr,"\nError sending the packet: \n", pcap_geterr(fp));
        exit(-2);
    }

    return 0;
}