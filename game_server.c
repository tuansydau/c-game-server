#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int sockfd, newsockfd, portno, n;
char buffer[BUFFER_SIZE];
struct sockaddr_in serv_addr, cli_addr;
socklen_t cli_len;

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

void initSocket()
{
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("Error opening socket");

  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
}

void bindSocket()
{
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("Binding failed.");
  printf("Binding succeeded.\n");
}

void startListening()
{
  if (listen(sockfd, 5) < 0)
  {
    error("failed to listen on sockfd");
  }
}

void handleClientConnection(int clientsockfd)
{
  while (1)
  {
    n = read(clientsockfd, buffer, BUFFER_SIZE);

    if (n == 0)
    {
      error("user has disconnected");
      break;
    }

    if (n < 0)
      error("Error on read");
    printf("%s\n", buffer);
    memset(buffer, 0, BUFFER_SIZE);
  }
}

int acceptConnection()
{
  cli_len = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
  if (newsockfd < 0)
    error("Error on accept");
  return newsockfd;
}

// Main function
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Port number not provided, program terminated.\n");
    exit(1);
  }
  portno = atoi(argv[1]);
  printf("PORT: %d\n", portno);

  // 1. Create a socket
  initSocket();

  // 2. Bind socket to a port
  bindSocket();

  // 3. Listen for connections
  startListening();

  while (1)
  {
    // Check for a new socket and save its file descriptor
    newsockfd = acceptConnection();

    if (fork() == 0)
    {
      // Handle child process
      handleClientConnection(newsockfd);
      exit(1);
    }
  }
  close(newsockfd);

  printf("closed socket\n");
}
