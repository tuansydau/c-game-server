#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
// Serverside process for HTTP/0.9
// 1. Create a socket: Socket(domain, type, protocol) -> sockfd
// 2. Bind the socket to a port: Bind(sockfd, *addr, addrlen)
// 3. Listen for connections: listen(sockfd, backlog)
//          clientside: connect(sockfd, *addr, addrlen)
// 4. Accept a connection: accept(sockfd, &addr, &addrlen) -> newsockfd
// 5. Read and validate request: read(newsockfd, buffer, buffer_size)
// 6. Write a response: write(newsockfd, buffer, buffer_size)
// 7. Close the connection after responding

void error(const char *msg) {
  perror(msg);
  exit(1);
}

// Main function
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Port number not provided, program terminated.");
    exit(1);
  }

  int sockfd, newsockfd, portno, n;
  char buffer[255];

  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("Error opening socket");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  printf("PORT: %d\n", portno);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))){
    error("Binding failed.");
  }
  
  printf("Binding succeeded.");

  printf("\n");
}
