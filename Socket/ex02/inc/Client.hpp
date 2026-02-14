#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

enum State
{
	READING,
	ZRITING,
	DONE
};

class Client
{
	private:
		int			fd;
		std::string	readBuffer;
		std::string	writeBuffer;
		bool		requestComplete;
	public:
		Client(int fd);
		~Client();
};


#endif