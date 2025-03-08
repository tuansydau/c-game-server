#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 256

void error(const char *msg) {
  perror(msg);
  exit(1);
}

// Main function
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Port number not provided, program terminated.\n");
    exit(1);
  }

  int sockfd, newsockfd, portno, n;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t cli_len;

  // 1. Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("Error opening socket");

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  printf("PORT: %d\n", portno);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  // 2. Bind socket to a port
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("Binding failed.");

  printf("Binding succeeded.\n");

  // 3. Listen for connections
  if (listen(sockfd, 5) < 0) {
    error("failed to listen on sockfd");
  }

  while (1) {
    // Check for a new socket and save its file descriptor
    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
    if (newsockfd < 0)
      error("Error on accept");

    if (fork() == 0) {
      while (1) {
        n = read(newsockfd, buffer, BUFFER_SIZE);

        if (n == 0) {
          error("user has disconnected");
          break;
        }

        if (n < 0)
          error("Error on read");
        printf("buffer: %s\n", buffer);
        bzero(buffer, BUFFER_SIZE);
      }
      exit(1);
    }
  }
  close(newsockfd);

  printf("closed socket\n");
}
