#include "my_socket.h"

int main_socket_client(int argc, char *argv[]){
		int sock;
		struct sockaddr_in server;
		struct hostent *hp;

		/*  create socket
			 *  int socket(int domain, int type, int protocol);
			 * SOCK_STREAM --> TCP: two-way, connection based type
			 * SOCK_DGRAM --> UDP // SOCK_RAW --> raw socket
			 * AF_INET:IPv4 Internet Protocol
			 * */
			sock = socket(AF_INET, SOCK_STREAM, 0 );
			if (sock<0){
				perror("my socket: error in openning socket /n/n ");
				exit(1);
			}

		hp = gethostbyname( (char *) argv[1]);

		if (hp == NULL){
			close(sock);
			perror("my socket: error in gethostbyname /n/n ");
							exit(1);
		}

		memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
			server.sin_family = AF_INET;
			server.sin_addr.s_addr=inet_addr("169.254.171.140");
			server.sin_port= htons(PORT_ADDR);

		if(connect(sock, (struct sockaddr *) &server, sizeof(server) ) < 0){
			close(sock);
			perror("my socket: error in connect /n/n ");
										exit(1);
		}
/* send data
 * ssize_t send(int sockfd, const void *buf, size_t len, int flags);
 * */
		if(send(sock, SEND_DATA,sizeof(SEND_DATA), 0) < 0){
			perror("my socket: error in sending data /n/n ");
			close(sock);
			exit(1);
		}
		printf ("Sent %s \n\n", SEND_DATA);
		close(sock);

		return 0;
}

int main_socket_server(int argc, char *argv[]) {

	int sock;
	struct sockaddr_in server;
	int mysock;
	char buf[1024];
	int rval;

	/*  create socket
	 *  int socket(int domain, int type, int protocol);
	 * SOCK_STREAM --> TCP: two-way, connection based type
	 * SOCK_DGRAM --> UDP // SOCK_RAW --> raw socket
	 * AF_INET:IPv4 Internet Protocol
	 * */
	sock = socket(AF_INET, SOCK_STREAM, 0 );
	if (sock<0){
		printf("my socket: error in openning socket /n/n ");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port= htons(PORT_ADDR);

	/* call bind
	 * int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
	 * */
	int out_bind = bind(sock, (struct sockaddr *) &server, sizeof(server));
	if( out_bind){
		perror("my socket: error in binding socket /n/n ");
		close(sock);
		exit(1);
	}


	/* listen
	 * int listen(int sockfd, int backlog);
	 *
	 * The backlog argument defines the maximum length to which the queue of
       pending connections for sockfd may grow.
	 * */
	if(listen(sock,NUMBER_OF_CONNECTION_LISTEN)){
		perror("my socket: error in listening socket /n/n ");
		close(sock);
		exit(1);
	}
	printf("my socket: start listening ...  \n\n");
	/*   accept
	 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	 * if we need more connections, we should alocate a process to each connection with fork
	 * but now, we need just one connection
	 * */
	 do {
		 mysock=accept(sock, (struct sockaddr *) 0, 0);
		 if (mysock == -1){
			 perror("my socket: error in accepting socket /n/n ");
			 close(sock);
			 exit(1);
		 }else{
			 memset(buf,0,sizeof(buf));
			 /* receive data
			  * ssize_t recv(int sockfd, void *buf, size_t len, int flags);
			  *  */
			 rval=recv(mysock, buf, sizeof(buf), 0);
			 if (rval <0){
				 close(sock);
				 perror("my socket: error in reading message  /n/n ");
				 			 exit(1);
			 }else if (rval == 0){
				 printf("my socket: Ending connection  \n\n");

			 }else {
				 printf( "MSG: %s \n", buf);
			 }
		 }
		 printf("my socket: Got the message (rval =%d)  \n\n", rval);
		 close(mysock);
	 }while(1);

	return 0;
}
