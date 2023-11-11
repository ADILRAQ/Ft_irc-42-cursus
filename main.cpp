#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#define BACKLOG 10
#define POLLSIZE 512

int	main()
{
	int				fdSocket, newSocket, error, reuseaddr = 1, flag;
	struct addrinfo	hints, *result;
	struct sockaddr_storage	inData;
	socklen_t	size;

	memset(&hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// TODO : Get localhost infos
	if ((error = getaddrinfo("localhost", "8080", &hints, &result)) != 0)
	{
		std::cout << "GADDRI: " << gai_strerror(error) << std::endl;
		return (1);
	}
	// TODO : Create a socket FD
	if ((fdSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) < 0)
	{
		perror("Socket ");
		freeaddrinfo(result);
		return (1);
	}
	// TODO : Change the status of the FD to NON-BLOCKING mode
	if ((flag = fcntl(fdSocket, F_GETFL, 0)) == -1)
	{
		freeaddrinfo(result);
		return (perror("Fcntl1 "), 1);
	}
	if (fcntl(fdSocket, F_SETFL, flag | O_NONBLOCK) == -1)
	{
		freeaddrinfo(result);
		return (perror("Fcntl2 "), 1);
	}
	// TODO : Reuse the port if 
	if (setsockopt(fdSocket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)))
		std::cout << "RESUSE: " << strerror(errno) << std::endl;
	if ((error = bind(fdSocket, result->ai_addr, result->ai_addrlen)) < 0)
	{
		perror("Bind ");
		freeaddrinfo(result);
		return (close(fdSocket), 1);
	}
	// TODO:
	freeaddrinfo(result);
	// TODO : Listening on incoming connections
	if (listen(fdSocket, 10) < 0)
	{
		perror("Listen ");
		freeaddrinfo(result);
		return (close(fdSocket), 1);
	}
	struct pollfd	fds[POLLSIZE];
	fds[0].fd = fdSocket;
	fds[0].events = POLLIN;
	while (1)
	{
		// TODO : Accepting incoming connections
		size = sizeof(struct sockaddr_storage);
		newSocket = accept(fdSocket, (struct sockaddr *) &inData, &size);
		if (newSocket < 0)
		{
			perror("Accept ");
			freeaddrinfo(result);
			return (close(fdSocket), 1);
		}
		std::cout << "NICE!" << std::endl;
		flag = 0;
		char	buf[100];
		memset(buf, '\0', 100);
		recv(newSocket, buf, 100, 0);
		send(newSocket, buf, strlen(buf), 0);
	}
	close(fdSocket);
	return (0);
}
