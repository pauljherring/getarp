#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if_arp.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <linux/sockios.h> 
#include <sys/types.h>
#include <ifaddrs.h>
#include <unistd.h>

static char *ethernet_mactoa(struct sockaddr *addr)
{
   static char buff[256];
   unsigned char *ptr = (unsigned char *) addr->sa_data;
   sprintf(buff, "%02X:%02X:%02X:%02X:%02X:%02X", ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);

	return (buff);

} 

int main(int argc, char** argv){
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	struct in_addr addr;
	struct arpreq ar = {0};
	struct sockaddr_in* sin;
	const char* address;
	struct ifaddrs *addrs=0, *taddrs;

	do{
		if (s == -1){
			printf("Unable to open socket: %s(%d)\n", strerror(errno), errno);
			break;
		}

		if (argc<2){
			printf(" getarp <ip address>\n");
			break;
		}
		address = argv[1];

		if (getifaddrs(&addrs) == -1){
			printf(" getifaddrs() failed: %s(%d)\n", strerror(errno), errno);
			break;
		}

		if (inet_pton(AF_INET, address, &addr) != 1){
			printf(" %s not recognised as an ipv4 address", address);
			break;
		}
		sin = (struct sockaddr_in*)&ar.arp_pa;
		sin->sin_family = AF_INET;
		sin->sin_addr = addr;
		
		for(taddrs=addrs; taddrs; taddrs=taddrs->ifa_next){
			if (taddrs->ifa_addr && taddrs->ifa_addr->sa_family == AF_INET){
				strncpy(ar.arp_dev, taddrs->ifa_name, sizeof ar.arp_dev);
				if (ioctl(s,SIOCGARP,&ar) != -1){
					printf("%s(%d) - %s -> %s\n", taddrs->ifa_name, taddrs->ifa_addr->sa_family, address, ethernet_mactoa(&ar.arp_ha));
					continue;
				}
			}
		}
	}while(0);

	if (s!=-1)
		close(s);
	if (addrs)
		freeifaddrs(addrs);
}