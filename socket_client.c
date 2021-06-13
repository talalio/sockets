#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client_address;
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(9002);
	client_address.sin_addr.s_addr = INADDR_ANY;
	
	int connection_status = connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address));
	
	if(connection_status == -1){
		printf("[ERR] CONNECTION FAILED");
	}
	
	char server_response[256];
	recv(client_socket, &server_response, sizeof(server_response), 0);
	
	printf("[INFO] SERVER SENT: %s\n", server_response);
	
	close(client_socket);
	
	return 0;
}
