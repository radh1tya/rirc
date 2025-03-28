#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

typedef struct Message {
	char *content;
	struct Message *next;
} Message;

typedef struct Account {
	char nickname[10];
	char username[10];
	char realname[10];
	char password[10];
} Account;

enum ACCOUNT {
	NICKNAME,
	USERNAME,
	REALNAME
};

typedef struct Server {
	char *domain;
	char *str_port;
	int port;
	struct Server *next;
} Server;

void
clearScreen(void)
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}

Server 
*struct_server(void)
{
	Server *server = malloc(sizeof(Server));
	if (server == NULL) {
		fprintf(stderr, "Failed malloc(sizeof(server))\n");
		exit(1);
	}
	return server;
}

Server
*server_node(char domain[50], char str_port[6], int port)
{
	Server *node = malloc(sizeof(Server)); 
	node->domain = domain;
	node->str_port = str_port;
	node->next = NULL;
	return node;
}

Account 
*struct_account(void)
{
	Account *account = malloc(sizeof(Account));
	if (account == NULL) {
		fprintf(stderr, "Failed malloc(sizeof(account))\n");
		exit(1);
	}
	return account;
}

char
*accountfoo(Account *account, enum ACCOUNT ACCOUNTNUM)
{
	char *target;
	const char *label;

	switch (ACCOUNTNUM) {
		case NICKNAME:
		target = account->nickname;
		label = "nickname";
		break;
		case USERNAME:
		target = account->username;
		label = "username";
		break;
		case REALNAME:
		target = account->realname;
		label = "realname";
	}

	fprintf(stdout, "%s: \n", label);
	fgets(target, 10, stdin);
	target[strcspn(target, "\n")] = '\0';
	return target;
}

char
*putdomain(void)
{
	char *domain = malloc(50 * sizeof(char));
	fprintf(stdout, "server: \n");
	fgets(domain, 50, stdin);
	domain[strcspn(domain, "\n")] = '\0';
	return domain;
}

int
putport(void)
{
	int port;
	char *str_port = malloc(6 * sizeof(char));
	fprintf(stdout, "port: \n");
	fgets(str_port, 6, stdin);
	str_port[strcspn(str_port, "\n")] = '\0';	
	port = strtol(str_port, NULL, 10);
	return (int)port;
}

Server
*coba(Server *server)
{
	Server *tmp = malloc(sizeof(Server));

	tmp->domain = putdomain();
	tmp->port = putport();
	tmp->next = NULL;

	if(server == NULL) 
		return tmp;

	Server *ptr = server;
	while(ptr->next != NULL) {
		ptr = ptr->next;
	}

	ptr->next = tmp;
	return server;
}

Server
*display(Server *server)
{
	Server *ptr = server;

	if ( ptr == NULL ) {
		printf("null\n");
	}
	while (ptr != NULL) {
		fprintf(stdout,"%s\n%d\n", ptr->domain, ptr->port);
		ptr = ptr->next;
	}
	return server;
}
int
create_socket_ssl(int sockfd) {
	char buffer[1024];
	SSL_CTX *ctx = SSL_CTX_new(TLS_method());
	SSL *ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sockfd);
	SSL_connect(ssl);
	SSL_read(ssl, buffer, 1023);
	printf("%s\n", buffer);
}

int
create_socket(char *domain, int port)
{

	int sockfd;
	struct sockaddr_in saddr;
	struct hostent *host_t;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "sockfd failed\n");
		return 1;
	}

	host_t = gethostbyname(domain);
	if (host_t == NULL) {
		fprintf(stderr, "gethostbyname failed\n");
		return 1;
	}
	
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	memcpy(&saddr.sin_addr.s_addr, 
			host_t->h_addr_list[0], 
			host_t->h_length);

	int status = connect(sockfd,
						(struct sockaddr*)&saddr, 
						sizeof(saddr));

	if (port == 6697) {
		create_socket_ssl(sockfd);
	}

	if (status == 0) {
		fprintf(stdout,"connected %s\n", domain);
	} else {
		fprintf(stderr,"status failed");
		return 1;
	}

	return sockfd;
}

int
main(void)
{
	Message *message = malloc(sizeof(Message));
	if (message == NULL) {
		fprintf(stderr, "message *message memory allocation failed\n");
		return 1;
	}

	Account *account = malloc(sizeof(Account));
	if (account == NULL) {
		fprintf(stderr, "Account *account memory allocation failed\n");
		return 1;
	}

	
	fprintf(stdout, "rirc - a nothing\n");

	Server *server = NULL;
	server = coba(server);
	display(server);
	char *username = accountfoo(account, USERNAME);	
	char *realname = accountfoo(account, REALNAME);
	char *nickname = accountfoo(account, NICKNAME);

	int create = create_socket(server->domain,server->port);	
	
	close(create);
}
