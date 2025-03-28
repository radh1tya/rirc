#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

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
	char str_port[5];
	int port;
} Server;

int
main(void)
{
	Message *message = malloc(sizeof(Message));
	if (message == NULL) {
		fprintf(stderr, "message *message memory allocation failed\n");
		return 1;
	}

	Info *info = malloc(sizeof(Info));
	if (info == NULL) {
		fprintf(stderr, "Info *info memory allocation failed\n");
		return 1;
	}

	Server *server = malloc(sizeof(Server));
	if (server == NULL) {
		fprintf(stderr, "Server *server memory allocation failed\n");
		return 1;
	}
	
	fprintf(stdout, "rirc - a nothing\n");

	fprintf(stdout, "server: \n");
	fgets(server->domain, 50, stdin);
	server->domain[strcspn(server->domain, "\n")] = '\0';

	fprintf(stdout, "port: \n");
	fgets(server->str_port, 5, stdin);
	server->str_port[strcspn(server->str_port, "\n")] = '\0';	
	server->port = strtol(server->str_port, NULL, 10);

	fprintf(stdout, "nickname: \n");
	fgets(info->nickname, sizeof(info->nickname), stdin);
	info->nickname[strcspn(info->nickname, "\n")] = '\0';

	fprintf(stdout, "username: \n");
	fgets(info->username, sizeof(info->username), stdin);
	info->username[strcspn(info->username, "\n")] = '\0';
	
	fprintf(stdout, "realname: \n");
	fgets(info->realname, sizeof(info->realname), stdin);
	info->realname[strcspn(info->realname, "\n")] = '\0';


	/* fprintf(stdout, "%d", server->port); */

	int status, valread, client_fd;

	struct sockaddr_in server_addr;
}
