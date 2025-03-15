## A game server implementation for a webfishing/stardew valley crossover game


https://github.com/user-attachments/assets/da2189eb-d04e-4fbc-bd68-55698da58493

### Demo Notes

Left - Server code running remotely on a DigitalOcean droplet, routed to with nginx

Right - Local terminal on my machine, running the game binary

The game client is running the client network code, and then sending the circle position to the game server on my droplet.

### Where it's at
* Can continuously receive messages from up to 10 clients concurrently (DigitalOcean VPS - 1vcpu, 1gb ram)
* Currently uses TDP

### Usage
Run `make` in the root directory, then:

Server: 
1. ./game_server <port_to_run_on>

Client
1. ./game_client <server_ip> <port> <client_label_#(1-8)>

### TODOs and System specs/reqs
I'm tracking the changes I want to make [here on Notion](https://ambitious-garden-823.notion.site/Server-to-do-s-1aeae526b05c803fb09efdd566fc0989?pvs=4)
