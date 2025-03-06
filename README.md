## A game server for a turn-based text RPG

### Where it's at
* Transitioning from its old roots as a WIP HTTP/0.9 server
* Can continuously receive messages from a client until client closes its connection

### Usage
Server: 
1. `gcc -std=c99 game_server.c -o server`
2. ./server <port_to_run_on>

Client
1. `gcc -std=c99 game_client.c -o client`
2. ./client <server_ip> <port>

![image](https://github.com/user-attachments/assets/5f7a2953-a2a6-4a26-b6a9-ba12786ecaf6)

### TODO
* Matchmaking between two clients and putting them in the same game room
* Account management
* Persistent account data between games
* Multi-tenancy
* Make the game 💀
* The inevitable port to C++
