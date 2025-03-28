#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

typedef struct Message {
	char content[256];
	struct Message *next;
} Message;

typedef struct Info {
	char nickname[50];
	char username[50];
	char realname[50];
} Info;

typedef struct Server {
	char domain[50];
	int port;
} Server;

int
main(void)
{
}
