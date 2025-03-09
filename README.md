## A game server implementation for a webfishing/stardew valley crossover game

### Where it's at
* Can continuously receive messages from up to 10 clients concurrently (I didn't test more)
* Currently uses TDP

### Usage
Run `make` in the root directory, then:

Server: 
1. ./game_server <port_to_run_on>

Client
1. ./game_client <server_ip> <port> <client_label_#(1-8)>

![image](https://github.com/user-attachments/assets/5f7a2953-a2a6-4a26-b6a9-ba12786ecaf6)

### TODOs and System specs/reqs
I'm tracking the changes I want to make [here on Notion](https://ambitious-garden-823.notion.site/Server-to-do-s-1aeae526b05c803fb09efdd566fc0989?pvs=4)
