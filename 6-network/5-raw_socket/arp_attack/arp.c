#include "arp.h"

int send_arp(int sockfd, struct in_addr ip4_sender, struct in_addr ip4_target)
{
    struct sockaddr_ll  ll_addr;
    struct frame_ether  {
        struct ether_header eth_header;
        struct arphdr arp_header;
        unsigned char src_mac[MAC_LEN];
        unsigned char src_ip[IP4_LEN];
        unsigned char dst_mac[MAC_LEN];
        unsigned char dst_ip[IP4_LEN];
    }frame_buff;
	struct sockaddr mac_sender;

/* get sender`s macaddress */
	gethwaddr(DEV_NAME, &mac_sender);
    
/* fill ll_addr  */
    memset(&ll_addr, 0, sizeof(ll_addr));
    ll_addr.sll_family = AF_PACKET;
    /* set the broadcast mac address: ff:ff:ff:ff:ff:ff */
#if 1
	memset(ll_addr.sll_addr, 0xff, sizeof(ll_addr.sll_addr));
#else
	char mac_gw[6] = {0x14,0xd6, 0x4d, 0xe3, 0x56, 0x36};
	memcpy(ll_addr.sll_addr, mac_gw, MAC_LEN);
#endif
    ll_addr.sll_halen = MAC_LEN;     /**/
    ll_addr.sll_ifindex = getifindex(DEV_NAME);

/* fill frame structure */
	/* fill ether header */
    memset(frame_buff.eth_header.ether_dhost, 0xff, MAC_LEN);
    memcpy(frame_buff.eth_header.ether_shost, mac_sender.sa_data, MAC_LEN);
    frame_buff.eth_header.ether_type = htons(ETHERTYPE_ARP);
	
	/* fill arp header */
    frame_buff.arp_header.ar_hrd = htons(ARPHRD_ETHER);
    frame_buff.arp_header.ar_pro = htons(ETHERTYPE_IP);
    frame_buff.arp_header.ar_hln = MAC_LEN;
    frame_buff.arp_header.ar_pln = IP4_LEN;
    frame_buff.arp_header.ar_op = htons(ARPOP_REQUEST);

	/* fill arp body */
    memcpy(frame_buff.src_mac, mac_sender.sa_data, MAC_LEN);
	memcpy(frame_buff.src_ip, &ip4_sender.s_addr, IP4_LEN);
	
	memset(frame_buff.dst_mac, 0, MAC_LEN);
	memcpy(frame_buff.dst_ip, &ip4_target.s_addr, IP4_LEN);

#if DEBUG
	printf("src_mac: %#x\n", *(int *)frame_buff.src_mac);
	printf("src_ip:  %#x\n", *(int *)frame_buff.src_ip);
	printf("dst_mac: %#x\n", *(int *)frame_buff.dst_mac);
	printf("dst_ip:  %#x\n", *(int *)frame_buff.dst_ip);
#endif
    

    if (-1 == sendto(sockfd, &frame_buff, sizeof(frame_buff), 0,
            (struct sockaddr *)&ll_addr, sizeof(ll_addr)))
        error_exit("sendto");

    return 0;
}
