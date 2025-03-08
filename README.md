## A game server for a turn-based text RPG

### Where it's at
* Can continuously receive messages from a client until client closes its connection
* Uses TCP at the moment, but will switch to UDP

### Usage
Run `make` in the root directory, then:

Server: 
1. ./server <port_to_run_on>

Client
1. ./client <server_ip> <port>

![image](https://github.com/user-attachments/assets/5f7a2953-a2a6-4a26-b6a9-ba12786ecaf6)

### TODO
I'm tracking the changes I want to make [here on Notion](https://ambitious-garden-823.notion.site/Server-to-do-s-1aeae526b05c803fb09efdd566fc0989?pvs=4)
