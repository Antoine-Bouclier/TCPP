#include <sys/socket.h> // socket(), bind(), accept(), listen()
#include <netinet/in.h> // sockadrr_in
#include <unistd.h> // close()
#include <string.h>
#include <vector>
#include <poll.h>

#include <iostream>

int	main(void)
{
	/* Creating the server socket */
	int	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET		->	Internet protocol v4 addresses (IPV4)
	// SOCK_STREAM	->	TCP socket 

	/* Defining server adress */
	sockaddr_in	serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080); // Converts port to network byte order.
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Accept connections on any IP.
	
	/* Bind socket to adress */
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	/* Listen for incomming connections */
	listen(serverSocket, 5);

	/* Accept client connection */
	int	clientSocket = accept(serverSocket, NULL, NULL);

	/* Receive data from client */
	char	buffer[1024] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);
	std::cout << "Messsage from client: " << buffer << std::endl;

	/* close server socket */
	close(serverSocket);

	return (0);
}

int main(void)
{
	/* Creating the server socket */
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET -> Internet protocol v4 addresses (IPV4)
	// SOCK_STREAM -> TCP socket /* Defining server adress */

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	// Converts port to network byte order. serverAddress.sin_addr.s_addr = INADDR_ANY;
	// Accept connections on any IP.
	
	/* Bind socket to adress */
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	
	/* Listen for incomming connections */
	listen(serverSocket, 5);
	
	std::vector<pollfd> fds;
	pollfd serverPoll;
	
	serverPoll.fd = serverSocket;
	serverPoll.events = POLLIN;
	fds.push_back(serverPoll);
	
	while (1)
	{
		poll(fds.data(), fds.size(), -1);
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == serverSocket)
				{
					/* Accept client connection */
					int clientSocket = accept(serverSocket, NULL, NULL);
					
					/* Adding new pollfd */
					pollfd clientPoll;
					
					clientPoll.fd = clientSocket;
					clientPoll.events = POLLIN;
					fds.push_back(clientPoll);
				}
				else
				{
					/* Handle message */
					char buffer[1024];

					memset(buffer, 0, sizeof(buffer));
					int bytes = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (bytes <= 0)
					{
						close(fds[i].fd);
						fds.erase(fds.begin() + i);
						i--;
					}
					else
						std::cout << "Message: " << buffer << std::endl;
				}
			}
		}
	}
	/* close server socket */
	close(serverSocket); return (0);
}