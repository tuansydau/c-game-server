# TODO: This was chatgpt'd, please make it not**

CC = clang
CFLAGS = -std=c99 -Wall -Werror

SERVER_SRC = game_server.c
CLIENT_SRC = game_client.c

SERVER_BIN = game_server
CLIENT_BIN = game_client

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_SRC)

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC)

clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)
