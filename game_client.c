#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int sockfd;

void error(const char *msg) {
  perror(msg);
  printf("\n");
  exit(1);
}

void cleanup(int signum) {
  if (sockfd != -1) {
    close(sockfd);
    printf("Socket closed due to signal %d\n", signum);
  }
  exit(0);
}

int main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s <server_ip> <port> <client_#>\n", argv[0]);
    exit(1);
  }

  int portno, n;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE];

  // 1. Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("Error opening socket");
  
  signal(SIGINT, cleanup);

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[2]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // 2. Write request (msg for now) to server
  bzero(buffer, BUFFER_SIZE);
  char message[256];
  snprintf(message, sizeof(message), "test string from %s", argv[3]);
  
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    error("failed to connect to server");
  }
  printf("%d", sockfd);
  while (1) {
    strcpy(buffer, message);
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
      error("Error writing to socket");

    printf("buffer: %s\n", buffer);

    usleep(1000000);
  }
  close(sockfd);
  printf("closed socket\n");
}
