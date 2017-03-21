#include <pcap/pcap.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int in_addr;
	int in_netmsk;
	char errbuff[PCAP_ERRBUF_SIZE];

	struct in_addr address,
				   netmask;
	char *dev;
	
	if( NULL == (dev = pcap_lookupdev(errbuff)))
	{
		puts(errbuff);
		return -1;
	}
	puts(dev);
	
	if(0 > pcap_lookupnet(dev, &in_addr, &in_netmsk, errbuff))
	{
		puts(errbuff);
		return -1;
	}


	address.s_addr = in_addr;
	netmask.s_addr = in_netmsk;
#if 1
	printf("%s:\n%#x:%#x\n", dev, address.s_addr, netmask.s_addr);
	
	printf("device:%s\nnet:%s\n", dev, inet_ntoa(address)); 
	printf("mask:%s\n", inet_ntoa(netmask));
#endif

	return 0;
}
