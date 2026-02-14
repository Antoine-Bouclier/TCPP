Sockets are a way to speak to other programs using standard Unix file descriptors. To get the file descriptor for network communication, we need to make a call to the ```socket()``` system routine. It return the socket descriptor. We communicate through it using ```send()``` and ```recv()``` socket calls. 

We can also use ```read()```and ```write()```, but ```send()``` and ```recv()``` offer much greater control over the data transmission.

Sockets come in two primary state. An active socket is connected to a remote active socket via an open data connection. A passive socket is not connected, but rather awaits an incoming connection, which will change the state to a new active socket once a connection is established.

Each port can have a single passive socket binded to it, awaiting incoming connections. And they have multiple active sockets, each corresponding to an open connection on the port. The passive socket is waiting for new messages, and when one arrives, the socket initiate a connection and let an active socket read the packet and respond back if necessary. this allows the passive socket to be free to receive new packets.

When a connection is established, the sender can send a **KEEPALIVE** packet at regular intervals to keep the connection alive. 

## socket()

```socket()``` creates an endpoint for communication and returns a file descriptor that refers to that endpoit.

```c
#include <sys/socket.h>

ssize_t	socket(int domain, int type, int protocol);
```

Valid socket types include **SOCK_STREAM** to open a stream socket, **SOCK_DGRAM** to open a datagram socket, and **SOCK_RAW** to open a raw socket to access the IP protocol directly.

* **0** and **IPPROTO_TCP** for TCP stream sockets
* **0** and **IPPROTO_UDP** for datagram socket
* **IPPROTO_SCTP** for SCTP stream sockets

### example :

```c
int	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
```
AF_INET		->	Internet protocol v4 addresses (IPV4) \
SOCK_STREAM	->	TCP socket

## sockaddr - type

```sockaddr``` is a structure for a socket address. ```sockaddr_in``` stand for an IPV4 Internet domain socket address. ```sockaddr_in6``` describes an IPV Internet domain socket address. 

### example :
```c
	sockaddr_in	serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(8080); // Converts port to network byte order.
	serverAdress.sin_addr.s_addr = INADDR_ANY; // Accept connections on any IP.
```

## bind()

```c
#include <sys/socket.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

When a socket is created with ```socket()```, it has no address assigned to it. ```bind()``` assings the address specified by **addr** to the socket reffered to by the file descriptor **sockfd**. addrlen specifies the size. It's similar to assigning a name to a socket.

**Return value**

On success, zero is returned, on error, -1 is returned and **errno** is set to indicate the error. In **webserv** checking the value of **errno** to adjust the server behaviour is strictly **FORBIDDEN** after performing a **read** or **write** operation.

## listen()

Listen for connections on a socket. ```listen()``` marks the socket referred to by **sockfd** as a passive socket.

```c
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

* The **sockfd** argument is a file descriptor that refers to a socket of type **SOCK_STREAM** or **SOCK_SEQPAQUET**.
* The **backlog** argument defines the maximum length to which the queue of pending connections for **sockfd** may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of **ECONNREFUSED**. If the protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.

### Return value

On success, zero is returned. On error, -1 is returned, and **errno** is set to indicate the error.

## accept()

Accept a connection on a socket. the ```accept()``` function is used with connection-based socket types (**SOCK_STREAM**, **SOCK_SEQPAQUET**). It extract the first connection request from the queue of pending connections. it create a new connected socket, in active mode. The passive socket is unaffected by this call.

```c
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *Nullable restrict addr, socklen_t *_Nullable restrict addrlen);
```

* The argument **sockfd** is a socket that has been create with ```socket()```, bound to a local address with ```bind()```, and is listening for connections after a ```listen()```.
* The argument **addr** is a pointer to a **sockaddr** structure. It is filled with the address of the peer socket, when **addr** is null, nothing is filled in, in this case **addrlen** is not used ans should also be null.
* The **addrlen** argument is a value-result argument, the caller must initialize it to contain the size of the structure in bytes pointed by addr. On return it will contain the actual size of the peer address.

### Return value

On success, these system calls return a file descriptor for the accepted socket (non negative integer). On error, -1 is returned, **errno** is set to indicate the error, and addrlen is left unchanged.

## send()

Send data out over a socket. ```send()``` is used fot TCP SOCK_STREAM connected sockets. the parameter **s** is the socket, **buf** is a pointer to the data, len is the number of bytes you want to send, and flags allows to specify more information about the data is to be sent (set to 0 if it's "normal" data).

```c
#include <sys/socket.h>

ssize_t	send(int s, const void *buf, size_t len, int flags);
```

|	MACRO	|	Description	|
|---		|---			|
|	MSG_OOB	|	Send *out-of-bound* data on sockets. The receiver will receive the signal ```SIGURG``` and can receive this data without receiving all the rest of the "normal" data in the queue.|
|	MSG_DONTROUTE	|	Keep the data in local, don't sending it over a router. |

**Return value**

Returns the number of bytes actually send, or -1 on error. The number of bytes might be less than expected (It can be handled). if the socket has been closed, we will get the signal SIGPIPE.

## recv()

Receive data on a socket.

## stream sockets