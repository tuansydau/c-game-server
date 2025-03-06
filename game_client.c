#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

void error(const char *msg) {
  perror(msg);
  printf("\n");
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
    exit(1);
  }

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  char buffer[256];

  // 1. Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("Error opening socket");

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[2]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // 2. Connect to server
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    error("Failed to connect to the server");
  }

  // 3. Write request (msg for now) to server
  bzero(buffer, sizeof(buffer));
  strcpy(buffer, "test msg!");

  n = write(sockfd, buffer, strlen(buffer) - 1);
  if (n < 0)
    error("Error writing to socket");

  printf("attempting to write to socket\n");

  n = read(sockfd, buffer, sizeof(buffer));

  if (n < 0)
    error("error reading from socket");

  printf("server response: %s\n", buffer);

  close(sockfd);
  printf("closed socket\n");
}
