#include <sys/socket.h> // socket(), bind(), accept(), listen()
#include <netinet/in.h> // sockadrr_in
#include <unistd.h> // close()
#include <string.h>

#include <iostream>

bool send_all(int socket, const char* buffer, size_t length)
{
	size_t totalSent = 0;
	
	while (totalSent < length)
	{
		ssize_t sent;

		sent = send(socket, buffer + totalSent, length - totalSent, 0);
		if (sent <= 0)
			return (false);
		totalSent += sent;
	}
	return (true);
}

int	main(void)
{
	/* Creating the client socket */
	int	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* Defining client adress */
	sockaddr_in	serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080); // Converts port to network byte order.
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Accept connections on any IP.

	/* Connect to server */
	connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	/* Send data to the server */
	const char* message = "Hello, server!";
	send(clientSocket, message, strlen(message), 0);

	/* close client socket */
	close(clientSocket);
	return (0);
}