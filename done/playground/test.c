#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include <arpa/inet.h>

int main() {
#if 0
	struct addrinfo hint;
	struct addrinfo *servinfo;
	int status;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	if((status = getaddrinfo(NULL, "9999", &hint, &servinfo)) != 0)
		fprintf(stdout, "getaddrinfo error: %s\n", gai_strerror(status));

	char ip[INET6_ADDRSTRLEN];

	inet_ntop(servinfo->ai_family, (struct sockaddr_in*)servinfo->ai_addr, ip, sizeof ip);

	fprintf(stdout, "sizeof 'struct sockaddr': %ld\n sizeof 'strut sockaddr_in': %ld\n sizeof 'sockaddr6': %ld\n", sizeof(struct sockaddr), sizeof(struct sockaddr_in), sizeof(struct sockaddr_in6));

	fprintf(stdout, "addr: %s, port: %d\n", ip, ntohs(((struct sockaddr_in*) servinfo->ai_addr)->sin_port));

	fprintf(stdout, "%d\n", 123);
#endif

	return 0;
}
