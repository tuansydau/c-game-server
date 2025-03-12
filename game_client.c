#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int sockfd;
struct sockaddr_in serv_addr;
int portno, n;
char buffer[BUFFER_SIZE];
char *serv_addr_str;

// General error handler
void error(const char *msg)
{
  perror(msg);
  printf("\n");
  exit(1);
}

// Create socket and bind to server ip address
void initSocket(const char *serv_addr_str)
{
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("Error opening socket");

  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = inet_addr(serv_addr_str);
}

// Close connection
void closeClient()
{
  if (sockfd != -1)
  {
    close(sockfd);
    printf("Socket closed.\n");
  }
  exit(1);
}

// Force close handler
void cleanup(int signum)
{
  closeClient();
}

// Send message
void sendPosition(int x, int y)
{
  if (sockfd < 0)
    return;

  char message[256];
  snprintf(message, sizeof(message), "Position: %d %d", x, y);
  strcpy(buffer, message);

  n = write(sockfd, buffer, strlen(buffer));
  if (n < 0)
  {
    error("Error writing to socket");
  }

  printf("%s\n", buffer);
}

void handleSocketSetup(const char *serv_addr_str, const char *portno_str)
{
  // Initialize port number and server address
  portno = atoi(portno_str);

  // 1. Create socket
  initSocket(serv_addr_str);

  // 2. Connect to server and write message
  memset(buffer, 0, BUFFER_SIZE);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    error("Failed to connect to server");
  }
  printf("Connected to server\n");
}

// int main(int argc, char **argv)
// {
//   if (argc < 4)
//   {
//     fprintf(stderr, "Usage: %s <server_ip> <port> <client_#>\n", argv[0]);
//     exit(1);
//   }

//   // Bind force close to cleanup function
//   signal(SIGINT, cleanup);

//   handleSocketSetup(argv[1], argv[2], argv[3], argv[3]);

//   // Client loop
//   while (1)
//   {
//     sendPosition(atoi(argv[3]), atoi(argv[3]));
//     usleep(1000000);
//   }

//   closeClient();
//   printf("Closed socket\n");
// }
