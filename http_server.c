#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	
	FILE *html_data = fopen("index.html", "r");
	
	char response_body[1024];
	fgets(response_body, 1024, html_data);
	
	char response_header[2048] = "HTTP/1.1 200 OK\r\n\n";
	
	strcat(response_header, response_body);
	
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port   = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	
	
	int client;
	
	while(1) {
		client = accept(server_socket, NULL, NULL);
		send(client, response_header, sizeof(response_header), 0);
		close(client);
	}
	
	close(server_socket);

	return 0;
}
