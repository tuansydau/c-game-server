#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 256

void error(const char *msg) {
  perror(msg);
  printf("\n");
  exit(1);
}

int main(int argc, char **argv) {
  //if (argc < 3) {
  //  fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
  //  exit(1);
  //}

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE];

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
  bzero(buffer, BUFFER_SIZE);
  char message[256];
  snprintf(message, sizeof(message), "test string from %s", argv[3]);

  while (1) {
    //bzero(buffer, BUFFER_SIZE);
    strcpy(buffer, message);
    n = write(sockfd, buffer, strlen(buffer));
    printf("buffer: %s\n", buffer);

    if (n < 0)
      error("Error writing to socket");

    usleep(50000);

    // n = read(sockfd, buffer, BUFFER_SIZE);

    // if (n < 0)
    //   error("error reading from socket");

    // printf("server response: %s\n", buffer);
  }
  close(sockfd);
  printf("closed socket\n");
}
