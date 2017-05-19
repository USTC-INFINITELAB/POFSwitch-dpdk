#include "string.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "net/if.h"
#include "sys/ioctl.h"
#include "arpa/inet.h"
#include "ifaddrs.h"
#include "stdio.h"

#define MAX_PORT_NAME_LEN 32
#define MAX_HWADDR_LEN 6
#define MAX_HWADDR_STR_LEN 32
#define MAX_PORT_NUM 32


struct port_info{
    char name[MAX_PORT_NAME_LEN];
    char hwaddr[MAX_HWADDR_STR_LEN];
    
};
static uint32_t mac_to_str(unsigned char mac_addrs[], char mac_str[]) {

	//sprintf(mac_str, "%d", mac_addrs->addr_bytes[0]);
	sprintf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x", mac_addrs[0],
			mac_addrs[1], mac_addrs[2],
			mac_addrs[3], mac_addrs[4],
			mac_addrs[5]);
        //mac_str[MAX_HWADDR_STR_LEN] = '\0';
	//printf("mac_str %s\n", mac_str);
	return 0;
}
static uint32_t get_hwaddr_by_name(const char name[], char hwaddr[]) {
	struct ifreq ifr; /* Interface request. */
	struct sockaddr_in *sin;
	int sock;
        unsigned char tmp[MAX_HWADDR_LEN];
	if (-1 == (sock = socket(AF_INET, SOCK_STREAM, 0))) {
		printf("GET SOCK ERROR\n");
	}
        memset(tmp, 0, MAX_HWADDR_LEN);
	//memset(hwaddr, 0, MAX_HWADDR_STR_LEN);
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, name, strlen(name) + 1);

	/* Get hardware address. */
	if (-1 == ioctl(sock, SIOCGIFHWADDR, &ifr)) {
		close(sock);
		printf("GET MAC ADDRESS ERROR\n");
	} else {
		memcpy(tmp, ifr.ifr_hwaddr.sa_data, MAX_HWADDR_LEN);
                if(mac_to_str(tmp, hwaddr)!=0)
                    printf("MAC TO STR ERROR\n");
                //printf("MAC %s\n",hwaddr);
	}

	close(sock);
	return 0;
}


static uint32_t get_port_info(struct port_info port[])
{
    //struct port_info port[MAX_PORT_NUM];
    //printf("in the get_port_info\n");
    struct ifaddrs *addrs, *tmp;
    int i=0;
    int port_num=0;
    getifaddrs(&addrs);
    for (tmp = addrs; tmp != NULL ; tmp = tmp->ifa_next) {
	if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET) {
             if (strcmp(tmp->ifa_name, "lo") == 0) {
		continue;
	     }
             strcpy(port[i].name,tmp->ifa_name);
             //printf("port name is %s\n",port[i].name);
             i++;
	}
    }
    freeifaddrs(addrs);
    port_num = i;
    for(i=0;i<port_num;i++){
        //printf("port name is %s\n",port[i].name);
        if(get_hwaddr_by_name(port[i].name, port[i].hwaddr)!=0)
             printf("GET HWADDR BY NAME ERROR\n");
    }

    //printf("port name is %s\n",port[i].name);
    return port_num; 
}
void main(void)
{
    char filename[] = "/usr/local/src/interfaces-index";
    FILE *fp;
    struct port_info port[MAX_PORT_NUM];
    int i=0;
    uint32_t ret=0;
    ret = get_port_info(port);
    if(ret == 0)
        printf("GET PORT INFOMATION ERROR\n");
    fp = fopen(filename, "w");
    if(fp==NULL)
       printf("FILE %s OPEN FAILED\n", filename);
    for(i=0;i<ret;i++)
        fprintf(fp, "HWADDR=\"%s\", NAME=\"%s\"\n",port[i].hwaddr, port[i].name);   
    fclose(fp);

}
