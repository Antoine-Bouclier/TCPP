#ifndef SERVER_HPP
#define SERVER_HPP

#include <poll.h>
#include <map>
#include <vector>

#include "Client.hpp"

class Server
{
	private:
		int	server_fd;
		
		std::vector<pollfd>		pollFds;
		std::map<int, Client*>	clients;
	public:
		Server();
		~Server();
		void	run();
};

#endif