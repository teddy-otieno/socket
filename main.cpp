#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>

int main() {
	std::cout << "Reached here1" << std::endl;
	int server_fd, new_socket, valread;
	struct sockaddr_in address;

	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cerr <<"socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "setsockopt" << std::endl;
		exit(EXIT_FAILURE);
	}

	memset(&address, '0', sizeof(address));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(4000);


	if(listen(server_fd, 10) == -1) {
		std::cerr << "Failed to listen\n";
		exit(EXIT_FAILURE);
	}
	std::cout <<"Listening here 2" << std::endl;

	int conn_fd;
	for(;;) {
		std::cout <<"Starting here" << std::endl;
		conn_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
		if (conn_fd < 0) {
			std::cerr << "Failed to accept connection\n";
			exit(EXIT_FAILURE);
		}

		std::cout <<"Reached here 2" << std::endl;

		valread = read(server_fd, buffer, 1024);
		std::cout << buffer << std::endl;
	}
}