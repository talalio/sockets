#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	
	char *dest = argv[1];
	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client_address;
	client_address.sin_family = AF_INET;
	client_address.sin_port	  = htons(80);
	inet_aton(dest, &client_address.sin_addr.s_addr); 
	
	connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address));
	
	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];
	
	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);
	
	printf("%s\n", response);
	close(client_socket);
	
	return 0;
}
