#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>
#define MAXBYTES2CAPTURE  2048

void ProcessPacket(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
	int i = 0, *counter = (int *)arg;
	printf("Packet Count : %d\n", ++(*counter));
	printf("Received Packet Size: %d\n", pkthdr->len);
	printf("Payload:\n");
	
	for (i=0; i<pkthdr->len; i++)
	{
		printf("%02x  ", (unsigned int)packet[i]);

		if ( (i%16 == 15 && i != 0) || (i == pkthdr->len -1))
		{
			printf("\n");
		}
	}
	printf("\n\n************************************************\n");
	return;
}	

int main(int argc, char *argv[])
{
	struct in_addr address,
				   netmask;
	int i = 0, count = 0;
	pcap_t *descr = NULL;
	char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;
	bpf_u_int32 netaddr = 0, mask = 0;
	struct bpf_program filter;
//	char *str = "arp and ether host 00:0c:29:ed:c4:33";
	char *str = "src host 192.168.0.120";

	memset(errbuf, 0, sizeof(errbuf));

	if (argc != 2)
		device = pcap_lookupdev(errbuf);
	else
		device = argv[1];
	
	printf("Try to open device %s\n", device);
	
	pcap_lookupnet(device, &address.s_addr, &netmask.s_addr, errbuf);
	puts("device info:");
	printf("dev:%s\n", device);
	printf("net:%s\n", inet_ntoa(address));
	printf("mask:%s\n", inet_ntoa(netmask));

	if((descr = pcap_open_live(device, MAXBYTES2CAPTURE, 1, 0, errbuf)) < 0) {
		printf("error : %s\n", errbuf);
		exit(-1);
	}
	

	if (pcap_compile(descr, &filter, str, 0, mask) < 0) {
		printf("pcap_compile error\n");
		exit(-1);
	}
	pcap_setfilter(descr, &filter);

	pcap_loop(descr, 2, ProcessPacket, (u_char *)&count);

	return 0;
}
